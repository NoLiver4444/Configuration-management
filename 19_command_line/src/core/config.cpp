#include "config.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>

namespace fs = filesystem;

Config::Config() : vfs_path("./vfs"), script_path(""), config_path("") {}

void Config::parse_command_line(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--vfs-path") == 0 || strcmp(argv[i], "-v") == 0) {
            if (i + 1 < argc) {
                vfs_path = argv[++i];
            }
        } else if (strcmp(argv[i], "--script") == 0 || strcmp(argv[i], "-s") == 0) {
            if (i + 1 < argc) {
                script_path = argv[++i];
            }
        } else if (strcmp(argv[i], "--config") == 0 || strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                config_path = argv[++i];
            }
        } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            cout << "Usage: " << argv[0] << " [options]\n"
                      << "Options:\n"
                      << "  -v, --vfs-path PATH   Set VFS physical path\n"
                      << "  -s, --script PATH     Set startup script path\n"
                      << "  -c, --config PATH     Set config file path\n"
                      << "  -h, --help            Show this help message\n";
            exit(0);
        }
    }
    
    if (!config_path.empty()) {
        parse_config_file();
    }
}

void Config::parse_config_file() {
    ifstream file(config_path);
    if (!file.is_open()) {
        cerr << "Error: Cannot open config file: " << config_path << "\n";
        return;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        size_t equals_pos = line.find('=');
        if (equals_pos != string::npos) {
            string key = line.substr(0, equals_pos);
            string value = line.substr(equals_pos + 1);
            
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            
            config_values[key] = value;
        }
    }
    
    file.close();
    
    if (vfs_path == "./vfs" && config_values.find("vfs_path") != config_values.end()) {
        vfs_path = config_values["vfs_path"];
    }
    if (script_path.empty() && config_values.find("script_path") != config_values.end()) {
        script_path = config_values["script_path"];
    }
}

void Config::print_config() const {
    cout << "=== Configuration ===\n";
    cout << "VFS Path: " << vfs_path << "\n";
    cout << "Script Path: " << (script_path.empty() ? "Not set" : script_path) << "\n";
    cout << "Config Path: " << (config_path.empty() ? "Not set" : config_path) << "\n";
    cout << "=====================\n";
}

void Config::create_vfs_directory() const {
    if (!vfs_path.empty()) {
        try {
            if (!fs::exists(vfs_path)) {
                fs::create_directories(vfs_path);
                cout << "Created VFS directory: " << vfs_path << "\n";
            }
        } catch (const exception& e) {
            cerr << "Error creating VFS directory: " << e.what() << "\n";
        }
    }
}

bool Config::config_file_exists() const {
    return !config_path.empty() && fs::exists(config_path);
}

bool Config::script_file_exists() const {
    return !script_path.empty() && fs::exists(script_path);
}