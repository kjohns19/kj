#ifndef INCLUDED_KJ_THREAD_POOL
#define INCLUDED_KJ_THREAD_POOL

#include <kj/queue.hpp>
#include <kj/caller.hpp>
#include <vector>
#include <thread>
#include <future>
#include <type_traits>
#include <memory>

namespace kj {

class ThreadPool
{
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    size_t size() const;
    size_t queued() const;

    template<typename Func>
    std::future<typename std::result_of<Func()>::type> push(Func func);
private:
    std::vector<std::thread> d_threads;
    kj::Queue<std::unique_ptr<kj::Caller<void()>>> d_queue;
};

template<typename Func>
std::future<typename std::result_of<Func()>::type> ThreadPool::push(Func func)
{
    using resulttype = typename std::result_of<Func()>::type;
    std::packaged_task<resulttype()> task(func);
    std::future<resulttype> future = task.get_future();
    auto uniqTask = std::make_unique<kj::Caller<void()>>(std::move(task));
    d_queue.push(std::move(uniqTask));
    return std::move(future);
}

} // close namespace kj

#endif //INCLUDED_KJ_THREAD_POOL
