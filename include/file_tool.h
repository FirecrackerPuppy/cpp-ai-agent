#ifndef FILE_TOOL_H
#define FILE_TOOL_H

#include <string>
#include "tool.h"

class FileTool : public Tool {
public:
    std::string name() const override;
    std::string run(const std::string& input) override;
};

#endif