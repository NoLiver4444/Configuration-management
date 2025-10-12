# VFS Terminal - Система управления виртуальной файловой системой

## Общее описание

VFS Terminal - это консольное приложение, эмулирующее терминал с виртуальной файловой системой (VFS). Проект предоставляет интерфейс командной строки для навигации и работы с файлами в виртуальной среде, которая отображает структуру реальной файловой системы на диске.

### Основные возможности:
- Эмуляция команд терминала (ls, cd, cat, pwd, echo, help, exit)
- Виртуальная файловая система, загружаемая с физического диска
- Поддержка скриптов для автоматизации команд
- Конфигурационные файлы для настройки поведения
- Полная изоляция от реальной файловой системы хоста

## Структура проекта

```
vscode/
├── config/                    # Конфигурационные файлы
│   ├── basic_test.toml
│   ├── config.toml
│   ├── error_test.toml
│   ├── full_test.toml
│   └── scripts/              # Скрипты для тестирования
│       ├── basic_test.txt
│       ├── error_script.txt
│       ├── startup.txt
│       └── test_vfs.txt
├── src/                      # Исходный код
│   ├── core/                # Основные компоненты системы
│   │   ├── commandline.cpp/h    # Обработчик командной строки
│   │   ├── config.cpp/h         # Управление конфигурацией
│   │   ├── vfs_manager.cpp/h    # Менеджер VFS
│   │   └── vfs_node.cpp/h       # Узлы файловой системы
│   ├── utils/               # Вспомогательные модули
│   ├── console.cpp/h           # Консольный интерфейс
│   └── main.cpp/h              # Главный модуль
├── tests/                   # Тесты
│   ├── test_commandline.cpp
│   ├── test_vfs.cpp
│   └── test_run.txt
├── Makefile                 # Сборка проекта
└── README.md               # Документация
```

## Описание функций и настроек

### Основные компоненты:

#### CommandLine
- **Парсинг команд**: Разбор введенных пользователем команд
- **Встроенные команды**: ls, cd, cat, pwd, echo, help, exit
- **Динамический prompt**: Отображение текущего пользователя, хоста и пути VFS
- **Обработка аргументов**: Поддержка параметров для всех команд

#### VFSManager
- **Загрузка файловой системы**: Рекурсивное чтение структуры каталогов с диска
- **Навигация**: Изменение текущей директории (cd)
- **Чтение файлов**: Получение содержимого файлов (cat)
- **Листинг директорий**: Просмотр содержимого каталогов (ls)
- **Относительные и абсолютные пути**: Поддержка обоих типов путей

#### Config
- **Аргументы командной строки**: Обработка параметров запуска
- **Конфигурационные файлы**: Чтение настроек из TOML-файлов
- **Автоматическое создание директорий**: Инициализация структуры VFS

#### VFSNode
- **Представление узлов**: Файлы и директории как узлы дерева
- **Иерархическая структура**: Родительско-дочерние отношения
- **Хранение содержимого**: Сохранение данных файлов в памяти

## Команды для сборки и запуска

### Сборка проекта:

```bash
# Клонирование репозитория (если необходимо)
git clone <repository-url>
cd vscode

# Сборка проекта
make

# Очистка собранных файлов
make clean

# Сборка с отладочной информацией
make debug
```

### Запуск приложения:

```bash
# Базовая версия (использует VFS по умолчанию ./vfs)
./vfs_terminal

# С указанием пути к VFS
./vfs_terminal --vfs-path /path/to/your/vfs

# Со скриптом инициализации
./vfs_terminal --script config/scripts/startup.txt

# С конфигурационным файлом
./vfs_terminal --config config/config.toml

# Комбинированный запуск
./vfs_terminal -v ./my_vfs -s config/scripts/basic_test.txt -c config/config.toml

# Справка по параметрам
./vfs_terminal --help
```

### Запуск тестов:

```bash
# Запуск unit-тестов
make test

# Запуск конкретного теста
./tests/test_vfs
./tests/test_commandline

# Тестирование с различными конфигурациями
./vfs_terminal -c config/basic_test.toml
./vfs_terminal -c config/error_test.toml
./vfs_terminal -c config/full_test.toml
```

## Примеры использования

### Базовое взаимодействие:

```bash
# Запуск терминала
$ ./vfs_terminal --vfs-path ./test_vfs

# Терминал отображает prompt и ожидает команды
user@host:/$ ls
📁 folder1
📁 folder2
📄 file1.txt

user@host:/$ cd folder1
Changed directory to: folder1

user@host:/folder1$ ls
📄 document.txt
📄 notes.md

user@host:/folder1$ cat document.txt
This is the content of document.txt

user@host:/folder1$ pwd
/folder1

user@host:/folder1$ cd /
Changed directory to: /

user@host:/$ exit 0
```

### Использование скриптов:

```bash
# Создание скрипта
echo "ls /" > myscript.txt
echo "cd folder1" >> myscript.txt
echo "ls" >> myscript.txt
echo "cat document.txt" >> myscript.txt

# Запуск со скриптом
./vfs_terminal --vfs-path ./test_vfs --script myscript.txt
```

### Пример конфигурационного файла (config.toml):

```toml
# Конфигурация VFS Terminal
vfs_path = "./my_vfs"
script_path = "./config/scripts/startup.txt"

# Дополнительные настройки
log_level = "info"
auto_create_dirs = true
```

### Пример тестового скрипта:

```bash
# test_vfs.txt - автоматическое тестирование функциональности
echo "=== VFS Testing ==="
echo "Loading VFS from: ./test_vfs"

echo "Current directory:"
pwd

echo "Listing root:"
ls /

echo "Changing to folder1:"
cd folder1
ls

echo "Changing to subfolder:"
cd ../folder2/subfolder
ls

echo "Reading files:"
cat ../file2.txt
cat file3.txt

echo "Testing error handling:"
cd /non_existent_folder
cat non_existent_file.txt

echo "=== VFS Test Complete ==="
```

### Поддерживаемые команды:

| Команда | Описание | Пример использования |
|---------|-----------|---------------------|
| `ls [path]` | Листинг директории | `ls /folder1` |
| `cd <path>` | Смена директории | `cd /folder1/subfolder` |
| `cat <file>` | Чтение файла | `cat document.txt` |
| `pwd` | Текущая директория | `pwd` |
| `echo <text>` | Вывод текста | `echo "Hello World"` |
| `help` | Справка по командам | `help` |
| `exit [code]` | Выход из терминала | `exit 0` |

### Обработка ошибок:

Приложение корректно обрабатывает различные ошибки:
- Несуществующие файлы и директории
- Некорректные пути
- Ошибки чтения конфигурационных файлов
- Проблемы с загрузкой VFS
- Некорректные аргументы команд

Для получения дополнительной информации используйте команду `help` внутри приложения или параметр `--help` при запуске.