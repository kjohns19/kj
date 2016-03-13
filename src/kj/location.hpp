#ifndef INCLUDED_KJ_LOCATION_HPP
#define INCLUDED_KJ_LOCATION_HPP

#include <ostream>

namespace kj {

class Location
{
public:
    Location()
    : d_x(0)
    , d_y(0) {}
    Location(int x, int y)
    : d_x(x)
    , d_y(y) {}

    int x() const { return d_x; }
    int y() const { return d_y; }

    void x(int x) { d_x = x; }
    void y(int y) { d_y = y; }

    void set(int x, int y);
    void translate(int x, int y);
    Location translated(int x, int y) const;
private:
    int d_x;
    int d_y;
};

inline void Location::set(int x, int y)
{
    d_x = x;
    d_y = y;
}
inline void Location::translate(int x, int y)
{
    d_x += x;
    d_y += y;
}
inline Location Location::translated(int x, int y) const
{
    Location copy(*this);
    copy.translate(x, y);
    return copy;
}

inline std::ostream& operator<<(std::ostream& os, const Location& rhs)
{
    return os << "(" << rhs.x() << ", " << rhs.y() << ")";
}

inline bool operator==(const Location& lhs, const Location& rhs)
{
    return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}
inline bool operator!=(const Location& lhs, const Location& rhs)
{
    return !(lhs == rhs);
}
inline bool operator<(const Location& lhs, const Location& rhs)
{
    if (lhs.x() != rhs.x())
        return lhs.x() < rhs.x();
    return lhs.y() < rhs.y();
}
inline bool operator>(const Location& lhs, const Location& rhs)
{
    return rhs < lhs;
}
inline bool operator<=(const Location& lhs, const Location& rhs)
{
    return !(rhs < lhs);
}
inline bool operator>=(const Location& lhs, const Location& rhs)
{
    return !(lhs < rhs);
}

} // close namespace kj

#endif //INCLUDED_KJ_LOCATION_HPP
