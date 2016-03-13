#ifndef INCLUDED_KJ_TIMER_HPP
#define INCLUDED_KJ_TIMER_HPP

#include <kj/duration.hpp>
#include <chrono>

namespace kj {

class Timer
{
public:
    Timer();

    void start();
    void stop();
    void reset();

    bool isRunning() const;
    Duration elapsedTime() const;
private:
    std::chrono::time_point<std::chrono::system_clock> d_startTime;
    std::chrono::time_point<std::chrono::system_clock> d_stopTime;
    bool d_running;
};

} // close namespace kj

#endif //INCLUDED_KJ_TIMER_HPP
