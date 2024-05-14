#include "thread_pool/thread_pool.h"

#include <cstdio>

int main() {
    ThreadPool pool(3);

    for (size_t i = 0; i < 10; ++i) {
        pool.AddTask([i] {
            int num = 3;
            while (num--) {
                printf("Task %lu\n", i);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        });
    }
}
