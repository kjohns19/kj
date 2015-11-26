#include <kj/semaphore.hpp>

namespace kj {

Semaphore::Semaphore()
: d_count(0) {}
Semaphore::Semaphore(int count)
: d_count(count) {}

void Semaphore::wait()
{
    std::unique_lock<std::mutex> guard(d_mutex);
    d_cond.wait(guard, [this]() { return d_count > 0; });
    d_count--;
}
bool Semaphore::tryWait()
{
    std::lock_guard<std::mutex> guard(d_mutex);
    if (d_count > 0)
    {
        d_count--;
        return true;
    }
    return false;
}
void Semaphore::post()
{
    std::lock_guard<std::mutex> guard(d_mutex);
    d_count++;
    d_cond.notify_one();
}

} // close namespace kj

