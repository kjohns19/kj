#ifndef INCLUDED_KJ_FINALLY_HPP
#define INCLUDED_KJ_FINALLY_HPP

#include <utility>

namespace kj {

template<typename F>
class Finally
{
public:
    Finally(F&& f)
    : d_f(std::forward<F>(f))
    , d_call(true) {}
    Finally(Finally&& f)
    : d_f(std::forward<F>(f.d_f))
    , d_call(f.d_call) {}
    Finally(const Finally&) = delete;
    Finally& operator=(Finally&) = delete;

    ~Finally() { if (d_call) d_f(); }

    void release() { d_call = false; }
private:
    F d_f;
    bool d_call;
};

template<typename F>
Finally<F> finally(F&& f) { return Finally<F>(std::forward<F>(f)); }

} // close namespace kj

#endif //INCLUDED_KJ_FINALLY_HPP
