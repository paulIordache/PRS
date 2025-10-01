#include <opencv2/opencv.hpp>
#include <iostream>3

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <image>" << std::endl;
        return 1;
    }

    cv::Mat image = cv::imread("../1.png", cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Failed to load image" << std::endl;
        return 1;
    }

    cv::namedWindow("display", cv::WINDOW_AUTOSIZE);
    cv::imshow("display", image);
    cv::waitKey(0);

    return 0;
}