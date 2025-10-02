#ifndef LAB_1_COORDINATES_H
#define LAB_1_COORDINATES_H
#include <opencv2/core/mat.hpp>

#include "Models.h"

class Coordinates {
public:
    explicit Coordinates(const char *argv) : models(Models(argv)) {
    }

    ~Coordinates() = default;

    void init();

    void draw_points(int model);

private:
    std::vector<std::pair<float, float> > coordinates;
    const char *file_path = nullptr;
    cv::Mat image;
    Models models;
};


#endif //LAB_1_COORDINATES_H
