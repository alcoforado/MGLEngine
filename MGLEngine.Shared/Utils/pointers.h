#pragma once

#include <memory>

template<class T>
using s_ptr = std::shared_ptr<T>;

template<class T>
using u_ptr = std::unique_ptr<T>;

template <typename T>
constexpr auto s_new = [](auto&&... args) {
    return std::make_shared<T>(std::forward<decltype(args)>(args)...);
};
