#pragma once

/**
 * @file print.h
 * @brief Functions for easier printing
 */

#include <iostream>
#include <sstream>

#include "dataStructures/string.h"

namespace cgl
{

static String endlToString(){
    std::stringstream s;
    s << std::endl;
    return s.str();
}

const String ENDLINE = endlToString();

struct PrintSpecs{
    String sep;
    String final;
};

template<typename... Args>
inline void coutPrintSpec(const PrintSpecs specs, const Args... args){
    #ifndef NO_PRINT
    ( (std::cout << args << specs.sep), ...);
    std::cout << specs.final << std::flush;
    #endif
}

template<typename... Args>
inline void coutPrint(const Args... args ){
     return coutPrintSpec<Args...>(PrintSpecs{" ", ENDLINE}, args...);
}

template<typename... Args>
inline void coutPrintDebug(const Args... args ){
    #ifdef DEBUG
    return coutPrint(args...);
    #endif
}


template<typename... Args>
inline void coutPrintNoSpace(const Args... args ){
    return coutPrintSpec<Args...>(PrintSpecs{"", ENDLINE}, args...);
}

}; // namespace cgl