/*
 * Mark Benjamin 13 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include "macros.h"

std::string simplify(std::string file_path, std::string base_path) {
    int prefix_length = 0;
    size_t loc;
    for (loc = 0; (loc = base_path.find('/', loc + 1)); prefix_length++) { }
    prefix_length++;
    std::vector<std::string> components;
    while ((loc = file_path.find_last_of('/'))) {
        if (!components.empty() && components.back() == std::string("..")) {
            components.pop_back();
        } else {
            components.push_back(file_path.substr(loc + 1, file_path.length()));
        }
        file_path = file_path.substr(0, loc);
    }
    components.push_back(file_path);
    file_path = "";
    while (!components.empty() && prefix_length > 0) {
        components.pop_back();
        prefix_length--;
    }
    while (!components.empty()) {
        file_path += components.back();
        components.pop_back();
        if (!components.empty()) {
            file_path += "/";
        }
    }
    return file_path;
}