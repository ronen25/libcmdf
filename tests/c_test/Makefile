CFLAGS=-ansi -pedantic -Wall -Werror -g -O0 -D_POSIX_SOURCE -I"../.."
LDLIBS=-lreadline

ALL: compile_c_test compile_c_submenu

clean:
	rm c_test
	rm c_submenu

c_test: c_test.c
c_submenu: c_submenu.c

compile_c_test: c_test
compile_c_submenu: c_submenu
