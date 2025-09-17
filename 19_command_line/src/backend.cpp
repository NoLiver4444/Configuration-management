#include "backend.h"

CommandLine::CommandLine() {
  get_terminal_prompt();
  tokens.clear();
  commands["help"] = [this](const auto& args) { help_command(args); };
  commands["echo"] = [this](const auto& args) { echo_command(args); };
  commands["exit"] = [this](const auto& args) { exit_command(args); };
  commands["ls"] = [this](const auto& args) { ls_command(args); };
  commands["cd"] = [this](const auto& args) { cd_command(args); };
}

// Получение строки приглашения терминала
void CommandLine::get_terminal_prompt() {
  // Получаем имя пользователя
  uid_t uid = geteuid();
  struct passwd* pw = getpwuid(uid);
  if (pw) {
    prompt += pw->pw_name;
    prompt += "@";
  }

  // Получаем имя хоста
  char hostname[HOST_NAME_MAX];
  if (gethostname(hostname, HOST_NAME_MAX) == 0) {
    prompt += hostname;
    prompt += ":";
  }

  // Получаем текущую директорию
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != nullptr) {
    // Сокращаем домашнюю директорию до ~
    string home_dir = pw ? pw->pw_dir : "";
    string current_dir = cwd;

    if (!home_dir.empty() && current_dir.find(home_dir) == 0) {
      current_dir = "~" + current_dir.substr(home_dir.length());
    }

    prompt += current_dir;
  }

  // Добавляем символ привилегий
  prompt += (uid == 0) ? "#" : "$";
}

// Деление строки на пробелы
void CommandLine::parser(string command) {
  tokens.clear();

  istringstream stream(command);
  string token;

  while (stream >> token) {
    tokens.push_back(token);
  }
}

void CommandLine::check_command() {
  std::vector<std::string> args(tokens.begin() + 1, tokens.end());

  if (commands.find(tokens[0]) != commands.end()) {
    commands[tokens[0]](args);
  } else {
    cout << "Unknown command: " << tokens[0] << "\n";
  }
}

void CommandLine::help_command(const vector<string>& args) {
  cout << " ls [опции] [файлы и каталоги]\n";
  cout << " echo [-neE] [аргумент ...]\n";
  cout << " cd [-L|[-P [-e]] [-@]] [каталог]\n";
  cout << " exit [n]\n";
  cout << " help [-dms] [шаблон ...]\n";
}

void CommandLine::echo_command(const vector<string>& args) {
  for (const auto& arg : args) {
    cout << arg << " ";
  }
  cout << "\n";
}

void CommandLine::exit_command(const vector<string>& args) { exit(0); }

void CommandLine::ls_command(const vector<string>& args) {
  for (const auto& arg : args) {
    cout << arg << " ";
  }
  cout << "\n";
}

void CommandLine::cd_command(const vector<string>& args) {
  for (const auto& arg : args) {
    cout << arg << " ";
  }
  cout << "\n";
}

string CommandLine::get_prompt() { return prompt; }

vector<string> CommandLine::get_tokens() { return tokens; }