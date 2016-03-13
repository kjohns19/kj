#ifndef INCLUDED_KJ_SUBJECT_HPP
#define INCLUDED_KJ_SUBJECT_HPP

#include <kj/observer.hpp>
#include <algorithm>
#include <vector>

namespace kj {

template<typename T>
class Subject
{
public:
    virtual ~Subject() = default;

    void addObserver(Observer<T>& observer);
    void removeObserver(Observer<T>& observer);

    void notifyObservers(T object);
private:
    std::vector<Observer<T>*> d_observers;
};

template<typename T>
void Subject<T>::addObserver(Observer<T>& observer)
{
    d_observers.push_back(&observer);
}
template<typename T>
void Subject<T>::removeObserver(Observer<T>& observer)
{
    d_observers.erase(
        std::remove(d_observers.begin(), d_observers.end(), &observer),
        d_observers.end());
}

template<typename T>
void Subject<T>::notifyObservers(T object)
{
    for(auto observer: d_observers)
        observer->update(object);
}

} // close namespace kj

#endif //INCLUDED_KJ_SUBJECT_HPP
