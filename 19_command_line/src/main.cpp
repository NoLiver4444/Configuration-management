#include "main.h"

int main(int argc, char* argv[]) {
  Config config;
  config.parse_command_line(argc, argv);
  config.print_config();

  // Если указан скрипт - выполняем его
  if (config.script_file_exists()) {
    execute_script(config.get_script_path());
  } else if (!config.get_script_path().empty()) {
    std::cerr << "Error: Script file not found: " << config.get_script_path()
              << "\n";
    return 1;
  }

  terminal_display();
  return 0;
}