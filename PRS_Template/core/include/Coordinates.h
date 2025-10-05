#ifndef LAB_1_COORDINATES_H
#define LAB_1_COORDINATES_H
#include <opencv2/core/mat.hpp>

#include "Models.h"

class Coordinates {
public:
    explicit Coordinates(const char *argv) : models(Models(Models::Type::LINEAR, argv)) {
    }

    ~Coordinates() = default;

    void init();

    void draw_points(int model);

private:
    cv::Mat image;
    Models models;
};


#endif //LAB_1_COORDINATES_H
