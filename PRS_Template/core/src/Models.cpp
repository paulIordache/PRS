//
// Created by paul on 10/2/25.
//

#include "../include/Models.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "../include/Coordinates.h"

void Models::build_coordinates() {
    FILE *file = fopen(file_path, "r");
    float x, y;
    int no_coord = 0;

    fscanf(file, "%d", &no_coord);
    std::cout << no_coord << std::endl;

    for (auto &coordinate: coordinates) {
        fscanf(file, "%f %f", &x, &y);
        coordinate = std::make_pair(x, y);
    }
    coordinates_size = coordinates.size();

    fclose(file);
}

void Models::init() {
    for (auto &[fst, snd]: coordinates) {
        sum_xy += fst * snd;
        sum_x += fst;
        sum_y += snd;
        sum_sqrt_x += fst * fst;
        sum_y2_minus_x2 += snd * snd - fst * fst;
    }

    sum_x_sqrt = sum_x * sum_x;
    sum_y_sqrt = sum_y * sum_y;

    build_coordinates();
}

Models::Models(const char *argv) : file_path(argv){
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
