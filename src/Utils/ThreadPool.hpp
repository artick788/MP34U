#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

class ThreadPool{
public:
    ThreadPool();

    ~ThreadPool();

    void addTask(std::function<void()>& task);

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