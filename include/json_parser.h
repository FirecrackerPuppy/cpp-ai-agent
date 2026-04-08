#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>

struct Action {
    std::string name;
    std::string input;
    bool valid = false;
};

class JsonParser {
public:
    static Action parse(const std::string& jsonStr);
};

#endif