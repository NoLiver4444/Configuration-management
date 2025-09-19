#include "core/config.h"
#include "core/commandline.h"
#include "utils/console.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Config config;
    config.parse_command_line(argc, argv);
    config.print_config();
    
    config.create_vfs_directory();
    
    // Сначала создаем и загружаем VFSManager
    VFSManager vfs;
    if (!config.get_vfs_path().empty()) {
        vfs.load_from_disk(config.get_vfs_path());
    }
    
    // Выполняем скрипт если указан (передаем vfs)
    if (config.script_file_exists()) {
        execute_script(config.get_script_path(), vfs);
    } else if (!config.get_script_path().empty()) {
        cerr << "Error: Script file not found: " << config.get_script_path() << "\n";
        return 1;
    }
    
    // Запускаем интерактивный режим (передаем vfs)
    terminal_display(vfs);
    return 0;
}