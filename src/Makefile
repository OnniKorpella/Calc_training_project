CC=						gcc #-g3 #$(FSANIT)

var=					$(shell pkg-config --cflags --libs check)

FLAGS=					-Wall -Wextra -std=c11 -Werror
FSANIT=					-fsanitize=address -pedantic
CHECK_FLAGS=            -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
GCOV_FLAGS=             -fprofile-arcs -ftest-coverage -lgcov
CHECK_FLAGS1=           -lcheck -lm -lpthread

PATH_C=					Functions/
PATH_O=					../datasets/object/
PATH_T=					Tests/

MAIN=					../code-samples/main.c 
TEST_FILE=		    	Tests/Test.c
MAIN_O=					$(PATH_O)main.o

# SRCS = *.c $(wildcard)
# OBJST = $(SRCS:.c=.o)
SRCS = 					$(PATH_C)Stack.c\
						$(PATH_C)Validator.c\
						$(PATH_C)PrintStack.c\
						$(PATH_C)Parser.c\
						$(PATH_C)Notation.c\
						$(PATH_C)Calc.c\
                        $(PATH_C)Credit.c\
                        $(PATH_C)Debit.c\

SRCS_TEST =				$(PATH_C)Stack.c\
						$(PATH_C)Validator.c\
						$(PATH_C)Parser.c\
						$(PATH_C)Notation.c\
						$(PATH_C)Calc.c\
						$(PATH_C)Credit.c\
                        $(PATH_C)Debit.c\

FOO_O=					../datasets/*.o
NAME =					test
REPORT_NAME =			report

all: main
test: 
	$(CC) $(SRCS) $(TEST_FILE) $(var) -o $(PATH_O)test 
	./$(PATH_O)test
gcov_report: 
	$(CC) $(var) -o $(PATH_T)$(NAME) $(SRCS_TEST) $(PATH_T)Test.c $(GCOV_FLAGS) $(CHECK_FLAGS1)
	./$(PATH_T)$(NAME)
	lcov -t "gcov_report" -o $(PATH_T)Tests.info -c -d .
	genhtml -o $(PATH_T)$(REPORT_NAME) $(PATH_T)Tests.info
	open $(PATH_T)report/index.html
	rm $(PATH_T)$(NAME)
	rm -rf *.gcno
	rm -rf *.gcda
clean:
	rm -rf *.gc* *.a *.gz *.o *.out *.info $(PATH_T)*.info test *.dSYM $(PATH_T)*.dSYM $(PATH_C)*.out
	rm -rf build* $(PATH_T)report
	rm -rf cd ../build
	rm -rf doxygen/html
check_my:
	cppcheck $(SRCS_TEST)
	# CK_FORK=no leaks --atExit -- obj_dir/./Tests.out
	find  . -name "*.c" > list_file | find  . -name "*.h" >> list_file | find  . -name "*.cpp" >> list_file
	cp ../materials/linters/.clang-format_my ../.clang-format
	clang-format --files list_file -i
	clang-format --files list_file -n
	rm list_file
check:
	cppcheck $(SRCS_TEST)
	find  . -name "*.c" > list_file | find  . -name "*.h" >> list_file | find  . -name "*.cpp" >> list_file
	cp ../materials/linters/.clang-format ../.clang-format
	clang-format --files list_file -i
	clang-format --files list_file -n
	rm list_file

install: clean test
	cd ./CALC/ && cmake . && $(MAKE) all
#make copy
	make run
run: 
# open $(HOME)/Desktop/S21_SamartCalc.app 
	# open CALC/CALC.app
	open CALC/CALC.app/Contents/MacOS/CALC 
copy:
	cp -rf CALC/CALC.app $(HOME)/Desktop/S21_SamartCalc.app 
uninstall: clean
	rm -rf CALC/CALC.app
	rm -rf CALC/CMakeFiles
	rm -rf CALC/Makefile
	rm -rf CALC/CALC_autogen
	rm -rf CALC/CMakeCache.txt
	rm -rf CALC/cmake_install.cmake
dist: 
	@mkdir CalcDir
	cp $(PATH_C)*.c CalcDir
	cp *.h CalcDir
	cp ./CALC/CMakeLists.txt.user CalcDir
	cp ./CALC/*.cpp CalcDir
	cp ./CALC/*.ui CalcDir
	cp Makefile CalcDir
	tar -czf CalcArh.tar.gz CalcDir/
	rm -rf CalcDir
dvi:
	cd doxygen && ./doxygen Doxyfile && open html/index.html
reinstall:
	make uninstall
	make install
# valgrind_main: main
# 	valgrind --trace-children=yes --track-fds=yes \
# 	--track-origins=yes --leak-check=full --show-leak-kinds=all ./$(PATH_O)/main.o
# leak_main: main
# 	CK_FORK=no leaks --atExit -- ./$(PATH_O)/main.o
# valgrind_test: test
# 	valgrind --trace-children=yes --track-fds=yes \
# 	--track-origins=yes --leak-check=full --show-leak-kinds=all ./$(PATH_O)/test
# leak_test: test
# 	CK_FORK=no leaks --atExit -- test
# git: uninstall
# 	git status
# git_add:
# 	git add -A
# 	git commit -m "FINISH!!!"
# 	git push origin develop
# test_copy:
# 	$(CC) $(var) ../data-samples/test_copy.c -o test_copy.o
# 	./test_copy.o
# main:
# 	# clear
# 	#$(CC) $(FLAGS) $(MAIN) $(SRCS) -o $(MAIN_O)
# 	$(CC) $(MAIN) $(SRCS) -o $(MAIN_O)
# 	./$(MAIN_O)
# gitlab:
#	find . -type f -name ".gitkeep" -delete