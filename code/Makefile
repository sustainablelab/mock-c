CFLAGS := -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
LFLAGS := -lglib-2.0 -lintl

# GLib is installed if this builds and prints to stdout:
# "Congratulations! GLib is installed."
../build/test-glib-install.exe: test-glib-install.c
	gcc $(CFLAGS) $< -o $@ $(LFLAGS)
	../build/test-glib-install.exe

.PHONY: lib-tags
lib-tags:
	gcc -M $(CFLAGS) test-glib-install.c | \
		sed -e 's/[\\ ]/\n/g' | \
		sed -e '/^ *$$/d' | \
		sed -e '/\.o:/d'  | \
		sed -e '/\.c$$/d' \
		> lib-tags.txt
	ctags -f $@ --c-kinds=+p -L lib-tags.txt
	rm lib-tags.txt

.PHONY: clean
clean:
	rm -f ../build/test-glib-install.exe
