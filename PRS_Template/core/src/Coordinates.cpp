#include "../include/Coordinates.h"

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void Coordinates::init() {
    image = cv::Mat(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));
    models.init();
}

std::pair<cv::Point, cv::Point> compute_normal(
    const float beta,
    const float rho,
    const cv::Mat &image) {
    cv::Point p1;
    cv::Point p2;

    const float cos_beta = cos(beta);
    const float sin_beta = sin(beta);

    if (std::abs(sin_beta) > std::abs(cos_beta)) {
        const float y1 = rho / sin_beta;
        const float y2 = (rho - (image.cols - 1.0f) * cos_beta) / sin_beta;
        p1 = cv::Point(0, static_cast<int>(y1));
        p2 = cv::Point(image.cols - 1, static_cast<int>(y2));
    } else {
        const float x1 = rho / cos_beta;
        const float x2 = (rho - (image.rows - 1.0f) * sin_beta) / cos_beta;
        p1 = cv::Point(static_cast<int>(x1), 0);
        p2 = cv::Point(static_cast<int>(x2), image.rows - 1);
    }
    return {p1, p2};
}

void Coordinates::draw_points(const int model) {
    for (auto [x1, y1]: models.get_coordinates()) {
        image.at<cv::Vec3b>(y1, x1)[0] = 0;
        image.at<cv::Vec3b>(y1, x1)[1] = 0;
        image.at<cv::Vec3b>(y1, x1)[2] = 0;
    }

    switch (model) {
        case 1: {
            auto [fst, snd] = models.compute_with_model();
            const cv::Point p1(0, fst * 0 + snd);
            const cv::Point p2(image.cols - 1, fst * (image.cols - 1) + snd);
            cv::line(image, p1, p2, cv::Scalar(0, 0, 255), 2);
            break;
        }
        case 2: {
            auto [beta, rho] = models.compute_with_model();
            auto [fst, snd] = compute_normal(beta, rho, image);
            cv::line(image, fst, snd, cv::Scalar(0, 0, 255), 2);
            break;
        }
        default:
            break;
    }

    cv::imshow("s", image);
    cv::waitKey();
}
