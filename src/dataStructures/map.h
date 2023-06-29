#pragma once

#include <map>
#include <unordered_map>
#include <functional>

namespace cgl{

template<typename K, typename V>
using Map = std::map<K, V>;

template<typename K, typename V, typename H = std::hash<K>>
using HashMap = std::unordered_map<K, V, H>;


};