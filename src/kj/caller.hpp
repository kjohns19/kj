#ifndef INCLUDED_KJ_CALLER_HPP
#define INCLUDED_KJ_CALLER_HPP

#include <memory>
#include <utility>

namespace kj {

template<typename R, typename... Args>
class Caller;

template<typename R, typename... Args>
class Caller<R(Args...)>
{
public:
    template<typename Callable>
    Caller(Callable&& callable)
    : d_impl(std::make_unique<CallerImpl<Callable>>(std::move(callable))) {}

    R call(Args&&... args)
    {
        return d_impl->call(std::forward<Args>(args)...);
    }
private:
    class CallerBase
    {
    public:
        virtual R call(Args&&... args) = 0;
        virtual ~CallerBase() = default;
    };
    template<typename Callable>
    class CallerImpl : public CallerBase
    {
    public:
        CallerImpl(Callable&& callable)
        : d_callable(std::move(callable)) {}

        R call(Args&&... args) override
        {
            return d_callable(std::forward<Args>(args)...);
        }

    private:
        Callable d_callable;
    };

    std::unique_ptr<CallerBase> d_impl;
};

} // close namespace kj

#endif //INCLUDED_KJ_CALLER_HPP
