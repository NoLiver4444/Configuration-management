# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -pedantic-errors
LDFLAGS = -lgtest -lgtest_main -lpthread

# Исходные файлы
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj
GCOV_DIR = obj/gcov
TESTS_OBJ_DIR = obj/tests
REPORT_DIR = report
BIN_DIR = bin

TARGET = test
MAIN_TARGET = main_program
GCOV_TARGET = gcov_report
LIBRARY = prac_1.a
GCOV_LIBRARY = preac_1_gcov.a

LCOV_FLAGS = -fprofile-arcs -ftest-coverage

# Исходные файлы
SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/s21_AVL_Tree/*.cpp $(SRC_DIR)/s21_set/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
GCOV_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(GCOV_DIR)/%.o,$(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(TESTS_OBJ_DIR)/%.o,$(TEST_SRCS))

# Найти main файл (предполагаем, что он называется main.cpp или содержит main)
MAIN_SRC = $(wildcard $(SRC_DIR)/main.cpp)
MAIN_OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRC))

# Фильтруем объектные файлы без main
LIB_OBJS = $(filter-out $(MAIN_OBJ),$(OBJS))

.PHONY: all test main gcov_report clean rebuild style leaks valgrind answ

all: main test

main: $(MAIN_TARGET)

test: $(TARGET)

# Компиляция основной программы
$(MAIN_TARGET): $(OBJ_DIR) $(BIN_DIR) $(LIB_OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $(LIB_OBJS) $(MAIN_OBJ) -o $(BIN_DIR)/$@
	@echo "\n\033[0;32mMain program compiled successfully!\033[0m\n"
	@echo "Run with: ./$(BIN_DIR)/$(MAIN_TARGET)"

# Запуск основной программы
run: $(MAIN_TARGET)
	@echo "\n\033[0;32mRunning main program...\033[0m\n"
	@./$(BIN_DIR)/$(MAIN_TARGET)

install_lib:
	sudo apt update
	sudo apt install gcc
	sudo apt install lcov
	sudo apt install valgrind

install_gtest:
	sudo apt install libgtest-dev
	sudo apt install cmake
	sudo cmake -S /usr/src/googletest -B /usr/src/googletest/build
	sudo cmake --build /usr/src/googletest/build
	sudo cp -r /usr/src/googletest/googletest/include/gtest /usr/local/include/
	sudo cp /usr/src/googletest/build/lib/*.a /usr/local/lib/

# ИСПРАВЛЕННАЯ ЦЕЛЬ: добавлены $(SRCS) и использование $(LDFLAGS)
gcov_report: clean
	$(CXX) $(CXXFLAGS) $(LCOV_FLAGS) $(TEST_SRCS) $(SRCS) -o $(GCOV_TARGET) $(LDFLAGS) -lgcov
	./$(GCOV_TARGET)
	lcov --ignore-errors mismatch --capture --directory . --output-file coverage.info
	lcov --remove coverage.info "/usr/*" "tests" --output-file coverage.info.cleaned
	genhtml coverage.info.cleaned --output-directory coverage

# Компиляция тестов
$(TARGET): $(TESTS_OBJ_DIR) $(OBJ_DIR) $(LIBRARY) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) $(LIBRARY) $(LDFLAGS) -o $@
	@echo "\n\033[0;32mTests compiled successfully!\033[0m\n"
	@echo "Run with: make test_run"

# Запуск тестов
test_run: $(TARGET)
	@echo "\n\033[0;32mRunning tests...\033[0m\n"
	@./$(TARGET)

$(LIBRARY): $(LIB_OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TESTS_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(TESTS_OBJ_DIR):
	@mkdir -p $(TESTS_OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(REPORT_DIR) $(GCOV_DIR) $(TESTS_OBJ_DIR) $(BIN_DIR)
	rm -f *.a *.o *.gcno *.gcda *.gcov coverage.info
	rm -f $(TARGET) $(GCOV_TARGET) $(MAIN_TARGET)
	rm -rf coverage
	rm -f coverage.info.cleaned
	rm -f answ/*.bin
	rm -f answ/*.txt

rebuild: clean all

clang:
	cp ../materials/.clang-format ./.clang-format
	clang-format -n --style=file $$(find . -type f \( -name "*.tpp" -o -name "*.h" -o -name "*.cpp" \))
	rm -f .clang-format

clang-fix:
	cp ../materials/.clang-format ./.clang-format
	clang-format -i --style=file $$(find . -type f \( -name "*.tpp" -o -name "*.h" -o -name "*.cpp" \))
	rm -f .clang-format

leaks: $(TARGET)
	leaks --atExit -- ./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET)

answ:
	mkdir -p answ

help:
	@echo "Available commands:"
	@echo "  make all       - Build both main program and tests"
	@echo "  make main      - Build only main program"
	@echo "  make run       - Build and run main program"
	@echo "  make test      - Build only tests"
	@echo "  make test_run  - Build and run tests"
	@echo "  make clean     - Clean all build artifacts"
	@echo "  make rebuild   - Clean and rebuild everything"
	@echo "  make leaks     - Run tests with leaks detection"
	@echo "  make valgrind  - Run tests with valgrind"