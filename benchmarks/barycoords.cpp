#include <gtest/gtest.h>

#include <glm/gtx/string_cast.hpp>


#include "renderer/geometry/Triangle.h"
#include "utility/Random.h"
#include "utility/print.h"
#include "utility/time/Stopwatch.h"

using namespace cgl;

const float FLOAT_EPS = std::numeric_limits<float>::epsilon() * 100;

bool cmpFloats(float f1, float f2){
    if (f1 == f2){
        return true;
    }
    else{
        return std::abs(f1 - f2) <= std::abs(FLOAT_EPS * 10 * f1);
    }
}

int main(){
    Triangle2D tri(Vec2{100.0f, 50.0f}, Vec2{5.5f, 3.0f}, Vec2{180.0f, 60.0f});
    Random rand;
    Vector<Vec2> sample_points;

    size_t sample_cnt = 10000000;
    for (size_t i = 0; i < sample_cnt; i++){
        sample_points.emplace_back(Vec2{rand.nextFloat(), rand.nextFloat()});
    }
    Vec3 bary_coords;
    Vec3 coords_total;

    Stopwatch sw;
    for (size_t i = 0; i < sample_cnt; i++){
        tri.getBarycentricCoordinates(sample_points[i], bary_coords);
        coords_total += bary_coords;
    }
    size_t total_time = sw.micros();

    coutPrint("Sampling ", sample_cnt, " texels took ", total_time / 1000, " milliseconds");
    coutPrint("Rate: ", splitIntoGroups(3, std::to_string(static_cast<size_t>(1000.0f / (total_time / 1000) * 10000000))), " coords per second");

    coutPrint(glm::to_string(coords_total));
}
