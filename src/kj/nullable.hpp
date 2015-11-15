#ifndef INCLUDED_KJ_NULLABLE
#define INCLUDED_KJ_NULLABLE

#include <kj/object_buffer.hpp>
#include <utility>

namespace kj {

template<typename T>
class Nullable
{
public:
    Nullable();
    template<typename ...Args>
    Nullable(Args&&... args);
    Nullable(Nullable&& other);

    Nullable(const Nullable& other);

    Nullable& operator=(const Nullable& other);
    Nullable& operator=(Nullable&& other);

    ~Nullable();

    T& value() { return d_buffer.object(); }
    const T& value() const { return d_buffer.object(); }

    template<typename ...Args>
    T& makeValue(Args&&... args);

    void makeNull();

    bool isNull() const { return d_null; };
private:
    ObjectBuffer<T> d_buffer;
    bool d_null;
};

template<typename T>
Nullable<T>::Nullable()
: d_null(true) {}

template<typename T>
template<typename ...Args>
Nullable<T>::Nullable(Args&&... args)
: d_null(true)
{
    makeValue(std::forward<Args>(args)...);
}

template<typename T>
Nullable<T>::Nullable(Nullable&& other)
: d_null(other.d_null)
{
    if (!d_null)
        makeValue(std::move(other.d_buffer.object()));
    other.makeNull();
}

template<typename T>
Nullable<T>::Nullable(const Nullable& other)
: d_null(other.d_null)
{
    if (!d_null)
        makeValue(other.d_buffer.object());
}

template<typename T>
Nullable<T>& Nullable<T>::operator=(const Nullable<T>& other)
{
    if (other.d_null)
        makeNull();
    else if (!d_null)
        value() = other.value();
    else
        makeValue(other.value());
    return *this;
}

template<typename T>
Nullable<T>& Nullable<T>::operator=(Nullable<T>&& other)
{
    if (other.d_null)
        makeNull();
    else if (!d_null)
        value() = std::move(other.value());
    else
        makeValue(std::move(other.value()));
    other.makeNull();
    return *this;
}

template<typename T>
Nullable<T>::~Nullable()
{
    makeNull();
}

template<typename T>
template<typename ...Args>
T& Nullable<T>::makeValue(Args&&... args)
{
    makeNull();
    new (d_buffer.buffer()) T(std::forward<Args>(args)...);
    d_null = false;
    return value();
}

template<typename T>
void Nullable<T>::makeNull()
{
    if (!d_null)
    {
        T& value = d_buffer.object();
        value.~T();
        d_null = true;
    }
}

} // close namespace kj

#endif //INCLUDED_KJ_NULLABLE
