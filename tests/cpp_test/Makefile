CXXFLAGS=-Wall -Werror -ggdb -O0
LDLIBS=-lreadline

ALL: compile_cpp_test

link_to_lib:
	ln -s ../../libcmdf.h ./libcmdf.h

cpp_test: cpp_test.cpp

compile_cpp_test: link_to_lib cpp_test
