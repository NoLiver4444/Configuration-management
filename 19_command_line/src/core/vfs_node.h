#ifndef VFS_NODE_H
#define VFS_NODE_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

using namespace std;

enum class NodeType { FILE, DIRECTORY };

class VFSNode {
private:
    string name;
    NodeType type;
    string content;
    unordered_map<string, shared_ptr<VFSNode>> children;
    
public:
    VFSNode(const string& name, NodeType type);
    
    void add_child(shared_ptr<VFSNode> child);
    shared_ptr<VFSNode> get_child(const string& name) const;
    const unordered_map<string, shared_ptr<VFSNode>>& get_children() const;
    
    void set_content(const string& content);
    const string& get_content() const;
    
    string get_name() const;
    NodeType get_type() const;
    bool is_directory() const;
    bool is_file() const;
};

#endif