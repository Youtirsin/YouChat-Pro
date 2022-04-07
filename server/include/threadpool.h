#pragma once


#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>


class ThreadPool {
public:
    explicit ThreadPool(size_t threadCount = 8);

    ThreadPool(ThreadPool&&) = default;
    
    ~ThreadPool();

    template<class F>
    void addTask(F&& task);

private:
    struct Pool {
        std::mutex mtx;
        std::condition_variable cond;
        bool isClosed;
        std::queue<std::function<void()>> tasks;
    };
    std::shared_ptr<Pool> pool_;
};

// template definition cant be in threadpool.cpp
template<class F>
void ThreadPool::addTask(F&& task) {
    {
        std::lock_guard<std::mutex> locker(pool_->mtx);
        pool_->tasks.emplace(std::forward<F>(task));
    }
    pool_->cond.notify_one();
}