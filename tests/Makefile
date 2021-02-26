# TODO(sustainablelab): /build/mock-c/ and /code/mock-c/
# Idea for simple distribution is to drop the mock-c source into
# the project, e.g., git-clone the mock-c repo directly into
# the project in a `unittest-c` folder.
# mock-c builds with the project, object files
# get generated -- those should go into a dedicated place that
# doesn't mix with the project object files.
CFLAGS := -I../code -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include \
	-g -Wall -Wextra -pedantic
LFLAGS := -lglib-2.0 -lintl

../build/test_runner.md: ../build/test_runner.exe
	$< > $@

../build/test_runner.exe: test_runner.c ExampleCalls.c \
						test_Mock.c test_ReturnValues.c \
						test_RecordedArg.c test_RecordedCall.c \
						../build/unity.o \
						../build/Mock.o ../build/ReturnValues.o \
						../build/RecordedArg.o ../build/RecordedCall.o
	gcc $(CFLAGS) $^ -o $@ $(LFLAGS)

../build/%.o: ../code/%.c ../code/%.h ../code/unity_internals.h
	gcc -c $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	rm -f ../build/ExampleCalls.o
	rm -f ../build/Mock.o
	rm -f ../build/RecordedArg.o
	rm -f ../build/RecordedCall.o
	rm -f ../build/ReturnValues.o
	rm -f ../build/test_runner.exe
	rm -f ../build/test_runner.md
	rm -f ../build/unity.o

.PHONY: lib-tags
lib-tags:
	gcc -M $(CFLAGS) test_runner.c | \
		sed -e 's/[\\ ]/\n/g' | \
		sed -e '/^ *$$/d' | \
		sed -e '/\.o:/d'  | \
		sed -e '/\.c$$/d' \
		> lib-tags.txt
	ctags -f $@ --c-kinds=+p -L lib-tags.txt
	rm lib-tags.txt
