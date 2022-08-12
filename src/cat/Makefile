CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: s21_cat

s21_cat: s21_cat.c s21_cat.h
	$(CC) s21_cat.c $(CFLAGS) -o s21_cat

clean:
	/bin/rm -rf s21_cat check*

run: s21_cat
	./s21_cat -n ../test_example/cat_test/my_tests/*

test: s21_cat
	sh cat_test_script.sh

checks: style leaks cppcheck

style:
	python3 ../../materials/linters/cpplint.py --extension=c *.c *.h
	
leaks: s21_cat
	leaks --atExit -- ./s21_cat -bents ../test_example/cat_test/*/*

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c *.h
