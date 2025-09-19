# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -pedantic-errors
LDFLAGS = 

# Директории
SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
UTILS_DIR = $(SRC_DIR)/utils
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include
CONFIG_DIR = config
SCRIPTS_DIR = scripts
TEST_VFS_DIR = test_vfs
TESTS_DIR = tests

# Цели
TARGET = terminal

# Исходные файлы
SRCS = $(SRC_DIR)/main.cpp \
       $(CORE_DIR)/commandline.cpp \
       $(CORE_DIR)/config.cpp \
       $(CORE_DIR)/vfs_manager.cpp \
       $(CORE_DIR)/vfs_node.cpp \
       $(UTILS_DIR)/console.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Флаги include
INCLUDE_FLAGS = -I$(INCLUDE_DIR) -I$(SRC_DIR)/core -I$(SRC_DIR)/utils

.PHONY: all clean rebuild run test test-vfs help init tree

# Основная цель
all: $(BIN_DIR)/$(TARGET)

# Сборка исполняемого файла
$(BIN_DIR)/$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	@echo "\n\033[0;32m✅ Terminal compiled successfully!\033[0m"
	@echo "🚀 Run with: ./$(BIN_DIR)/$(TARGET)"

# Компиляция объектных файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# Создание директорий
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/core $(OBJ_DIR)/utils

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Запуск программы
run: all
	@echo "\n\033[0;32m🎯 Running terminal...\033[0m\n"
	./$(BIN_DIR)/$(TARGET)

# Тест с VFS
test-vfs: all
	@echo "\n\033[0;32m🧪 Testing with VFS...\033[0m\n"
	./$(BIN_DIR)/$(TARGET) --vfs-path $(TEST_VFS_DIR) --script $(SCRIPTS_DIR)/test_vfs.txt

# Тест с конфигом
test-config: all
	@echo "\n\033[0;32m📋 Testing with config...\033[0m\n"
	./$(BIN_DIR)/$(TARGET) --config $(CONFIG_DIR)/config.toml

# Создать тестовую VFS структуру
create-test-vfs:
	@echo "\n\033[0;32m📁 Creating test VFS structure...\033[0m"
	mkdir -p $(TEST_VFS_DIR)/folder1
	mkdir -p $(TEST_VFS_DIR)/folder2/subfolder
	mkdir -p $(TEST_VFS_DIR)/folder3/level2/level3
	
	echo "Hello from file1.txt" > $(TEST_VFS_DIR)/file1.txt
	echo "Content of file2" > $(TEST_VFS_DIR)/folder1/file2.txt
	echo "Nested file content" > $(TEST_VFS_DIR)/folder2/subfolder/file3.txt
	echo "Deep file content" > $(TEST_VFS_DIR)/folder3/level2/level3/deep_file.txt
	echo "Another file" > $(TEST_VFS_DIR)/folder2/file4.txt
	echo "Level 2 file" > $(TEST_VFS_DIR)/folder3/level2/file5.txt
	echo "Root file" > $(TEST_VFS_DIR)/folder3/file6.txt
	@echo "\033[0;32m✅ Test VFS structure created!\033[0m"

# Показать структуру проекта
tree:
	@echo "\n\033[0;36m📁 Project structure:\033[0m"
	@tree -I 'bin|obj|*.o' -d

# Создать стандартную структуру папок
init:
	mkdir -p $(SRC_DIR)/core $(SRC_DIR)/utils $(OBJ_DIR) $(BIN_DIR) $(INCLUDE_DIR)/terminal \
	         $(CONFIG_DIR) $(SCRIPTS_DIR) $(TEST_VFS_DIR) $(TESTS_DIR) docs
	@echo "\n\033[0;32m📁 Project structure created!\033[0m"

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "\n\033[0;32m🧹 Clean completed!\033[0m"

# Полная очистка
distclean: clean
	rm -f *.log *.tmp
	@echo "\n\033[0;32m🧹 Deep clean completed!\033[0m"

# Тестовые цели
test-basic: all
	@echo "\n\033[0;32m🧪 Running basic test...\033[0m\n"
	./$(BIN_DIR)/$(TARGET) --config $(CONFIG_DIR)/basic_test.toml

test-full: all
	@echo "\n\033[0;32m🧪 Running full test...\033[0m\n"
	./$(BIN_DIR)/$(TARGET) --config $(CONFIG_DIR)/full_test.toml

test-error: all
	@echo "\n\033[0;32m🧪 Running error test...\033[0m\n"
	./$(BIN_DIR)/$(TARGET) --config $(CONFIG_DIR)/error_test.toml

test-all: test-basic test-full test-error

# Пересборка
rebuild: clean all

# Создать тестовые конфиги
create-test-configs:
	@echo "\n\033[0;32m📝 Creating test configs...\033[0m"
	mkdir -p $(CONFIG_DIR)
	echo 'vfs_path = "test_vfs"' > $(CONFIG_DIR)/basic_test.toml
	echo 'script_path = "scripts/basic_test.txt"' >> $(CONFIG_DIR)/basic_test.toml
	echo 'vfs_path = "test_vfs"' > $(CONFIG_DIR)/full_test.toml
	echo 'script_path = "scripts/test_vfs.txt"' >> $(CONFIG_DIR)/full_test.toml
	echo 'vfs_path = "test_vfs"' > $(CONFIG_DIR)/error_test.toml
	echo 'script_path = "scripts/error_test.txt"' >> $(CONFIG_DIR)/error_test.toml
	@echo "\033[0;32m✅ Test configs created!\033[0m"