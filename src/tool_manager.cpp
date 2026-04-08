#include "tool_manager.h"

void ToolManager::registerTool(std::unique_ptr<Tool> tool) {
    tools[tool->name()] = std::move(tool);
}

Tool* ToolManager::getTool(const std::string& name) {
    if (tools.find(name) != tools.end()) {
        return tools[name].get();
    }
    return nullptr;
}