#pragma once

#include <chrono>


namespace cgl{

class Stopwatch{

    public:
        void reset();

        size_t seconds() const;
        size_t millis() const;
        size_t micros() const;
        size_t nanos() const;
    private:

        decltype(std::chrono::high_resolution_clock::now()) m_set_time = std::chrono::high_resolution_clock::now();

};

};