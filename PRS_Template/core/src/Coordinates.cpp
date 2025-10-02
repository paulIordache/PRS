//
// Created by paul on 10/2/25.
//

#include "../include/Coordinates.h"

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void Coordinates::init() {
    image = cv::Mat(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));
    models.init();
}

void Coordinates::draw_points(const int model) {
    for (auto [x1, y1]: coordinates) {
        image.at<cv::Vec3b>(y1, x1)[0] = 0;
        image.at<cv::Vec3b>(y1, x1)[1] = 0;
        image.at<cv::Vec3b>(y1, x1)[2] = 0;
    }

    switch (model) {
        case 1: {
            auto [fst, snd] = models.model_1();
            cv::Point p1(0, fst * 0 + snd);
            cv::Point p2(image.cols - 1, fst * (image.cols - 1) + snd);
            cv::line(image, p1, p2, cv::Scalar(0, 0, 255), 2);
            break;
        }
        case 2: {
            auto [beta, rho] = models.model_2();
            const float cos_beta = cos(beta);
            const float sin_beta = sin(beta);

            cv::Point p1, p2;

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
            cv::line(image, p1, p2, cv::Scalar(0, 0, 255), 2);
            break;
        }
        default:
            break;
    }

    cv::imshow("s", image);
    cv::waitKey();
}
