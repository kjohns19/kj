#include <kj/timer.hpp>

namespace kj {

Timer::Timer()
: d_running(false) {}

void Timer::start()
{
    if (!d_running)
    {
        d_running = true;
        d_startTime = std::chrono::system_clock::now();
    }
}
void Timer::stop()
{
    if (d_running)
    {
        d_stopTime = std::chrono::system_clock::now();
        d_running = false;
    }
}
void Timer::reset()
{
    d_running = false;
    d_stopTime = d_startTime;
}

bool Timer::isRunning() const
{
    return d_running;
}

Duration Timer::elapsedTime() const
{
    auto stop = d_running ? std::chrono::system_clock::now() : d_stopTime;
    auto duration = stop - d_startTime;
    double ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    return Duration(ns);
}

} // close namespace kj

