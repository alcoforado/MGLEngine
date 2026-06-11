#include <memory>

template<class T>
using s_ptr = std::shared_ptr<T>;

template<class T>
using u_ptr = std::unique_ptr<T>;