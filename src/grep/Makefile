CC = gcc
CFLAGS =-std=c11 -Wall -Wextra -Werror -D_GNU_SOURCE

s21_grep: clean
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

clean:
	rm -rf s21_grep s21_grep.dSYM *.o *.out .clang-format *.log

rebuild: clean s21_grep

clang: s21_grep
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	clang-format -i *.c *.h

valgrind_check:
	sh ../../materials/build/run.sh

check: s21_grep
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c *.h
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ./../../materials/linters/cpplint.py --extensions=c *.c *.h
	rm -f CPPLINT.cfg

