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