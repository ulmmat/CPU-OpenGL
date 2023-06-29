#pragma once

#include <optional>
#include <functional>

namespace cgl
{

template<typename T>
using Opt = std::optional<T>;

const std::nullopt_t NULLOPT = std::nullopt;

template<typename T>
bool optDoIfPresent(Opt<T>& opt, std::function<void(T&)> fun){
    if (opt.has_value()){
        fun(opt.value());
        return true;
    }
    return false;
}

}; // namespace cgl