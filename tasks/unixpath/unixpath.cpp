#include "unixpath.h"

#include <vector>

std::vector<std::string_view> SplitPath(std::string_view path) {
    std::vector<std::string_view> answer = {};
    const char* current_start = path.begin();
    for (auto curr = path.begin(); curr < path.end(); ++curr) {
        if (*curr == '/') {
            if (current_start != path.end() && current_start != curr) {
                answer.push_back({current_start, curr});
            }
            current_start = path.end();
        } else if (current_start == path.end()) {
            current_start = curr;
        }
    }
    if (current_start != path.end()) {
        answer.push_back({current_start, path.end()});
    }
    return answer;
}

bool IsAbsolutePath(std::string_view path) {
    if (!path.empty() && path[0] == '/') {
        return true;
    }
    return false;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::vector<std::string_view> good_nodes =
        IsAbsolutePath(path) ? std::vector<std::string_view>{} : SplitPath(current_working_dir);
    std::vector<std::string_view> relative_nodes = SplitPath(path);
    for (auto node : relative_nodes) {
        if (node == "..") {
            if (!good_nodes.empty()) {
                good_nodes.pop_back();
            }
        } else if (node != ".") {
            good_nodes.push_back(node);
        }
    }
    std::string final_path;
    for (auto node : good_nodes) {
        final_path += "/";
        final_path += node;
    }
    if (final_path.empty()) {
        final_path += "/";
    }
    return final_path;
}
