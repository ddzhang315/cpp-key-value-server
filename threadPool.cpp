#include "threadPool.h"
#include <utility>
#include <stdexcept>
#include <exception>
#include <iostream>

void ThreadPool::workerLoop()
{
    while(true)
    {
        std::function<void()> task;

        {
        std::unique_lock<std::mutex> lock(queueMutex);
        
        condition.wait(
            lock,
            [this]()
            {
                return stopping || !tasks.empty();
            }

        );

        if(stopping && tasks.empty()) return;
        task = std::move(tasks.front());
        tasks.pop();
        }

        try
        {
            task();
        }
        catch(const std::exception& e)
        {
            std::cerr<< "Task failed: "<< e.what() << '\n';
        }
        catch(...)
        {
            std::cerr << "Task failed: unknown exception\n";
        }
        
        
    }
}


ThreadPool::ThreadPool(std::size_t threadCount)
{
    workers.reserve(threadCount);
    for (std::size_t i = 0; i< threadCount; i++)
    {
        workers.emplace_back(
            [this]()
            {
                workerLoop();
            }
        );
    }
}

void ThreadPool::enqueue(std::function<void()> task)
{
    {
    std::lock_guard<std::mutex> lock(queueMutex);
    if(stopping)
    {
        throw std::runtime_error("Cannot enqueue task after shutdown");
    }
    tasks.push(std::move(task));
    }

    condition.notify_one();

}

ThreadPool::~ThreadPool()
{
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stopping = true;
    }
    condition.notify_all();
    for (auto& worker : workers)
    {
        worker.join();
    }
}