#include "console.h"

void terminal_display() {
  CommandLine command_line;
  string command;

  bool work = 1;

  cout << "Terminal:\n";

  while (work) {
    cout << command_line.get_prompt() << " ";
    getline(cin, command);

    command_line.parser(command);
    command_line.check_command();
  }
}

void execute_script(const std::string& script_path) {
  std::ifstream script_file(script_path);
  if (!script_file.is_open()) {
    std::cerr << "Error: Cannot open script file: " << script_path << "\n";
    return;
  }

  CommandLine command_line;
  std::string line;

  std::cout << "=== Executing script: " << script_path << " ===\n";

  while (std::getline(script_file, line)) {
    // Пропускаем пустые строки и комментарии
    if (line.empty() || line[0] == '#') continue;

    std::cout << command_line.get_prompt() << " " << line << "\n";

    command_line.parser(line);
    command_line.check_command();

    // Останавливаемся при первой ошибке
    if (command_line.get_tokens().size() > 0) {
      std::string command = command_line.get_tokens()[0];
      if (command != "echo" && command != "help") {
        // Здесь можно добавить проверку на ошибки выполнения
      }
    }
  }

  script_file.close();
  std::cout << "=== Script execution completed ===\n";
}