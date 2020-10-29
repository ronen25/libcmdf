CFLAGS=-ansi -pedantic -Wall -Werror -ggdb -O0 -D_POSIX_SOURCE
LDLIBS=-lreadline

ALL: compile_c_test

link_to_lib:
	ln -s ../../libcmdf.h ./libcmdf.h

c_test: c_test.c
c_submenu: c_submenu.c

compile_c_test: link_to_lib c_test
compile_c_submenu: link_to_lib c_submenu
