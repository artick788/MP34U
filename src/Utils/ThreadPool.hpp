#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

class ThreadPool{
public:
    ThreadPool();

    ~ThreadPool();

    void addTask(std::function<void()>& task);

    template<typename... Args>
    void addTask(Args&&... args) {
        {
            std::unique_lock<std::mutex> lock(m_QueueMutex);
            m_Jobs.push(std::bind(std::forward<Args>(args)...));
        }
        mutex_condition.notify_one();
    }


    void stop();

private:

    void ThreadLoop();

private:

    bool m_ShouldStop;
    std::mutex m_QueueMutex;
    std::condition_variable mutex_condition;
    std::vector<std::thread> m_Threads;
    std::queue<std::function<void()>> m_Jobs;
};