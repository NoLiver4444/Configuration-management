#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>

#include "../main.h"

class Config {
 private:
  string vfs_path;
  string script_path;
  string config_path;
  std::map<std::string, std::string> config_values;

 public:
  Config();
  void parse_command_line(int argc, char* argv[]);
  void parse_config_file();
  void print_config() const;

  // Геттеры
  std::string get_vfs_path() const { return vfs_path; }
  std::string get_script_path() const { return script_path; }
  std::string get_config_path() const { return config_path; }

  // Проверка существования файлов
  bool config_file_exists() const;
  bool script_file_exists() const;
};

#endif