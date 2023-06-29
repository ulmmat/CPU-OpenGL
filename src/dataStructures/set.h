#pragma once

#include <set>
#include <unordered_set>

namespace cgl
{

template<typename T, typename Comp = std::less<T>>
using Set = std::set<T, Comp>;

template<typename K, typename V>
using HashSet = std::unordered_set<K, V>;

template<typename T, typename Comp = std::less<T>>
bool setContains(const Set<T>& set, const T& val){
    auto it = set.find(val);
    return it != set.end();
}

}; // namespace cgl