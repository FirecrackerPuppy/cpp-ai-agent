#include "memory.h"
#include <sstream>

void Memory::add(const std::string& entry) {
    history.push_back(entry);
}

std::string Memory::getContext() const {
    std::stringstream ss;
    for (const auto& item : history) {
        ss << item << "\n";
    }
    return ss.str();
}