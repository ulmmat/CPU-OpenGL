#include "utility/time/Stopwatch.h"


namespace cgl{

void Stopwatch::reset(){
    m_set_time = std::chrono::high_resolution_clock::now();
}

size_t Stopwatch::seconds() const{
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_set_time).count();
}
size_t Stopwatch::millis() const{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_set_time).count();
}
size_t Stopwatch::micros() const{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_set_time).count();
}
size_t Stopwatch::nanos() const{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_set_time).count();
}

};