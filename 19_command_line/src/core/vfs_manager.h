#ifndef VFS_MANAGER_H
#define VFS_MANAGER_H

#include "vfs_node.h"
#include <string>
#include <memory>

using namespace std;

class VFSManager {
private:
    shared_ptr<VFSNode> root;
    shared_ptr<VFSNode> current_dir;
    string source_path;
    
public:
    VFSManager();
    
    bool load_from_disk(const string& source_path);
    bool change_directory(const string& path);
    string get_current_path() const;
    string list_directory(const string& path = "") const;
    bool file_exists(const string& path) const;
    string read_file(const string& path) const;
    shared_ptr<VFSNode> get_node(const string& path) const;
    shared_ptr<VFSNode> get_relative_node(const std::string& path) const;
    
private:
    void load_directory(const string& disk_path, shared_ptr<VFSNode> vfs_node);
    vector<string> split_path(const string& path) const;
};

#endif