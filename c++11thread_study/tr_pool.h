#ifndef TR_POOL_H
#define TR_POOL_H

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

class ThreadPool {
public:
    ThreadPool(int num = 1);
    ~ThreadPool();
    template <class F, class... Args>
    void enqueue(F&& f, Args&&... args) {  // 类模板成员函数不能定义在cpp文件中
        std::function<void()> task =
            std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(move(task));
        }
        condition.notify_one();
    }

private:
    std::mutex mtx;
    std::condition_variable condition;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;

    bool stop;
};

#endif