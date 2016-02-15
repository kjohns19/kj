#ifndef INCLUDED_KJ_RANDOM
#define INCLUDED_KJ_RANDOM

#include <limits>
#include <type_traits>
#include <random>

namespace kj {

template<typename T, typename A=void>
class Random {};

template<typename T>
class Random<T, typename std::enable_if<std::is_integral<T>::value, void>::type>
{
public:
    Random()
    : d_gen(std::random_device()())
    , d_dis() {}
    Random(std::mt19937::result_type seed)
    : d_gen(seed)
    , d_dis() {}

    void seed(std::mt19937::result_type seed)
    {
        d_gen.seed(seed);
    }

    T operator()(T min, T max)
    {
        return d_dis(d_gen, typename decltype(d_dis)::param_type(min, max));
    }
    T operator()()
    {
        return operator()(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    }
private:
    std::mt19937 d_gen;
    std::uniform_int_distribution<T> d_dis;
};

template<typename T>
class Random<T, typename std::enable_if<std::is_floating_point<T>::value, void>::type>
{
public:
    Random()
    : d_gen(std::random_device()())
    , d_dis() {}
    Random(std::mt19937::result_type seed)
    : d_gen(seed)
    , d_dis() {}

    void seed(std::mt19937::result_type seed)
    {
        d_gen.seed(seed);
    }

    T operator()(T min, T max)
    {
        return d_dis(d_gen, typename decltype(d_dis)::param_type(min, max));
    }
    T operator()()
    {
        return operator()(0, 1);
    }
private:
    std::mt19937 d_gen;
    std::uniform_real_distribution<T> d_dis;
};

} // close namespace kj

#endif //INCLUDED_KJ_RANDOM
