#ifndef ECHO_TOOL_H
#define ECHO_TOOL_H

#include <string>
#include "tool.h"

class EchoTool : public Tool {
public:
    std::string name() const override;
    std::string run(const std::string& input) override;
};

#endif