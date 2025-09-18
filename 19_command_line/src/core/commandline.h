#ifndef BACKEND_H_
#define BACKEND_H_

#include "../main.h"

class CommandLine {
 private:
  string prompt;
  vector<string> tokens;
  map<string, function<void(const vector<string>&)>> commands;

  void get_terminal_prompt();

  void help_command(const vector<string>& args);
  void echo_command(const vector<string>& args);
  void exit_command(const vector<string>& args);
  void ls_command(const vector<string>& args);
  void cd_command(const vector<string>& args);

 public:
  CommandLine();

  string get_prompt();
  vector<string> get_tokens();
  void check_command();
  void parser(string command);
};

#endif