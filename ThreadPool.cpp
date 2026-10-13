#include "ThreadPool.hpp"

void ThreadPool::worker() {
    while (!done) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            queueCondition.wait(lock, [this] { return !workQueue.empty() || done; });
            
            if (done && workQueue.empty()) {
                return;
            }
            
            if (!workQueue.empty()) {
                task = workQueue.front();
                workQueue.pop();
            }
        }
        
        if (task) {
            activeTasks++;
            task();
            activeTasks--;
            
            if (activeTasks == 0 && workQueue.empty()) {
                waitCondition.notify_one();
            }
        }
    }
}

ThreadPool::ThreadPool() : done(false), activeTasks(0) {
    size_t const threadCount = std::thread::hardware_concurrency();
    if (threadCount == 0) {
        throw ThreadError("Failed to detect hardware concurrency");
    }
    
    try {
        for (int i = 0; i < (int)threadCount; i++) {
            threads.emplace_back(&ThreadPool::worker, this);
        }
    }
    catch (...) {
        done = true;
        throw;
    }
}

ThreadPool::ThreadPool(int numThreads) : done(false), activeTasks(0) {
    try {
        for (int i = 0; i < (int)numThreads; i++) {
            threads.emplace_back(&ThreadPool::worker, this);
        }
    }
    catch (const std::exception& e) {
        throw ThreadError("Failed to create thread");
    }
}

ThreadPool::~ThreadPool() {
    done = true;
    queueCondition.notify_all();
    
    for (unsigned int i = 0; i < (unsigned int)threads.size(); i++) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }
}

void ThreadPool::submit(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        workQueue.push(task);
    }
    queueCondition.notify_one();
}

void ThreadPool::wait() {
    std::unique_lock<std::mutex> lock(queueMutex);
    waitCondition.wait(lock, [this] { 
        return workQueue.empty() && activeTasks == 0; 
    });
}

int ThreadPool::size() const {
    return (int)threads.size();
}

int ThreadPool::getActiveTasks() const {
    return activeTasks.load();
}