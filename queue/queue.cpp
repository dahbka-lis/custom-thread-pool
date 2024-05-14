#include "queue.h"

void MPMCUnboundedQueue::AddTask(std::function<void()> &&task) {
    if (is_closed_.load()) {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(std::move(task));
    cond_.notify_one();
}

std::optional<std::function<void()>> MPMCUnboundedQueue::TakeTask() {
    std::unique_lock<std::mutex> lock(mutex_);

    if (is_closed_.load() && queue_.empty()) {
        return std::nullopt;
    }

    while (queue_.empty()) {
        cond_.wait(lock, [this] { return !queue_.empty(); });
    }

    auto task = std::move(queue_.front());
    queue_.pop();
    return task;
}

void MPMCUnboundedQueue::Close() {
    is_closed_.store(true);
}
