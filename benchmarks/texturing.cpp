#include "renderer/textures/Texture.h"

#include "utility/Random.h"
#include "utility/print.h"
#include "utility/time/Stopwatch.h"

using namespace cgl;



enum class TexturingStrategy{
    BILINEAR,
    NEAREST
};

enum class SamplingStrategy{
    LINEAR,
    RANDOM
};

template<
    bool POWER_OF_TWO_SIZE = false,
    bool NON_NEGATIVE_COORDS = false
>
inline void mainSampleLoop(size_t sample_cnt, Texture& tex, Vector<float>& u_samples, Vector<float>& v_samples, size_t& ctr){
    for (size_t i = 0; i < sample_cnt; i++){
        ctr += tex.sampleTex<POWER_OF_TWO_SIZE, NON_NEGATIVE_COORDS>(u_samples[i], v_samples[i]).red;
    }
}

void doTextureBenchmark(
    int tex_width,
    int tex_height,
    int sample_cnt,
    TexturingStrategy tex_strategy,
    SamplingStrategy sample_strategy,
    bool non_negative_coords = false,
    int attempt_cnt = 1
){
    bool is_power_of_two = ( ((tex_width & (tex_width - 1)) == 0) && ((tex_height & (tex_height - 1)) == 0) );
    Random random;
    float total_time = 0.0f;
    size_t total_ctr = 0;
    for (int i = 0; i < attempt_cnt; i++){
        Texture tex;
        Vector<unsigned char> tex_data;
        tex_data.resize(tex_width*tex_height*4);
        for (size_t i = 0; i < (tex_width*tex_height*4); i++){
            tex_data[i] = random.nextUInt8();
        }

        tex.setData(
            GL_TEXTURE_2D, 0,
            GL_RGBA,
            tex_width, tex_height,
            0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data.data()
        );

        switch (tex_strategy)
        {
            case TexturingStrategy::NEAREST :
                tex.mag_filter = GL_NEAREST;
                tex.min_filter = GL_NEAREST;
                break;

            case TexturingStrategy::BILINEAR :
                tex.mag_filter = GL_LINEAR;
                tex.min_filter = GL_LINEAR;
                break;

            default:
                break;
        }


        Vector<float> u_samples;
        Vector<float> v_samples;

        for (size_t i = 0; i < sample_cnt; i++){
            switch (sample_strategy)
            {
                case SamplingStrategy::LINEAR :
                    u_samples.emplace_back(static_cast<float>(i) / sample_cnt);
                    v_samples.emplace_back(static_cast<float>(i) / sample_cnt);
                    break;

                case SamplingStrategy::RANDOM :
                    u_samples.emplace_back(random.nextFloat());
                    v_samples.emplace_back(random.nextFloat());

                default:
                    break;
            }
        }
        size_t ctr = 0;
        Stopwatch timer;
        if (is_power_of_two){
            if (non_negative_coords){
                mainSampleLoop<true, true>(sample_cnt, tex, u_samples, v_samples, ctr);
            }
            else{
                mainSampleLoop<true, false>(sample_cnt, tex, u_samples, v_samples, ctr);
            }
        }
        else{
            if (non_negative_coords){
                mainSampleLoop<false, true>(sample_cnt, tex, u_samples, v_samples, ctr);
            }
            else{
                mainSampleLoop<false, false>(sample_cnt, tex, u_samples, v_samples, ctr);
            }
        }
        size_t millis = timer.micros();
        total_time += millis;
        total_ctr += ctr;
    }
    total_time /= attempt_cnt;
    coutPrint("Sampling ", sample_cnt, " texels took ", total_time / 1000, " milliseconds", total_ctr);
    coutPrint("Rate: ", splitIntoGroups(3, std::to_string(static_cast<size_t>(1000.0f / (total_time / 1000) * 10000000))), " texels per second");
}

int main(){
    doTextureBenchmark(16, 16, 10000000, TexturingStrategy::NEAREST, SamplingStrategy::LINEAR, false, 1);
    doTextureBenchmark(16, 24, 10000000, TexturingStrategy::BILINEAR, SamplingStrategy::LINEAR, false, 1);
    doTextureBenchmark(16, 16, 10000000, TexturingStrategy::BILINEAR, SamplingStrategy::LINEAR, false, 1);
    doTextureBenchmark(16, 16, 10000000, TexturingStrategy::BILINEAR, SamplingStrategy::LINEAR, true, 1);
}