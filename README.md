Mock functions for C unit tests.

# What are unit tests and what is a mock?

A unit test checks that a particular function does a particular
thing under a particular condition. Mocks enable unit tests to
say "here is a list of expected calls and the arguments they
should be called with under this scenario, tell me if my code is
producing the same list".

# Repo organization

```
.
├── build/
├── code/
└── tests/
```

Folder `tests` contains the unit tests for testing **mock-c**.

Folder `build` contains the **mock-c** object files that unit
tests are linked with. It is also where the `tests/Makefile`
dumps the executable that runs the unit tests for testing
**mock-c** and the final test result output.

Folder `code` contains:

- the **mock-c** source code:

  ```
  Mock.c           Mock.h
  RecordedArg.c    RecordedArg.h
  RecordedCall.c   RecordedCall.h
  ReturnValues.c   ReturnValues.h
  ```
- a modified version of the **Unity Test** source code:
  ```
  unity.c          unity.h
                   unity_internals.h
  ```
- and two extra files that are not necessary to use `mock-c`:
    - `Makefile`
        - run `make` inside the `code` folder to test GLib is installed
        - run `make lib-tags` to build a tags file with ctags to
          tag-jump and auto-complete using symbols from *system
          headers*, in particular the system header `glib.h` and
          all the headers it includes
    - `test-glib-install.c`
        - this is 11 lines of code that prints a
          "Congratulations" if GLib is installed

# The mock tool is built on top of these libraries

