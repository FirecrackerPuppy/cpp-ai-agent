#ifndef AGENT_H
#define AGENT_H

#include <string>
#include "tool_manager.h"
#include "memory.h"
#include "thread_pool.h"
#include "task_queue.h"

class Agent {
private:
    ToolManager manager;
    Memory memory;
    ThreadPool pool;
    TaskQueue taskQueue;
    int maxSteps;

public:
    Agent(int maxSteps = 3, int numThreads = 4);

    std::string run(const std::string& userInput);
};

#endif