#ifndef TOOL_H
#define TOOL_H

#include <string>

class Tool {
public:
    virtual ~Tool() = default;

    virtual std::string name() const = 0;
    virtual std::string run(const std::string& input) = 0;
};

#endif