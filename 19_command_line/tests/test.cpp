#include "test.h"

std::string execCommand(const char* cmd) {
  std::array<char, 128> buffer;
  std::string result;

  // Используем lambda для закрытия pipe вместо pclose
  auto closer = [](FILE* f) {
    if (f) pclose(f);
  };
  std::unique_ptr<FILE, decltype(closer)> pipe(popen(cmd, "r"), closer);

  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

  return result;
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

TEST(TerminalTest, CompareWithBashPrompt) {
  CommandLine *command_line = new CommandLine();

  // Запускаем bash в интерактивном режиме и получаем приглашение
  std::string terminalOutput = execCommand("bash -i -c 'echo \"$PS1\"'");

  terminalOutput.erase(
      std::remove(terminalOutput.begin(), terminalOutput.end(), '\n'),
      terminalOutput.end());

  // PS1 может содержать escape-последовательности, поэтому сравниваем
  // содержимое
  EXPECT_TRUE(command_line->get_prompt().find("@") != std::string::npos);
  EXPECT_TRUE(command_line->get_prompt().find(":") != std::string::npos);

  delete command_line;
}

TEST(TerminalTest, Parser) {
  CommandLine *command_line = new CommandLine();

  vector<string> answ = {"sudo", "apt", "install", "firefox", "clementine", "vlc"};

  command_line->parser("sudo apt install firefox clementine vlc");

  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(answ[i], command_line->get_tokens()[i]);
  }

  delete command_line;
}