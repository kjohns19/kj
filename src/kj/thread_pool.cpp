#include <kj/thread_pool.hpp>
#include <iostream>

namespace kj {

namespace {

void threadWorker(kj::Queue<std::unique_ptr<kj::Caller<void()>>>& queue);

}

ThreadPool::ThreadPool(size_t numThreads)
: d_threads(numThreads)
{
    for(size_t i = 0; i < numThreads; i++)
        d_threads[i] = std::thread(threadWorker, std::ref(d_queue));
}

ThreadPool::~ThreadPool()
{
    for(size_t i = 0; i < d_threads.size(); i++)
        d_queue.push(nullptr);
    for(auto& thread: d_threads)
        thread.join();
}

size_t ThreadPool::size() const
{
    return d_threads.size();
}

size_t ThreadPool::queued() const
{
    return d_queue.size();
}

namespace {

void threadWorker(kj::Queue<std::unique_ptr<kj::Caller<void()>>>& queue)
{
    std::unique_ptr<kj::Caller<void()>> task;
    while(1)
    {
        queue.pop(&task);
        if (!task)
            break;
        task->call();
    }
}

}

} // close namespace kj

