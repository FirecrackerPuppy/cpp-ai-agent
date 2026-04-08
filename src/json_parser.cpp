#include "json_parser.h"

Action JsonParser::parse(const std::string& jsonStr) {
    Action action;

    size_t actionKeyPos = jsonStr.find("\"action\"");
    size_t inputKeyPos = jsonStr.find("\"input\"");

    if (actionKeyPos == std::string::npos || inputKeyPos == std::string::npos) {
        return action;
    }

    size_t actionColon = jsonStr.find(":", actionKeyPos);
    size_t actionQuote1 = jsonStr.find("\"", actionColon);
    size_t actionQuote2 = jsonStr.find("\"", actionQuote1 + 1);

    if (actionColon == std::string::npos || actionQuote1 == std::string::npos || actionQuote2 == std::string::npos) {
        return action;
    }

    action.name = jsonStr.substr(actionQuote1 + 1, actionQuote2 - actionQuote1 - 1);

    size_t inputColon = jsonStr.find(":", inputKeyPos);
    size_t inputQuote1 = jsonStr.find("\"", inputColon);
    size_t inputQuote2 = jsonStr.find("\"", inputQuote1 + 1);

    if (inputColon == std::string::npos || inputQuote1 == std::string::npos || inputQuote2 == std::string::npos) {
        return action;
    }

    action.input = jsonStr.substr(inputQuote1 + 1, inputQuote2 - inputQuote1 - 1);
    action.valid = true;

    return action;
}