CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: s21_grep

s21_grep: s21_grep.c s21_grep.h
	$(CC) s21_grep.c $(CFLAGS) -o s21_grep

clean:
	/bin/rm -rf s21_grep checkGrep*

run: s21_grep
	./s21_grep test ../test_example/grep_test/my_tests/*

test: s21_grep
	sh grep_test_script.sh

checks: style leaks cppcheck

style:
	python3 ../../materials/linters/cpplint.py --extension=c *.c *.h
	
leaks: s21_grep
	leaks --atExit -- ./s21_grep -e test -e 123 -i -n ../test_example/grep_test/*/*

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c *.h
