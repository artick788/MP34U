#include "ThreadPool.hpp"

ThreadPool::ThreadPool():
    m_ShouldStop(false){
    const uint32_t threadCount = std::thread::hardware_concurrency();
    for(uint32_t i = 0; i < threadCount; ++i){
        m_Threads.emplace_back(&ThreadPool::ThreadLoop, this);
    }

}

ThreadPool::~ThreadPool() {
    stop();
}

void ThreadPool::addTask(std::function<void()> &task) {
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);
        m_Jobs.push(task);
    }
    mutex_condition.notify_one();
}

void ThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);
        m_ShouldStop = true;
    }
    mutex_condition.notify_all();
    for (std::thread& active_thread : m_Threads) {
        active_thread.join();
    }
    m_Threads.clear();
}

void ThreadPool::ThreadLoop() {
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(m_QueueMutex);
            mutex_condition.wait(lock, [this] {
                return !m_Jobs.empty() || m_ShouldStop;
            });
            if (m_ShouldStop) {
                return;
            }
            job = m_Jobs.front();
            m_Jobs.pop();
        }
        job();
    }
}