- [Unity Test](https://github.com/ThrowTheSwitch/Unity) by ThrowTheSwitch
- [GLib](https://developer.gnome.org/glib/unstable/) from
  GNOME.org
    - this is a **big** library that gives C "modern" types
    - I'm using it for strings and lists (doubly-linked lists):
        - [GString](https://developer.gnome.org/glib/unstable/glib-Strings.html)
        - [GList](https://developer.gnome.org/glib/unstable/glib-Doubly-Linked-Lists.html)

## Unity Test
Unity Test is just three source files:

- `code/unity.c`
- `code/unity.h`
- `code/unity_internals.h`

There is nothing to install, no linker flags to add to the build
recipe.

### Modified Unity Test
I modified **Unity Test** slightly for function faking. That is
the version of **Unity Test** included in this repository.

TODO(sustainablelab): list my changes to Unity Test

## GLib

1. Install `GLib`.

   Either download a tarball from here:

   https://developer.gnome.org/glib/

   Or use your package manager. For example, here is the
   installation using the command-line version of Cygwin's package
   manager:

   ```bash
   $ apt-cyg install libglib2.0-devel libglib2.0-doc
   ```

2. Determine the compiler and linker flags to add to your build
   recipe.

   This is explained here:

   https://developer.gnome.org/glib/2.66/glib-compiling.html

   TLDR, do this:

   ```bash
   $ pkg-config --libs glib-2.0
   -lglib-2.0 -lintl
   
   $ pkg-config --cflags glib-2.0
   -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
   ```

3. Test that `glib` is installed.

   *Create a file to compile that depends on glib:*
   
   ```c
   // code/test-glib-install.c
   #include <glib.h>
   #include <stdbool.h>
   #include <stdio.h>

   int main()
   {
       GString *msg = g_string_new("Congratulations! GLib is installed.");
       puts(msg->str);
       g_string_free(msg, true);
       return 0;
   }
   ```

   *Create a makefile:*
   
   ```make
    CFLAGS := -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
    LFLAGS := -lglib-2.0 -lintl

    ../build/test-glib-install.exe: test-glib-install.c
    	gcc $(CFLAGS) $< -o $@ $(LFLAGS)
    	../build/test-glib-install.exe
   ```
   
    - The CFLAGS are necessary for the compiler to find `glib.h`
      and the files that get included by `glib.h`
        - in the above example,. the `GString` datatype is
          defined in `gstring.h`
        - the `-I` flags tell the compiler which directories to
          search for header files
    - The LFLAGS are necessary for the linker to find the
      definitions of the `glib` symbols
        - in the above example, the definitions for functions
          `g_string_new` and `g_string_free` are in pre-compiled
          libraries
        - the `-l` flags tell the linker which libraries to
          search when linking

   *Build:*
   
   ```bash
   $ make
   ../build/test-glib-install.exe
   Congratulations! GLib is installed.
   ```

# Example unittest

TODO(sustainablelab): example unittest and build.

## Building up the Makefile for unit tests

`unity.o` builds quickly. If there are no other object files to
link, then there is no need for conditional builds. So the
Makefile would boil down to one recipe:

```make
../build/test_runner.exe: test_runner.c ../code/unity.c ../code/unity.h ../code/unity_internals.h
	gcc $(CFLAGS) test_runner.c ../code/unity.c -o $@ $(LFLAGS)
```

But once there are several object files to link, the build goes
much faster if the object files do not have to rebuild every time
(based on my experience using `gcc` in Cygwin).

So the `make` recipe splits into two recipes:

```make
../build/test_runner.exe: test_runner.c ../build/unity.o
	gcc $(CFLAGS) $^ -o $@ $(LFLAGS)

../build/unity.o: ../code/unity.c ../code/unity.h ../code/unity_internals.h
	gcc -c $< -o $@ $(LFLAGS)
```

The first recipe says:

- `test_runner.exe` depends on `test_runner.c` and on the
  pre-compiled object file `../build/unity.o`

The idea is that the `test_runner.c` file is changing as tests
are edited, but the source files in the compilation unit for
`unity.o` are not going to change often.

Therefore, there is no point rebuilding `unity.o` every time
`test_runner.exe` is built. `unity.o` is only rebuilt if any of
the `unity` source files change. And if that happens, `make`
detects that `unity.o` is out-of-date and rebuilds `unity.o`
before building `test_runner.exe`.

This is captured in the second recipe:

- build `unity.o` by compiling `unity.c`
- the trigger to rebuild `unity.o` is to check if `unity.c` or
  either of its header files change.

The point of splitting into two recipes is that there are several
object files, not just `unity.o`. To handle any object file, the
second recipe turns into this:

```make
../build/%.o: ../code/%.c ../code/unity.h ../code/unity_internals.h
	gcc -c $< -o $@ $(CFLAGS)
```

The idea is that `test_runner.exe` is built by linking
`test_runner.o` with *many* object files, not just `unity.o`.
This revised recipe is generalized for making a `foo.o` in the
`build` folder from any `foo.c` in the `code` folder. If changes
to a header file should trigger a rebuild, those header files get
added to the list of prerequisites.

Finally, here is the actual make recipe for the unit tests that
test `mock-c`. There are several object files to link with and the "main"
source code is divided into several files.

```make
../build/test_runner.exe: test_runner.c ExampleCalls.c test_ExampleCalls.c \
						test_Mock.c test_ReturnValues.c \
						test_RecordedArg.c test_RecordedCall.c \
						../build/unity.o \
						../build/Mock.o ../build/ReturnValues.o \
						../build/RecordedArg.o ../build/RecordedCall.o
	gcc $(CFLAGS) $^ -o $@ $(LFLAGS)

../build/%.o: ../code/%.c ../code/%.h ../code/unity_internals.h
	gcc -c $< -o $@ $(CFLAGS)
```

# More explanation about what this is

To "Mock" a function is to stub it with a **fake** version that
does not do anything except record that it was called and what
arguments it was called with.

TDD is a rabbit-hole, so instead of expecting you to look this
stuff up and reconcile contradictory definitions, I will just say
what I mean when I use these words *stub*, *fake*, and *mock*:

- A *stub* replaces a function with a dummy version that still
  compiles but has zero functionality. This is what I use 99% of
  the time. The common use case is testing a function that calls
  functions that wait on the embedded hardware.
- A *fake* is a *stub* that adds fake functionality for the
  purposes of the test, for example giving the unit test control
  over the value returned by the function so that the unit test
  can test a scenario where the function returns a particular
  value. The return value is "faked".
- A *mock* is where the fake functionality is to record how the
  function was called. And maybe it does other fake functionality
  too, like the return value thing. This kind of fake gets a
  special name simply because **it's more difficult to implement
  this particular fake functionality**.

TLDR: Mocking is for the *small* subset of unit tests where the
goal is to check whether the function under test is calling other
functions and calling them with the correct arguments.

How does that work? People do lots of complicated things to mock
functions. Everything I found was too complicated for me to get
it working. So I came up with my own way.

The mocks record themselves in a global list setup by the test
suite (the test suite is the application that calls all the unit
tests). This global list is erased before each unit test.

When the function under test calls fake functions, the fake
function writes its name and its arguments to the global list.
The test is to compare the expected list of calls against what
was recorded in the global list and identify where something
unexpected happened.

In practice, this means the source code definition of the
function under test gets bracketed with macros that rename
functions with a `Fake` suffix. Those macros add noise to the
source code. That's one reason to use this tool sparingly.

Mocking a function also generates a lot of extra test code that
now needs to be maintained. If the function's argument types
change, the definition of the fake needs to change and all the
tests that are checking the arguments needs to change. That's
another reason to use this tool sparingly.

