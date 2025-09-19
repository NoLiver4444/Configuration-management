#include "vfs_manager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = filesystem;

VFSManager::VFSManager() {
    root = make_shared<VFSNode>("/", NodeType::DIRECTORY);
    current_dir = root;
}

bool VFSManager::load_from_disk(const std::string& source_path) {
    this->source_path = source_path;
    
    if (!fs::exists(source_path)) {
        std::cerr << "Source directory does not exist: " << source_path << "\n";
        return false;
    }
    
    try {
        load_directory(source_path, root);
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error loading VFS: " << e.what() << "\n";
        return false;
    }
}

void VFSManager::load_directory(const string& disk_path, shared_ptr<VFSNode> vfs_node) {
    for (const auto& entry : fs::directory_iterator(disk_path)) {
        string name = entry.path().filename().string();
        
        if (entry.is_directory()) {
            auto dir_node = make_shared<VFSNode>(name, NodeType::DIRECTORY);
            vfs_node->add_child(dir_node);
            load_directory(entry.path().string(), dir_node);
        } else if (entry.is_regular_file()) {
            auto file_node = make_shared<VFSNode>(name, NodeType::FILE);
            
            ifstream file(entry.path().string());
            stringstream buffer;
            buffer << file.rdbuf();
            file_node->set_content(buffer.str());
            
            vfs_node->add_child(file_node);
        }
    }
}

bool VFSManager::change_directory(const string& path) {
    auto target_dir = get_node(path);
    if (target_dir && target_dir->is_directory()) {
        current_dir = target_dir;
        return true;
    }
    return false;
}

std::string VFSManager::get_current_path() const {
    if (current_dir == root) return "/";
    
    // Простая реализация - возвращаем имя текущей директории
    return current_dir->get_name();
}

std::string VFSManager::list_directory(const std::string& path) const {
    std::shared_ptr<VFSNode> target_dir;
    
    if (path.empty()) {
        target_dir = current_dir;  // ← Должен использовать current_dir!
    } else {
        target_dir = get_node(path);
        if (!target_dir) {
            return "Directory not found: " + path;
        }
        if (!target_dir->is_directory()) {
            return "Not a directory: " + path;
        }
    }
    
    std::string result;
    for (const auto& [name, node] : target_dir->get_children()) {
        result += (node->is_directory() ? "📁 " : "📄 ") + name + "\n";
    }
    
    return result;
}

bool VFSManager::file_exists(const string& path) const {
    return get_node(path) != nullptr;
}

string VFSManager::read_file(const string& path) const {
    auto node = get_node(path);
    if (node && node->is_file()) {
        return node->get_content();
    }
    return "File not found: " + path;
}

std::shared_ptr<VFSNode> VFSManager::get_node(const std::string& path) const {
    if (path.empty() || path == "/") {
        return root;
    }
    
    // Обработка относительных путей
    if (path[0] != '/') {
        // Относительный путь - начинаем с текущей директории
        return get_relative_node(path);
    }
    
    // Абсолютный путь
    std::string clean_path = path.substr(1);
    auto path_parts = split_path(clean_path);
    std::shared_ptr<VFSNode> current = root;
    
    for (const auto& part : path_parts) {
        if (part.empty() || part == ".") continue;
        if (part == "..") {
            // Упрощенно - всегда возвращаемся в корень
            current = root;
            continue;
        }
        
        current = current->get_child(part);
        if (!current) return nullptr;
    }
    
    return current;
}

std::shared_ptr<VFSNode> VFSManager::get_relative_node(const std::string& path) const {
    auto path_parts = split_path(path);
    std::shared_ptr<VFSNode> current = current_dir;
    
    for (const auto& part : path_parts) {
        if (part.empty() || part == ".") continue;
        if (part == "..") {
            // Упрощенно - всегда возвращаемся в корень
            current = root;
            continue;
        }
        
        current = current->get_child(part);
        if (!current) return nullptr;
    }
    
    return current;
}

vector<string> VFSManager::split_path(const string& path) const {
    vector<string> parts;
    stringstream ss(path);
    string part;
    
    while (getline(ss, part, '/')) {
        if (!part.empty()) {
            parts.push_back(part);
        }
    }
    
    return parts;
}