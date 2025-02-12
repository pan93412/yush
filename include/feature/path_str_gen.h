#ifndef FEATURE_PATH_STR_GEN_H
#define FEATURE_PATH_STR_GEN_H

#include <iostream>
#include <filesystem>

std::string path_str_gen(std::string_view home_dir) {
    std::string pwd = std::filesystem::current_path().lexically_normal().string();
    if (pwd.substr(0, home_dir.size()) == home_dir) {
        return std::string("~") + std::string(pwd.substr(home_dir.size(), std::string_view::npos));
    } else {
        return std::string(pwd);
    }
}

#endif
