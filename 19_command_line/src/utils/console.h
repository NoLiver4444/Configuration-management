#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include "../core/vfs_manager.h"

// Объявляем forward declaration чтобы избежать circular includes
class CommandLine;

void terminal_display(VFSManager& vfs);
void execute_script(const std::string& script_path, VFSManager& vfs);

#endif