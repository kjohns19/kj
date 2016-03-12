#ifndef INCLUDED_KJ_OBSERVER
#define INCLUDED_KJ_OBSERVER

namespace kj {

template<typename T>
class Observer
{
public:
    virtual void update(T object) = 0;
private:
};

} // close namespace kj

#endif //INCLUDED_KJ_OBSERVER
