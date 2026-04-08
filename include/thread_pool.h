#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;

public:
    explicit ThreadPool(size_t numThreads = 4);
    ~ThreadPool();

    template <class F>
    auto enqueue(F&& f) -> std::future<decltype(f())> {
        using ReturnType = decltype(f());

        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::forward<F>(f)
        );

        std::future<ReturnType> res = task->get_future();

        {
            std::unique_lock<std::mutex> lock(queueMutex);

            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            tasks.emplace([task]() {
                (*task)();
            });
        }

        condition.notify_one();
        return res;
    }
};

#endif