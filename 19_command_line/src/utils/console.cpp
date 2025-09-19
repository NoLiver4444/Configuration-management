#include "console.h"
#include "../core/commandline.h"
#include <fstream>
#include <iostream>

using namespace std;

void execute_script(const std::string& script_path, VFSManager& vfs) {
    ifstream script_file(script_path);
    if (!script_file.is_open()) {
        cerr << "Error: Cannot open script file: " << script_path << endl;
        return;
    }
    
    // Передаем VFSManager в CommandLine
    CommandLine command_line(vfs);
    string line;
    
    cout << "=== Executing script: " << script_path << " ===" << endl;
    
    while (getline(script_file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        cout << command_line.get_prompt() << " " << line << endl;
        
        command_line.parser(line);
        command_line.check_command();
    }
    
    script_file.close();
    cout << "=== Script execution completed ===" << endl;
}

void terminal_display(VFSManager& vfs) {
    // Передаем VFSManager в CommandLine
    CommandLine command_line(vfs);
    string command;
    
    cout << "Terminal (interactive mode):" << endl;
    
    while (true) {
        cout << command_line.get_prompt() << " ";
        getline(cin, command);
        
        command_line.parser(command);
        command_line.check_command();
    }
}