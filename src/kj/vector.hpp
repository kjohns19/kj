#ifndef INCLUDED_KJ_VECTOR
#define INCLUDED_KJ_VECTOR

#include <ostream>
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

    static Vector2<T> polar(T length, T angle);
    static Vector2<T> cartesian(T x, T y);

    T x() const { return d_x; }
    T y() const { return d_y; }

    void x(T x) { d_x = x; }
    void y(T y) { d_y = y; }

    void reset() { d_x = d_y = T(); }

    template<typename U>
    T distance(const Vector2<U>& vec) const { return std::sqrt(distanceSqr(vec)); }
    template<typename U>
    T distanceSqr(const Vector2<U>& vec) const;

    T length() const { return std::sqrt(lengthSqr()); }
    T lengthSqr() const;

    void length(T length);
    Vector2<T> atLength(T length) const;
    void normalize() { length(1); }
    Vector2<T> normalized() const { return atLength(1); }

    template<typename U>
    T angle(const Vector2<U>& vec) const;
    T angle() const;

    void angle(T angle);
    Vector2<T> atAngle(T angle) const;
private:
    T d_x;
    T d_y;
};

template<typename T>
Vector2<T> Vector2<T>::polar(T length, T angle)
{
    return Vector2(length*std::cos(angle), -length*std::sin(angle));
}
template<typename T>
Vector2<T> Vector2<T>::cartesian(T x, T y)
{
    return Vector2(x, y);
}

template<typename T>
template<typename U>
T Vector2<T>::distanceSqr(const Vector2<U>& vec) const
{
    T dx = x() - vec.x();
    T dy = y() - vec.y();
    return dx*dx + dy*dy;
}
template<typename T>
T Vector2<T>::lengthSqr() const
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
void Vector2<T>::length(T length)
{
    T current = this->length();
    x(x()*length/current);
    y(y()*length/current);
}
template<typename T>
Vector2<T> Vector2<T>::atLength(T length) const
{
    auto copy(*this);
    copy.length(length);
    return copy;
}

template<typename T>
void Vector2<T>::angle(T angle)
{
    T length = this->length();
    x(length*std::cos(angle));
    y(-length*std::sin(angle));
}

template<typename T>
Vector2<T> Vector2<T>::atAngle(T angle) const
{
    auto copy(*this);
    copy.angle(angle);
    return copy;
}

template<typename T>
bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return lhs.x() == rhs.x() && lhs.y() += rhs.y();
}
template<typename T>
bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return !(lhs == rhs);
}

template<typename T, typename U>
Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<U>& rhs)
{
    lhs.x(lhs.x() + rhs.x());
    lhs.y(lhs.y() + rhs.y());
    return lhs;
}

template<typename T, typename U>
Vector2<T>& operator-=(Vector2<T>& lhs, const Vector2<U>& rhs)
{
    lhs.x(lhs.x() - rhs.x());
    lhs.y(lhs.y() - rhs.y());
    return lhs;
}

template<typename T, typename U>
Vector2<T>& operator*=(Vector2<T>& lhs, U rhs)
{
    lhs.x(lhs.x() * rhs);
    lhs.y(lhs.y() * rhs);
    return lhs;
}

template<typename T, typename U>
Vector2<T>& operator/=(Vector2<T>& lhs, U rhs)
{
    lhs.x(lhs.x() / rhs);
    lhs.y(lhs.y() / rhs);
    return lhs;
}

template<typename T, typename U>
auto operator+(const Vector2<T>& lhs, const Vector2<U>& rhs)
{
    Vector2<decltype(T()+U())> copy(lhs.x()+rhs.x(), lhs.y()+rhs.y());
    return copy;
}
template<typename T, typename U>
auto operator-(const Vector2<T>& lhs, const Vector2<U>& rhs)
{
    Vector2<decltype(T()-U())> copy(lhs.x()-rhs.x(), lhs.y()-rhs.y());
    return copy;
}
template<typename T, typename U>
auto operator*(const Vector2<T>& lhs, U rhs)
{
    Vector2<decltype(T()*U())> copy(lhs.x()*rhs, lhs.y()*rhs);
    return copy;
}
template<typename T, typename U>
auto operator*(U lhs, const Vector2<T>& rhs)
{
    Vector2<decltype(U()*T())> copy(rhs*lhs.x(), rhs*lhs.y());
    return copy;
}
template<typename T, typename U>
auto operator/(const Vector2<T>& lhs, U rhs)
{
    Vector2<decltype(T()/U())> copy(lhs.x()/rhs, lhs.y()/rhs);
    return copy;
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
