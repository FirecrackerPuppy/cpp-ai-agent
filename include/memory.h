#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <vector>

class Memory {
private:
    std::vector<std::string> history;

public:
    void add(const std::string& entry);
    std::string getContext() const;
};

#endif