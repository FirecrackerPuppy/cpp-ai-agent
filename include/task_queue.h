#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <future>
#include <string>
#include "tool.h"
#include "thread_pool.h"

class TaskQueue {
private:
    ThreadPool& pool;

public:
    explicit TaskQueue(ThreadPool& pool);

    std::future<std::string> submit(Tool* tool, const std::string& input);
};

#endif