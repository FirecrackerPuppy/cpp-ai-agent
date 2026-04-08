#ifndef LLM_CLIENT_H
#define LLM_CLIENT_H

#include <string>

class LLMClient {
public:
    std::string call(const std::string& prompt);
};

#endif