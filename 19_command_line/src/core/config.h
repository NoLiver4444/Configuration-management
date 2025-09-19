#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

using namespace std;

class Config {
private:
    string vfs_path;
    string script_path;
    string config_path;
    map<string, string> config_values;
    
public:
    Config();
    void parse_command_line(int argc, char* argv[]);
    void parse_config_file();
    void print_config() const;
    void create_vfs_directory() const;
    
    string get_vfs_path() const { return vfs_path; }
    string get_script_path() const { return script_path; }
    string get_config_path() const { return config_path; }
    
    bool config_file_exists() const;
    bool script_file_exists() const;
};

#endif