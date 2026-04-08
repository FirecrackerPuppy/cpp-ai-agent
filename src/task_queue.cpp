#include "task_queue.h"

TaskQueue::TaskQueue(ThreadPool& pool) : pool(pool) {}

std::future<std::string> TaskQueue::submit(Tool* tool, const std::string& input) {
    return pool.enqueue([tool, input]() {
        return tool->run(input);
    });
}