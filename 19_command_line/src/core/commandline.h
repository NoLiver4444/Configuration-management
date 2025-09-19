#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "vfs_manager.h"

using namespace std;

class CommandLine {
private:
    string prompt;
    vector<string> tokens;
    unordered_map<string, function<void(const vector<string>&)>> commands;
    VFSManager& vfs; 
    
    void get_terminal_prompt();
    
public:
    CommandLine(VFSManager& vfs_ref);
    
    void parser(string command);
    void check_command();
    string get_prompt() const;
    vector<string> get_tokens() const;
    void set_vfs_path(const string& path);
    
    // Команды
    void help_command(const vector<string>& args);
    void echo_command(const vector<string>& args);
    void exit_command(const vector<string>& args);
    void ls_command(const vector<string>& args);
    void cd_command(const vector<string>& args);
    void cat_command(const vector<string>& args);
    void pwd_command(const vector<string>& args);
};

#endif