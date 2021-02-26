Mock functions for C unit tests.

# What are unit tests and what is a mock?

A unit test checks that a particular function does a particular
thing under a particular condition. Mocks enable unit tests to
say "here is a list of expected calls and the arguments they
should be called with under this scenario, tell me if my code is
producing the same list".

## Table of Contents

- [mock-c repository contents](README.md#mock-c-repository-contents)
- [Integrating mock-c in your project](README.md#integrating-mock-c-in-your-project)
- [Example recipe for a unit test application](README.md#example-recipe-for-a-unit-test-application)
- [About mock-c](README.md#about-mock-c)
- [Avoid mocking as much as possible](README.md#avoid-mocking-as-much-as-possible)

# mock-c repository contents

```
.
├── build/
├── code/
└── tests/
```

## mock-c tests folder

`tests/` contains the unit tests for testing **mock-c**.
Ignore `tests/` unless you are changing `mock-c`.

## mock-c code folder

`code/` contains:

- the **mock-c** source code:

  ```
  Mock.c           Mock.h
  RecordedArg.c    RecordedArg.h
  RecordedCall.c   RecordedCall.h
  ReturnValues.c   ReturnValues.h
  ```

  I'm disappointed every time I start poking around in here. I
  implemented stuff in **mock-c** as I needed it and never went
  back to clean out the old stuff. It does what I need for now,
  but it needs a haircut.

- a modified version of *ThrowTheSwitch*'s [Unity
  Test](https://github.com/ThrowTheSwitch/Unity) source code:

  ```
  unity.c          unity.h
                   unity_internals.h
  ```

  My modifications are very minor.

- and two extra files that are not necessary to use **mock-c**
  but help me get **mock-c** running on a new computer:
    - `Makefile`
        - run `make lib-tags` inside the `code` folder to build a
          tags file with ctags to tag-jump and auto-complete
          using symbols from *system headers*, in particular the
          system header `glib.h` and all the headers it includes
        - run `make` inside the `code` folder to test if GLib is
          installed
    - `test-glib-install.c`
        - this is 11 lines of code that prints a
          "Congratulations" if GLib is installed

## mock-c build folder

`build/` contains the **mock-c** object files that unit tests are
linked with. The object files are not in this repository; your
project compiles them. And your project links with these object
files when it builds its test runner application.

# Integrating mock-c in your project

```bash
$ cd my-project
$ git clone https://github.com/sustainablelab/mock-c.git
```

Here is an example project structure:

```
. <------------------- My project
├── project-code/ <--- My project's top-level firmware folder
│   ├── build/
│   ├── code/
│   ├── tests/
│   └── Makefile <---- My build script tells the linker to look in ../mock-c/build/
│
└── mock-c/ <--------- this repository
    ├── build/ <------ My build script builds these .o files
    │   ├─── Mock.o
    │   ├─── RecordedArg.o
    │   ├─── RecordedCall.o
    │   ├─── ReturnValues.o
    │   └─── unity.o
    │
    ├── code/
    └── tests/
```

Here are build examples using:

- `make` and `gcc` as the build tools
- the above file structure
    - i.e., where **mock-c** is cloned, relative to your build
      script

## Compiling mock-c

Your project's build script (`Makefile`) builds the `mock-c` object files
like this:

```make
CFLAGS := -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include

../mock-c/build/%.o: ../mock-c/code/%.c ../mock-c/code/%.h ../mock-c/code/unity_internals.h
	gcc -c $< -o $@ $(CFLAGS)
```

*The context is that your test runner executable links with
mock-c object files (I'll show a recipe for that later). The
recipe above tells `make` how to create those files in the
`../mock-c/build/` folder if they don't exist (and they won't
exist when you first clone this repository).*

I explain how to read this recipe so you can achieve the same
goal with build tools other than `make` and `gcc`.

### Reading Makefile recipes

```
target: pre-requisites
	action
```

- `target` is whatever needs to get made
- `pre-requisites` are a list of files
    - `make` rebuilds `target` if it is older than any of the `pre-requisites`
- `action` is whatever needs to get done (e.g., compile a `.c` into a `.o`)

*`action` uses symbols `$<` and `$@`*

```
target: pre-requisites
	gcc -c $< -o $@ $(CFLAGS)
    └──────────┬────────────┘
               │
            action
```

- `$<` -- the **first** file in the list of `pre-requisites`
- `$^` -- **all** the files in the list of `pre-requisites`
- `$@` -- the `target`

*`target` and `pre-requisites` use symbol `%`*

```
  target───┐  pre-requisites ──┐
           │                   │
           │  ┌────────────────┴─────┐
../build/%.o: ../code/%.c ../code/%.h
```

The `%` captures the **stem**, thereby generalizing this for all
of the `../mock-c/build/` object files.

For example, if `../mock-c/build/Mock.o` does not exist, `make`
finds the above recipe because it matches the pattern `../mock-c/build/%.o`.

In this example, the **stem** is `Mock`, so when make needs to
create `Mock.o`, it expands the recipe into this:

```make
../mock-c/build/Mock.o: ../mock-c/code/Mock.c ../mock-c/code/Mock.h ../mock-c/code/unity_internals.h
	gcc -c ../mock-c/code/Mock.c -o ../mock-c/build/Mock.o -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
```

The `CFLAGS` are in addition to whatever compiler flags your
build script already has. The example only shows the compiler
flags necessary to compile **mock-c**:

```make
CFLAGS := -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
```

The `-Ipath` flag tells the compiler where to search for header
files, so the above tells the compiler where to find your
computer's `glib` headers. I detail how to install **GLib** and
how to determine these flags [later](README.md#glib). The
`-Ipath` flags in the example above show the default POSIX
install path for **GLib**.

The **mock-c** source code has `#include <glib.h>`, but this
repository does not include **GLib** source code and does not
include pre-compiled **GLib** libraries. I treat `glib.h` as a
system header, so these `-I` flags are necessary for the compiler
to find the **GLib** headers on your system.

## Linking mock-c

Unit test code will `#include <mock-c.h>`. Tell the compiler
where to search for this header file:

```
-I../mock-c/code
```

The test runner executable links with the **mock-c** object
files. Tell the linker where to search for these object files:

```
-L../mock-c/build
```

The **mock-c** object files refer to symbols in the **GLib**
libraries. Tell the linker which libraries to search to find
definitions of the **GLib** symbols:

```
-lglib-2.0 -lintl
```

## Example recipe for a unit test application

Putting that all together, here is my project's recipe for
writing test results to a markdown file:

```make
CFLAGS := -I../mock-c/code \
	-I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include \
	-g -Wall -Wextra -pedantic
LFLAGS := -lglib-2.0 -lintl

build/test_runner.md: build/test_runner.exe
	$< > $@

build/test_runner.exe: tests/test_runner.c test_Blah1.c test_Blah2.c \
						../mock-c/build/unity.o \
						../mock-c/build/Mock.o ../mock-c/build/ReturnValues.o \
						../mock-c/build/RecordedArg.o ../mock-c/build/RecordedCall.o
	gcc $(CFLAGS) $^ -o $@ $(LFLAGS)

../mock-c/build/%.o: ../mock-c/code/%.c ../mock-c/code/%.h ../mock-c/code/unity_internals.h
	gcc -c $< -o $@ $(CFLAGS)
```

# Example usage in a test

TODO(sustainablelab): Document how to use this thing

# About mock-c

**mock-c** is entirely in C, no C++. I'd like to make it
dependency-free one day, but for now it requires **GLib**.

## mock-c is built on top of these libraries

- [Unity Test](https://github.com/ThrowTheSwitch/Unity) by ThrowTheSwitch
    - a three-file library targeting unit tests for embedded systems
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

### Slightly modified Unity Test

I modified **Unity Test** to make the setup and teardown
functions into function pointers. That is the version of **Unity
Test** included in this repository.

TODO(sustainablelab): Show my specific changes to Unity Test

### Unity Test License

The original [**Unity Test** license](LICENSE-Unity-Test.md) is
included in this repository, as required by the standard MIT
license.

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

*I explained earlier [what the cryptic symbols
mean](README.md#reading-makefile-recipes).*

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

To "mock" a function is to stub it with a **fake** version that
records when (in the call order) it was called and what arguments
it was called with.

## TDD terminology

TDD (Test Driven Development) is a rabbit-hole, so instead of
expecting you to look this stuff up and reconcile contradictory
definitions, I will just say what I mean when I use these words
*stub*, *fake*, and *mock*:

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

## Reinventing wheels

How do you implement mocking? People do lots of complicated
things to mock functions. Everything I found was too complicated
for me to get it working. So I came up with my own way.

The mocks record themselves in a global list setup by the test
suite (the test suite is the application that calls all the unit
tests). This global list is erased before each unit test.

When the function under test calls fake functions, the fake
function writes its name and its arguments to the global list.
The test is to compare the expected list of calls against what
was recorded in the global list and identify where something
unexpected happened.

## Avoid mocking as much as possible

In practice, the source code definition of the function under
test gets bracketed with macros that rename functions with a
`Fake` suffix. **Those macros add noise to the source code.**

It's possible to eliminate these macros using function pointers,
and that is exactly how **mock-c** started out. But when speed
matters, the function pointer approach adds extra operations to
load the function. Speed matters in embedded systems. I think
it's a mistake to sacrifice speed in support of 100% unit test
coverage (i.e., if every function used a function pointer because
every function was mocked because that's the only way to true
100% test coverage). Furthermore, in my particular case writing C
for 8-bit AVR microcontrollers, the function pointer approach
prevented **avr-gcc** from choosing the optimal assembly
instructions.

**Mocking also generates a lot of extra code (i.e, project code
that is not running on the target)**. This extra code takes time
to maintain. When the function's argument types change, the
definition of the fake needs to change, and all the tests that
are checking the arguments needs to change. The main benefit of
TDD is that it *lowers* the barrier to changing code. So if
hitting 100% test coverage means I'm more hesitant to change the
code (because of this enormous ripple effect throughout the
tests), then it defeats the main reason for doing TDD in the
first place.
