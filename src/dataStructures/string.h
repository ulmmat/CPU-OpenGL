#pragma once

#include <string>

namespace cgl
{

using String = std::string;

inline String splitIntoGroups(uint8_t group_size, const String& str){
    String out_str = str;
    size_t size = str.size();
    size_t off = size % group_size;
    if (off == 0){
        off = group_size;
    }
    for (size_t i = off; i < out_str.size(); i+=(group_size + 1)){
        out_str.insert(out_str.begin() + i, ' ');
    }
    return out_str;
}

}; // namespace cgl