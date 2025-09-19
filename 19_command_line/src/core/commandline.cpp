#include "commandline.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>

using namespace std;

CommandLine::CommandLine(VFSManager& vfs_ref) : vfs(vfs_ref) {
    get_terminal_prompt();
    tokens.clear();
    commands["help"] = [this](const auto& args) { help_command(args); };
    commands["echo"] = [this](const auto& args) { echo_command(args); };
    commands["exit"] = [this](const auto& args) { exit_command(args); };
    commands["ls"] = [this](const auto& args) { ls_command(args); };
    commands["cd"] = [this](const auto& args) { cd_command(args); };
    commands["cat"] = [this](const auto& args) { cat_command(args); };
    commands["pwd"] = [this](const auto& args) { pwd_command(args); };
}

void CommandLine::get_terminal_prompt() {
    prompt.clear();
    
    uid_t uid = geteuid();
    struct passwd* pw = getpwuid(uid);
    if (pw) {
        prompt += pw->pw_name;
        prompt += "@";
    }

    char hostname[HOST_NAME_MAX];
    if (gethostname(hostname, HOST_NAME_MAX) == 0) {
        prompt += hostname;
        prompt += ":";
    }

    // Используем VFS путь вместо реального
    prompt += vfs.get_current_path();

    prompt += (uid == 0) ? "#" : "$";
}

void CommandLine::parser(string command) {
    tokens.clear();
    istringstream stream(command);
    string token;

    while (stream >> token) {
        tokens.push_back(token);
    }
}

void CommandLine::check_command() {
    if (tokens.empty()) return;
    
    vector<string> args(tokens.begin() + 1, tokens.end());

    if (commands.find(tokens[0]) != commands.end()) {
        commands[tokens[0]](args);
    } else {
        cout << "Unknown command: " << tokens[0] << "\n";
    }
}

void CommandLine::set_vfs_path(const string& path) {
    if (!vfs.load_from_disk(path)) {
        cout << "Failed to load VFS from: " << path << "\n";
    }
}

// Реализации команд
void CommandLine::help_command(const vector<string>& args) {
    cout << "Available commands:\n";
    cout << "  ls [path]        - List directory contents\n";
    cout << "  cd [path]        - Change directory\n";
    cout << "  cat [file]       - Display file content\n";
    cout << "  pwd              - Print working directory\n";
    cout << "  echo [text]      - Display text\n";
    cout << "  exit [code]      - Exit terminal\n";
    cout << "  help             - Show this help\n";
}

void CommandLine::echo_command(const vector<string>& args) {
    for (const auto& arg : args) {
        cout << arg << " ";
    }
    cout << "\n";
}

void CommandLine::exit_command(const vector<string>& args) {
    int exit_code = 0;
    if (!args.empty()) {
        try {
            exit_code = stoi(args[0]);
        } catch (...) {
            cout << "Invalid exit code: " << args[0] << "\n";
            exit_code = 1;
        }
    }
    exit(exit_code);
}

void CommandLine::ls_command(const std::vector<std::string>& args) {
    std::string path;
    if (args.empty()) {
        path = "";  // Будет использовать текущую директорию
    } else {
        path = args[0];
    }
    
    std::string result = vfs.list_directory(path);
    
    if (!result.empty()) {
        std::cout << result;
    }
}

void CommandLine::cd_command(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "Usage: cd <directory>\n";
        return;
    }
    
    if (vfs.change_directory(args[0])) {
        std::cout << "Changed directory to: " << args[0] << "\n";
        // Обновляем prompt после смены директории
        get_terminal_prompt();
    } else {
        std::cout << "Directory not found: " << args[0] << "\n";
    }
}

void CommandLine::cat_command(const vector<string>& args) {
    if (args.empty()) {
        cout << "Usage: cat <file>\n";
        return;
    }
    
    cout << vfs.read_file(args[0]) << "\n";
}

void CommandLine::pwd_command(const vector<string>& args) {
    cout << vfs.get_current_path() << "\n";
}

string CommandLine::get_prompt() const { return prompt; }
vector<string> CommandLine::get_tokens() const { return tokens; }