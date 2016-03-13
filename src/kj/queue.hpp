#ifndef INCLUDED_KJ_QUEUE_HPP
#define INCLUDED_KJ_QUEUE_HPP

#include <kj/semaphore.hpp>
#include <chrono>
#include <mutex>
#include <queue>

namespace kj {

template<typename T>
class Queue
{
public:
    size_t size() const { return d_queue.size(); }
    bool empty() const { return d_queue.empty(); }

    void push(const T& value);
    void push(T&& value);

    void pop(T* value);
    template<typename Rep, typename Period>
    bool pop(T* value, const std::chrono::duration<Rep, Period>& timeout);
    bool tryPop(T* value);
private:
    void doWrite(const T& value);
    void doRead(T* value);

    std::queue<T> d_queue;
    Semaphore d_readSem;
    std::mutex d_mutex;
};

template<typename T>
void Queue<T>::push(const T& value)
{
    std::lock_guard<std::mutex> guard(d_mutex);
    d_queue.push(value);
    d_readSem.post();
}

template<typename T>
void Queue<T>::push(T&& value)
{
    std::lock_guard<std::mutex> guard(d_mutex);
    d_queue.push(std::move(value));
    d_readSem.post();
}

template<typename T>
void Queue<T>::pop(T* value)
{
    d_readSem.wait();
    doRead(value);
}
template<typename T>
template<typename Rep, typename Period>
bool Queue<T>::pop(T* value, const std::chrono::duration<Rep, Period>& timeout)
{
    if (!d_readSem.wait(timeout))
        return false;
    doRead(value);
    return true;
}
template<typename T>
bool Queue<T>::tryPop(T* value)
{
    if (!d_readSem.tryWait())
        return false;
    doRead(value);
    return true;
}

template<typename T>
void Queue<T>::doRead(T* value)
{
    std::lock_guard<std::mutex> guard(d_mutex);
    *value = std::move(d_queue.front());
    d_queue.pop();
}

} // close namespace kj

#endif //INCLUDED_KJ_QUEUE_HPP
