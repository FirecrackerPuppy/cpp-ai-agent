#include "file_tool.h"
#include <fstream>
#include <sstream>
#include <string>

std::string FileTool::name() const {
    return "read_file";
}

std::string FileTool::run(const std::string& input) {
    std::ifstream file(input);

    if (!file.is_open()) {
        return "Error: cannot open file";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}