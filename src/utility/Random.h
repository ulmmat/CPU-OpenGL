#pragma once

#include <chrono>
#include <random>


namespace cgl{

class Random{

    public:
        Random(size_t seed = std::chrono::system_clock::now().time_since_epoch().count());

        // Range [0.0;1.0]
        float nextFloat();

        int8_t nextInt8();
        uint8_t nextUInt8();

        int16_t nextInt16();
        uint16_t nextUInt16();

        int32_t nextInt32();
        uint32_t nextUInt32();

        int64_t nextInt64();
        uint64_t nextUInt64();

    private:
        // Range [-1.0;1.0]
        float nextFloatNeg();
        std::mt19937 m_gen;
        std::uniform_real_distribution<float> m_pos_dis = std::uniform_real_distribution<float>(0.0f, 1.0f);
        std::uniform_real_distribution<float> m_neg_dis = std::uniform_real_distribution<float>(0.0f, 1.0f);

};

};