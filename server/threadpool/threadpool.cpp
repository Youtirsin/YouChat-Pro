#include "threadpool.h"


ThreadPool::ThreadPool(size_t threadCount): pool_(std::make_shared<Pool>()) {
    for(size_t i = 0; i < threadCount; i++) {
        std::thread([pool = pool_] {
            std::unique_lock<std::mutex> locker(pool->mtx);
            while(true) {
                if(!pool->tasks.empty()) {
                    auto task = std::move(pool->tasks.front());
                    pool->tasks.pop();
                    locker.unlock();
                    task();
                    locker.lock();
                } 
                else if(pool->isClosed) break;
                else pool->cond.wait(locker);
            }
        }).detach();
    }
}


ThreadPool::~ThreadPool() {
    if(static_cast<bool>(pool_)) {
        {
            std::lock_guard<std::mutex> locker(pool_->mtx);
            pool_->isClosed = true;
        }
        pool_->cond.notify_all();
    }
}
