.PHONY: all clean test s21_matrix_oop.a

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
TFLAGS = -lgtest
CORE = core/matrix_oop
TEST = unit_tests/matrix_tests
COVEREGE = --coverage

all: matrix_oop.a test gcov_report

matrix_oop.a: $(CORE).h
	@$(CC) $(CFLAGS) -c $(CORE).cc
	@ar rc matrix_oop.a matrix_oop.o
	@rm matrix_oop.o

test: $(CORE).cc $(TEST).cc $(CORE).h
	@$(CC) $(CFLAGS) $(COVEREGE) $(CORE).cc $(TEST).cc -o test $(TFLAGS)
	mv ./test object_files
	@object_files/./test

gcov_report: test
	rm matrix_tests.gc*
	mv *.gc* object_files
	cd object_files
	lcov -t test -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	@-rm -rf *.o *.a test object_files/./test object_files/*.gc* Report/* *.info *.gc* core/*.a

style:
	@clang-format -style=google -n $(CORE).cc $(CORE).h $(TEST).cc
