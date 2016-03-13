#ifndef INCLUDED_KJ_DURATION_HPP
#define INCLUDED_KJ_DURATION_HPP

namespace kj {

class Duration
{
public:
    explicit Duration(double ns):
        d_ns(ns) {}

    void seconds(double seconds) { d_ns = seconds*1000000000.0; }
    void milliseconds(double ms) { d_ns = ms*1000000.0; }
    void microseconds(double us) { d_ns = us*1000.0; }
    void nanoseconds(double ns)  { d_ns = ns; }

    double seconds() const      { return d_ns/1000000000.0; }
    double milliseconds() const { return d_ns/1000000.0; }
    double microseconds() const { return d_ns/1000.0; }
    double nanoseconds() const  { return d_ns; }
private:
    double d_ns;
};

} // close namespace kj

#endif //INCLUDED_KJ_DURATION_HPP
