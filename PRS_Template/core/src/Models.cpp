#include "../include/Models.h"
#include <cmath>
#include <iostream>
#include <vector>

#include "Coordinates.h"
#include "common.h"

void Models::init() {
    coordinates_size = build_coordinates_from_file();

    for (auto &[fst, snd]: coordinates) {
        sum_xy += fst * snd;
        sum_x += fst;
        sum_y += snd;
        sum_sqrt_x += fst * fst;
        sum_y2_minus_x2 += snd * snd - fst * fst;
    }

    sum_x_sqrt = sum_x * sum_x;
    sum_y_sqrt = sum_y * sum_y;
}

Models::Models(const Type type, const char *argv) : logger("model_logger.txt"),
                                                    type(type),
                                                    file_path(argv) {
}

std::pair<float, float> Models::model_1() const {
    float m{}, b{};

    m = (static_cast<float>(coordinates_size) * sum_xy - sum_x * sum_y) / (
            static_cast<float>(coordinates_size) * sum_sqrt_x - sum_x_sqrt);
    b = (sum_y - m * sum_x) / static_cast<float>(coordinates_size);

    return std::make_pair(m, b);
}

std::pair<float, float> Models::model_2() const {
    float beta = -0.5f * std::atan2(
                     2.0f * sum_xy - 2.0f / static_cast<float>(coordinates_size) * sum_x * sum_y,
                     sum_y2_minus_x2 + 1.0f / static_cast<float>(coordinates_size) * sum_x_sqrt - (
                         1.0f / static_cast<float>(coordinates_size)) *
                     sum_y_sqrt
                 );

    float rho = (cos(beta) * sum_x + sin(beta) * sum_y) / coordinates_size;

    return {beta, rho};
}

std::pair<float, float> Models::compute_with_model() const {
    return (type == Type::LINEAR)
               ? model_1()
               : model_2();
}
