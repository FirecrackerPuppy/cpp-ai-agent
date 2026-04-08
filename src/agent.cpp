#include "agent.h"
#include "echo_tool.h"
#include "file_tool.h"
#include "shell_tool.h"
#include "json_parser.h"
#include <memory>
#include <string>
#include <iostream>

// 模拟 LLM
std::string fakeLLM(const std::string& userInput, const std::string& context, int step) {
    if (userInput == "bad") {
        if (step == 0 && context.empty()) {
            return "this is not json";
        }
        return "{\"action\":\"echo\",\"input\":\"Recovered after retry\"}";
    }

    if (step == 0) {
        if (userInput.find("file") != std::string::npos) {
            return "{\"action\":\"read_file\",\"input\":\"test.txt\"}";
        } else if (userInput.find("shell") != std::string::npos) {
            return "{\"action\":\"run_shell\",\"input\":\"dir\"}";
        } else {
            return "{\"action\":\"echo\",\"input\":\"" + userInput + "\"}";
        }
    }

    return "{\"action\":\"finish\",\"input\":\"done\"}";
}

Agent::Agent(int maxSteps, int numThreads)
    : pool(numThreads), taskQueue(pool), maxSteps(maxSteps) {
    manager.registerTool(std::make_unique<EchoTool>());
    manager.registerTool(std::make_unique<FileTool>());
    manager.registerTool(std::make_unique<ShellTool>());
}

std::string Agent::run(const std::string& userInput) {
    std::string lastAction = "";
    std::string finalResult;

    for (int step = 0; step < maxSteps; ++step) {
        std::string context = memory.getContext();

        std::string llmOutput = fakeLLM(userInput, context, step);

        Action action = JsonParser::parse(llmOutput);

        // 最小 retry：第一次解析失败，再试一次
        if (!action.valid) {
            std::cout << "[Retry] First parse failed, retrying once...\n";

            std::string retryOutput = fakeLLM(userInput, context, step);
            std::cout << "[Retry] Retry output:\n" << retryOutput << std::endl;

            action = JsonParser::parse(retryOutput);

            if (!action.valid) {
                std::cout << "[Fallback] Retry still failed, fallback to echo.\n";
                action.name = "echo";
                action.input = "Invalid LLM output after retry";
            }
        }

        if (action.name == "finish") {
            break;
        }

        std::string signature = action.name + ":" + action.input;
        if (signature == lastAction) {
            break;
        }
        lastAction = signature;

        Tool* tool = manager.getTool(action.name);
        if (!tool) {
            return "Tool not found";
        }

        auto future = taskQueue.submit(tool, action.input);
        std::string result = future.get();

        finalResult = result;

        memory.add("step=" + std::to_string(step));
        memory.add("action=" + action.name);
        memory.add("input=" + action.input);
        memory.add("result=" + result);
    }

    return finalResult;
}