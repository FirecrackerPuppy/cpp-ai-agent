#include "shell_tool.h"
#include <cstdlib>
#include <string>

std::string ShellTool::name() const {
    return "run_shell";
}

std::string ShellTool::run(const std::string& input) {
    int ret = std::system(input.c_str());

    if (ret == 0) {
        return "Shell command executed successfully";
    }

    return "Shell command failed with code: " + std::to_string(ret);
}