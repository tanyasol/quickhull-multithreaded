#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include "Error.hpp"

class ThreadPool {
private:
    std::atomic<bool> done;
    std::queue<std::function<void()>> workQueue;
    std::mutex queueMutex;
    std::condition_variable queueCondition;
    std::condition_variable waitCondition;
    std::vector<std::thread> threads;
    std::atomic<int> activeTasks;
    
    void worker();
    
public:
    ThreadPool();
    ThreadPool(int numThreads);
    ~ThreadPool();
    
    void submit(std::function<void()> task);
    void wait();
    
    int size() const;
    int getActiveTasks() const;
};

#endif