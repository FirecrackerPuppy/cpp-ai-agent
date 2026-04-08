#ifndef SHELL_TOOL_H
#define SHELL_TOOL_H

#include <string>
#include "tool.h"

class ShellTool : public Tool {
public:
    std::string name() const override;
    std::string run(const std::string& input) override;
};

#endif