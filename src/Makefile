CC=				gcc
CFLAGS=			-Wall -Wextra -Werror -std=c11 -pedantic
GCOVFLAGS=		-fprofile-arcs -ftest-coverage
GTKFLAGS=		$(shell pkg-config --cflags gtk4)
GTKLIBS=		$(shell pkg-config --libs gtk4)
GFLAGS=			$(shell pkg-config --cflags glib-2.0)
GLIBS=			$(shell pkg-config --libs glib-2.0)
OS:=			$(shell uname -s)
SOURSES_TEST=	test_*.c
SOURSES_POL=	s21_pol*.c
OBJECT_POL=		$(patsubst %*.c, %*.o, $(SOURSES_POL))
SOURSES_CALC=	s21_SmartCalc*.c

ifeq ($(OS), Linux)
	CC+=		-D OS_LINUX
	CHECKFLAGS=	-lpthread -lcheck -pthread -lrt -lm -lsubunit
	
endif
ifeq ($(OS), Darwin)
	CC+=		-D OS_MAC
	CHECKFLAGS=	-lcheck
endif

all: clean smart_calc

smart_calc: rebuild_lib $(SOURSES_CALC)
	$(CC) $(CFLAGS) $(GTKFLAGS) $(SOURSES_CALC) s21_polish_notation.a $(GTKLIBS) -lm -o SmartCalc_v1.0

install: uninstall smart_calc
	@mkdir ~/SmartCalc_v1.0
	@install SmartCalc_v1.0 ~/SmartCalc_v1.0

uninstall:
	@rm -rf ~/SmartCalc_v1.0

dvi:
	open readme.html

dist:
	tar -cf SmartCalc_v1.0.tar *.c *.h Makefile readme.html SmartCalc.supp gtk-osx-setup.sh

s21_polish_notation.a: $(SOURSES_POL)
	$(CC) $(CFLAGS) $(GFLAGS) -c $(SOURSES_POL) $(GLIBS)
	@ar rcs s21_polish_notation.a $(OBJECT_POL)

test: rebuild_lib $(SOURSES_TEST)
	$(CC) $(CFLAGS) $(GFLAGS) $(SOURSES_TEST) s21_polish_notation.a $(CHECKFLAGS) $(GLIBS) -o test
	./test

gcov_report: rebuild_lib
	@gcc $(GFLAGS) $(GCOVFLAGS) $(SOURSES_TEST) $(SOURSES_POL) $(CHECKFLAGS) $(GLIBS) -o GcovReport
	@./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d .
	@genhtml -o report GcovReport.info
	@open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*.gcda ./GcovReport.*

clang:
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	@rm .clang-format

valgrind_test: test
	valgrind --tool=memcheck --leak-check=yes ./test

valgrind_snap_test: test
	snap run valgrind --tool=memcheck --leak-check=full ./test

valgrind_calc: smart_calc
	valgrind --tool=memcheck --leak-check=full --suppressions=./SmartCalc.supp ./SmartCalc_v1.0

valgrind_snap_calc: smart_calc
	snap run valgrind --tool=memcheck --leak-check=full --suppressions=./SmartCalc.supp ./SmartCalc_v1.0

leaks_test: test
	leaks -atExit -- ./test

leaks_calc: test
	leaks -atExit -- ./SmartCalc_v1.0

clean:
	@rm -rf ./a.out ./*.o ./*.a ./test ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./SmartCalc_v1.0

rebuild_lib: clean s21_polish_notation.a
	@rm ./*.o

single_test: rebuild_lib
	$(CC) $(GFLAGS) polish_test.c s21_polish_notation.a $(GLIBS) -lm

install_gtk:
	ifeq ($(OS), Linux)
		sudo apt install libgtk-4-1
		sudo apt install libgtk-4-dev
		sudo apt install gtk-4-examples
	endif
	ifeq ($(OS), Darwin)
		brew install gtk4
	endif

supp:
	valgrind --tool=memcheck --leak-check=full --gen-suppressions=yes --suppressions=./SmartCalc.supp ./SmartCalc_v1.0