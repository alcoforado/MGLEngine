#pragma once

#include <memory>
#include <cstdlib>
template<class T>
using s_ptr = std::shared_ptr<T>;

template<class T>
using u_ptr = std::unique_ptr<T>;

template <typename T>
constexpr auto s_new = [](auto&&... args) {
    return std::make_shared<T>(std::forward<decltype(args)>(args)...);
};

class AlignedByteBuffer
{
    void* ptr;
public:
    AlignedByteBuffer(void* p) { ptr = p; }
    void* getPointer() { return ptr; }
    void free() {
        if (ptr != nullptr)
        {
            #if defined(_MSC_VER) || defined(__MINGW32__)
                _aligned_free(ptr);
            #else
             // Linux, macOS, and BSD can use standard free
             std::free(ptr);
            #endif
        }
    }
};

template<typename T>
void* copy_to_aligned_buffer(const T& data) {
    static_assert(std::is_trivially_copyable<T>::value, "Initializable type must be Trivially Copyable to use with DeclareMappedUbo!");
    void* ptr = nullptr;
#if defined(_MSC_VER) || defined(__MINGW32__)
    // Windows / MSVC
    ptr= _aligned_malloc(sizeof(T), alignof(T));
#elif defined(__APPLE__) || defined(__FreeBSD__)
    // macOS / BSD (posix_memalign is highly reliable here)
    posix_memalign(&ptr, alignof(T), sizeof(T)) == 0) 
#else
    // Linux / Standard POSIX (C11 / C++17)
    // Note: size must be a multiple of alignment for std::aligned_alloc
    ptr= std::aligned_alloc(alignof(T), sizeof(T));
#endif
    return AlignedByteBuffer(ptr);
}