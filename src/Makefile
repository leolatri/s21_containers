CPP = g++ -g  
FLAGS_CC = -std=c++17 -fprofile-arcs -ftest-coverage
FLAGS_LEAKS = leaks --atExit --
TEST_FLAGS = -I /usr/local/include -L /usr/local/lib -lgtest -lgtest_main -pthread

RUN = ./s21_containers.out
TEST_RUN = ./test_containers.out

all: clean s21_containers_oop run 

test: 
	@$(CPP) $(FLAGS_CC) tests.cc -o test_containers.out $(TEST_FLAGS) 
	$(TEST_RUN) 
	@rm -rf *.o 
	@clear
	@$(TEST_RUN)

coverage: test
	@gcovr -r . --html --html-details -o coverage.html

clean: 
	@rm -rf *.out *.gcda *.gcno *.gcov *.css *.html *.a