#include "vfs_node.h"
#include <iostream>

using namespace std;

VFSNode::VFSNode(const string& name, NodeType type) 
    : name(name), type(type) {}

void VFSNode::add_child(shared_ptr<VFSNode> child) {
    
    children[child->get_name()] = child;

    for (const auto& [key, value] : children) {
        cout << key << " ";
    }
    cout << endl;
}

shared_ptr<VFSNode> VFSNode::get_child(const string& name) const {
    auto it = children.find(name);
    if (it != children.end()) {
        return it->second;
    }
    return nullptr;
}

const unordered_map<string, shared_ptr<VFSNode>>& VFSNode::get_children() const {
    for (const auto& [child_name, child_ptr] : children) {
        cout << child_name << "(" << (child_ptr ? "valid" : "NULL") << ") ";
    }
    cout << endl;
    return children;
}

void VFSNode::set_content(const string& content) {
    this->content = content;
}

const string& VFSNode::get_content() const {
    return content;
}

string VFSNode::get_name() const {
    return name;
}

NodeType VFSNode::get_type() const {
    return type;
}

bool VFSNode::is_directory() const {
    return type == NodeType::DIRECTORY;
}

bool VFSNode::is_file() const {
    return type == NodeType::FILE;
}