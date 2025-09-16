#include "console.h"

void terminal_display() {
  string prompt = get_terminal_prompt();
  string command;

  cout << "Terminal:\n";

  while (1) {
    cout << prompt << " ";
    cin >> command;
  }
}

string get_terminal_prompt() {
  std::string prompt;

  // Получаем имя пользователя
  uid_t uid = geteuid();
  struct passwd *pw = getpwuid(uid);
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
    std::string home_dir = pw ? pw->pw_dir : "";
    std::string current_dir = cwd;

    if (!home_dir.empty() && current_dir.find(home_dir) == 0) {
      current_dir = "~" + current_dir.substr(home_dir.length());
    }

    prompt += current_dir;
  }

  // Добавляем символ привилегий
  prompt += (uid == 0) ? "#" : "$";

  return prompt;
}