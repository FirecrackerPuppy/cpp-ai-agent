#include "echo_tool.h"
#include <string>

std::string EchoTool::name() const {
    return "echo";
}

std::string EchoTool::run(const std::string& input) {
    return "Echo: " + input;
}