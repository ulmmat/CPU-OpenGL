#include "utility/Random.h"

#include <limits>

namespace cgl{

Random::Random(size_t seed){
    m_gen.seed(seed);
}

float Random::nextFloat(){
    return m_pos_dis(m_gen);
}
float Random::nextFloatNeg(){
    return m_neg_dis(m_gen);
}
int8_t Random::nextInt8(){
    return nextFloatNeg() * std::numeric_limits<int8_t>::max();
}
uint8_t Random::nextUInt8(){
    return nextFloat() * std::numeric_limits<uint8_t>::max();
}

int16_t Random::nextInt16(){
    return nextFloatNeg() * std::numeric_limits<int16_t>::max();
}
uint16_t Random::nextUInt16(){
    return nextFloat() * std::numeric_limits<uint16_t>::max();
}

int32_t Random::nextInt32(){
    return nextFloatNeg() * std::numeric_limits<int32_t>::max();
}
uint32_t Random::nextUInt32(){
    return nextFloat() * std::numeric_limits<uint32_t>::max();
}

int64_t Random::nextInt64(){
    return nextFloatNeg() * std::numeric_limits<int64_t>::max();
}
uint64_t Random::nextUInt64(){
    return nextFloat() * std::numeric_limits<uint64_t>::max();
}


};