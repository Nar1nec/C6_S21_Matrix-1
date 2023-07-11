CC = gcc
CFLAGS = -Wall -Werror -Wextra 
GKOVFLAGS = -lgcov --coverage
CHECKFLAGS = -lcheck

OPEN_CMD = open

OS = $(shell uname)
ifeq ($(OS), Linux)
CHECKFLAGS += -lm -lpthread -lsubunit -lrt
OPEN_CMD = xdg-open
endif

SOURCES = $(wildcard s21_*.c)
OBJECTS = $(SOURCES:.c=.o)
TESTS_SOURSES = $(wildcard ./tests/*.check)
CFLAGS_GCOV =-fprofile-arcs --coverage

all: s21_matrix.a

rebuild: clean all

s21_matrix.a: $(OBJECTS) s21_matrix.h
	ar rc $@ $(OBJECTS)
	ranlib -D $@

lib_cov.a: $(SOURCES) s21_matrix.h
	$(CC) $(CFLAGS) $(CFLAGS_GCOV) -c  $(SOURCES)
	ar rc lib_cov.a $(OBJECTS)
	ranlib lib_cov.a

test: clean $(TESTS_SOURSES) s21_matrix.a
	@checkmk clean_mode=1 ./s21_matrix.h $(TESTS_SOURSES) > test.c
	$(CC) test.c $(CHECKFLAGS) -lm s21_matrix.a -o test
	./test

gcov_report: clean $(TESTS_SOURSES) lib_cov.a
	checkmk clean_mode=1 $(TESTS_SOURSES) > test.c
	$(CC)  test.c -c
	$(CC)  test.o -g $(CHECKFLAGS) lib_cov.a -o test $(GKOVFLAGS)
	./test > /dev/null
	lcov -t "t" -o test.info -c -d . 
	genhtml -o report test.info 
	$(OPEN_CMD) ./report/index.html
	rm -f test.c

style:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h
	rm .clang-format

style_check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	rm .clang-format

clean:
	rm -rf *.a *.o *.test *test.c .test.c *.gcda *.gcno *.info test.c report a.out test report
