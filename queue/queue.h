#pragma once

#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <optional>

class MPMCUnboundedQueue {
public:
    MPMCUnboundedQueue() = default;

    void AddTask(std::function<void()> &&task);

    std::optional<std::function<void()>> TakeTask();

    void Close();

private:
    std::atomic<bool> is_closed_ = false;
    std::condition_variable cond_;
    std::mutex mutex_;
    std::queue<std::function<void()>> queue_;
};
