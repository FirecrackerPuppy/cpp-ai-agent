#include <iostream>
#include <string>
#include "agent.h"

int main() {
    Agent agent;

    std::cout << "Enter your request:\n";

    std::string input;
    std::getline(std::cin, input);

    std::string result = agent.run(input);

    std::cout << "Final Result:\n" << result << std::endl;

    return 0;
}