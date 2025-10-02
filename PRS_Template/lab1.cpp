#include <opencv2/opencv.hpp>
#include <iostream>

#include "core/include/Coordinates.h"

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <image>" << std::endl;
        return 1;
    }

    int model{1};
    std::cin >> model;
    Coordinates coordinates(argv[1]);
    coordinates.init();
    coordinates.draw_points(model);

    return 0;
}
