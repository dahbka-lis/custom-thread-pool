#include "thread_pool.h"

ThreadPool::ThreadPool(std::uint32_t worker_cnt) {
    for (std::uint32_t i = 0; i < worker_cnt; ++i) {
        workers_.emplace_back([this] {
            while (true) {
                auto task = queue_.TakeTask();
                if (task != std::nullopt) {
                    (*task)();
                } else {
                    return;
                }
            }
        });
    }
}

void ThreadPool::AddTask(std::function<void()> &&task) {
    queue_.AddTask(std::move(task));
}

ThreadPool::~ThreadPool() {
    queue_.Close();
    for (auto &worker : workers_) {
        worker.join();
    }
}
