#include "tr_pool.h"

ThreadPool::ThreadPool(int num) : stop(false) {
    for (int i = 0; i < num; i++) {
        threads.emplace_back([this] {
            while (true) {
                std::unique_lock<std::mutex> lock(mtx);
                condition.wait(lock, [this] {
                    return !tasks.empty() || stop;
                });
                if (stop && tasks.empty())
                    return;

                std::function<void()> task(std::move(tasks.front()));
                tasks.pop();
                lock.unlock();
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;
    }
    condition.notify_all();
    for (auto& t : threads) t.join();
}
