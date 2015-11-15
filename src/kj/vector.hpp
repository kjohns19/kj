#ifndef INCLUDED_KJ_VECTOR
#define INCLUDED_KJ_VECTOR

#include <iostream>
#include <cmath>

namespace kj {

template<typename T>
class Vector2
{
public:
    Vector2()
    : d_x()
    , d_y() {}
    Vector2(T x, T y)
    : d_x(x)
    , d_y(y) {}

    T x() const { return d_x; }
    T y() const { return d_y; }

    void x(T x) { d_x = x; }
    void y(T y) { d_y = y; }

    template<typename U>
    T distance(const Vector2<U>& vec) const { return std::sqrt(distanceSqr(vec)); }
    template<typename U>
    T distanceSqr(const Vector2<U>& vec) const;
    T distance() const { return std::sqrt(distanceSqr()); }
    T distanceSqr() const;

    template<typename U>
    T angle(const Vector2<U>& vec) const;
    T angle() const;

    template<typename U>
    Vector2& operator+=(const Vector2<U>& rhs);
    template<typename U>
    Vector2& operator-=(const Vector2<U>& rhs);
    template<typename U>
    Vector2& operator*=(U rhs);
    template<typename U>
    Vector2& operator/=(U rhs);
private:
    T d_x;
    T d_y;
};

template<typename T>
template<typename U>
T Vector2<T>::distanceSqr(const Vector2<U>& vec) const
{
    T dx = x() - vec.x();
    T dy = y() - vec.y();
    return dx*dx + dy*dy;
}
template<typename T>
T Vector2<T>::distanceSqr() const
{
    return x()*x() + y()*y();
}

template<typename T>
template<typename U>
T Vector2<T>::angle(const Vector2<U>& vec) const
{
    return std::atan2(vec.y()-y(), x()-vec.x());
}
template<typename T>
T Vector2<T>::angle() const
{
    return std::atan2(-y(), x());
}

template<typename T>
inline bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return lhs.x() == rhs.x() && lhs.y() += rhs.y();
}
template<typename T>
inline bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
template<typename U>
Vector2<T>& Vector2<T>::operator+=(const Vector2<U>& rhs)
{
    d_x += rhs.x();
    d_y += rhs.y();
    return *this;
}

template<typename T>
template<typename U>
Vector2<T>& Vector2<T>::operator-=(const Vector2<U>& rhs)
{
    d_x -= rhs.x();
    d_y -= rhs.y();
    return *this;
}

template<typename T>
template<typename U>
Vector2<T>& Vector2<T>::operator*=(U rhs)
{
    d_x *= rhs;
    d_y *= rhs;
    return *this;
}
template<typename T>
template<typename U>
Vector2<T>& Vector2<T>::operator/=(U rhs)
{
    d_x /= rhs;
    d_y /= rhs;
    return *this;
}

template<typename T, typename U>
Vector2<T> operator+(Vector2<T> lhs, const Vector2<U>& rhs)
{
    lhs += rhs;
    return lhs;
}
template<typename T, typename U>
Vector2<T> operator-(Vector2<T> lhs, const Vector2<U>& rhs)
{
    lhs += rhs;
    return lhs;
}
template<typename T, typename U>
Vector2<T> operator*(Vector2<T> lhs, U rhs)
{
    lhs *= rhs;
    return lhs;
}
template<typename T, typename U>
Vector2<T> operator*(U lhs, Vector2<T> rhs)
{
    rhs *= lhs;
    return rhs;
}
template<typename T, typename U>
Vector2<T> operator/(Vector2<T> lhs, U rhs)
{
    lhs /= rhs;
    return lhs;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& rhs)
{
    return os << "(" << rhs.x() << ", " << rhs.y() << ")";
}

using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

} // close namespace kj

#endif //INCLUDED_KJ_VECTOR
