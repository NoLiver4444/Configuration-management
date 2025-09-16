#include "console.h"

void terminal_display() {
  string prompt = get_terminal_prompt();
  string command;
  vector<string> tokens;

  cout << "Terminal:\n";

  while (1) {
    cout << prompt << " ";
    cin >> command;
    tokens = parser(command);
  }
}