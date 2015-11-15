#ifndef INCLUDED_KJ_OBJECT_BUFFER
#define INCLUDED_KJ_OBJECT_BUFFER

namespace kj {

template<typename T>
class ObjectBuffer
{
public:
    T& object() { return *reinterpret_cast<T*>(&d_buffer); }
    const T& object() const { return *reinterpret_cast<const T*>(&d_buffer); }
    void* buffer() { return d_buffer; }
    const void* buffer() const { return d_buffer; }
private:
    alignas(T) char d_buffer[sizeof(T)];
};

} // close namespace kj

#endif //INCLUDED_KJ_OBJECT_BUFFER
