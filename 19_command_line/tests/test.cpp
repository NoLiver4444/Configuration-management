#include "test.h"

std::string execCommand(const char* cmd) {
  char buffer[128];
  std::string result = "";
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
    result += buffer;
  }

  return result;
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

TEST(TerminalTest, ComparePromptWithCommandOutput) {
  // Получаем вывод из кода
  std::string codeOutput = get_terminal_prompt();

  // Получаем вывод из терминальной команды (замените на вашу реальную команду)
  std::string terminalOutput = execCommand("echo 'user@hostname:~$ '");

  // Убираем возможные символы новой строки
  terminalOutput.erase(
      std::remove(terminalOutput.begin(), terminalOutput.end(), '\n'),
      terminalOutput.end());

  // Сравниваем результаты
  EXPECT_EQ(codeOutput, terminalOutput);
}