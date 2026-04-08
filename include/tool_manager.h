#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include <string>
#include <unordered_map>
#include <memory>
#include "tool.h"

class ToolManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Tool>> tools;

public:
    void registerTool(std::unique_ptr<Tool> tool);

    Tool* getTool(const std::string& name);
};

#endif