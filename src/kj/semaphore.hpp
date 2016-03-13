#ifndef INCLUDED_KJ_SEMAPHORE_HPP
#define INCLUDED_KJ_SEMAPHORE_HPP

#include <chrono>
#include <condition_variable>
#include <mutex>

namespace kj {

class Semaphore
{
public:
    Semaphore();
    Semaphore(int count);

    void wait();
    template<typename Rep, typename Period>
    bool wait(const std::chrono::duration<Rep, Period>& rel_time);
    bool tryWait();

    void post();

    int count() const { return d_count; }
private:
    std::mutex d_mutex;
    std::condition_variable d_cond;
    int d_count;
};

template<typename Rep, typename Period>
bool Semaphore::wait(const std::chrono::duration<Rep, Period>& rel_time)
{
    std::unique_lock<std::mutex> guard(d_mutex);
    bool status = d_cond.wait_for(guard, rel_time, [this]() { return d_count > 0; });
    if (status)
        d_count--;
    return status;
}

} // close namespace kj

#endif //INCLUDED_KJ_SEMAPHORE_HPP
