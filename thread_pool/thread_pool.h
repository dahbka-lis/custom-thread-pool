#pragma once

#include "../queue/queue.h"

#include <cstdint>
#include <vector>
#include <thread>

class ThreadPool {
public:
    explicit ThreadPool(std::uint32_t worker_cnt);

    void AddTask(std::function<void()> &&task);

    ~ThreadPool();

private:
    std::vector<std::thread> workers_;
    MPMCUnboundedQueue queue_;
};
