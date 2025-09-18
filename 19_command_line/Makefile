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
CONFIG_DIR = config
SCRIPTS_DIR = scripts

# Цели
TARGET = terminal

# Исходные файлы
SRCS = $(SRC_DIR)/main.cpp \
       $(CORE_DIR)/commandline.cpp \
       $(CORE_DIR)/config.cpp \
       $(UTILS_DIR)/console.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all clean rebuild run test help install

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
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Создание директорий
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/core $(OBJ_DIR)/utils

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Запуск программы
run: all
	@echo "\n\033[0;32m🎯 Running terminal...\033[0m\n"
	./$(BIN_DIR)/$(TARGET)

# Запуск с тестовыми параметрами
test: all
	@echo "\n\033[0;32m🧪 Testing with config...\033[0m\n"
	./$(BIN_DIR)/$(TARGET) --config $(CONFIG_DIR)/config.toml

# Запуск со скриптом
test-script: all
	@echo "\n\033[0;32m📜 Testing with script...\033[0m\n"
	./$(BIN_DIR)/$(TARGET) --script $(SCRIPTS_DIR)/startup.txt

# Показать структуру проекта
tree:
	@echo "\n\033[0;36m📁 Project structure:\033[0m"
	@find . -type d -name "bin" -prune -o -type d -name "obj" -prune -o -type f -print | head -20
	@echo "..."

# Создать стандартную структуру папок
init:
	mkdir -p $(SRC_DIR)/core $(SRC_DIR)/utils $(OBJ_DIR) $(BIN_DIR) \
	         $(CONFIG_DIR) $(SCRIPTS_DIR) tests docs
	@echo "\n\033[0;32m📁 Project structure created!\033[0m"

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "\n\033[0;32m🧹 Clean completed!\033[0m"

# Полная очистка
distclean: clean
	rm -f *.log *.tmp
	@echo "\n\033[0;32m🧹 Deep clean completed!\033[0m"

# Пересборка
rebuild: clean all

# Помощь
help:
	@echo "\n\033[1;34m📋 Available commands:\033[0m"
	@echo "  \033[0;32mmake all\033[0m        - Build terminal (default)"
	@echo "  \033[0;32mmake run\033[0m        - Build and run terminal"
	@echo "  \033[0;32mmake test\033[0m       - Test with config file"
	@echo "  \033[0;32mmake test-script\033[0m - Test with script"
	@echo "  \033[0;32mmake tree\033[0m       - Show project structure"
	@echo "  \033[0;32mmake init\033[0m       - Create project structure"
	@echo "  \033[0;32mmake clean\033[0m      - Clean build artifacts"
	@echo "  \033[0;32mmake distclean\033[0m  - Deep clean"
	@echo "  \033[0;32mmake rebuild\033[0m    - Clean and rebuild"
	@echo "  \033[0;32mmake help\033[0m       - Show this help"