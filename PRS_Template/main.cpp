#include <opencv2/opencv.hpp>
#include <iostream>

std::vector<std::pair<float, float> > build_coordinates(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    float x, y;
    int no_coord = 0;

    fscanf(file, "%d", &no_coord);
    std::cout << no_coord << std::endl;

    std::vector<std::pair<float, float> > coordinates(no_coord);
    for (auto &coordinate: coordinates) {
        fscanf(file, "%f %f", &x, &y);
        coordinate = std::make_pair(x, y);
    }

    fclose(file);
    return coordinates;
}

std::pair<float, float> model_1(std::vector<std::pair<float, float> > coordinates) {
    float m{}, b{};
    float sum_xy{}, sum_x{}, sum_y{}, sum_sqrt_x{}, sum_x_sqrt{};

    for (auto &[fst, snd]: coordinates) {
        sum_xy += fst * snd;
        sum_x += fst;
        sum_y += snd;
        sum_sqrt_x += fst * fst;
    }
    sum_x_sqrt = sum_x * sum_x;

    m = (static_cast<float>(coordinates.size()) * sum_xy - sum_x * sum_y) / (
            static_cast<float>(coordinates.size()) * sum_sqrt_x - sum_x_sqrt);
    b = (sum_y - m * sum_x) / static_cast<float>(coordinates.size());

    return std::make_pair(m, b);
}

std::pair<float, float> model_2(const std::vector<std::pair<float, float> > &coordinates) {
    float sum_x = 0.0f, sum_y = 0.0f;
    float sum_xy = 0.0f, sum_y2_minus_x2 = 0.0f;
    const size_t n = coordinates.size();

    for (auto &[x, y]: coordinates) {
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_y2_minus_x2 += y * y - x * x;
    }

    const float sum_x_sqr = sum_x * sum_x;
    const float sum_y_sqr = sum_y * sum_y;

    float beta = -0.5f * atan2(
                     2.0f * sum_xy - 2.0f / static_cast<float>(n) * sum_x * sum_y,
                     sum_y2_minus_x2 + (1.0f / static_cast<float>(n)) * sum_x_sqr - (1.0f / static_cast<float>(n)) *
                     sum_y_sqr
                 );

    float rho = (cos(beta) * sum_x + sin(beta) * sum_y) / n;

    return {beta, rho};
}


void draw_points(cv::Mat img, const char *file, const int model) {
    std::vector<std::pair<float, float> > coords =
            build_coordinates(file);
    for (auto [x1, y1]: coords) {
        img.at<cv::Vec3b>(y1, x1)[0] = 0;
        img.at<cv::Vec3b>(y1, x1)[1] = 0;
        img.at<cv::Vec3b>(y1, x1)[2] = 0;
    }

    switch (model) {
        case 1: {
            auto [fst, snd] = model_1(coords);
            cv::Point p1(0, fst * 0 + snd);
            cv::Point p2(img.cols - 1, fst * (img.cols - 1) + snd);
            cv::line(img, p1, p2, cv::Scalar(0, 0, 255), 2);
            break;
        }
        case 2: {
            auto [beta, rho] = model_2(coords);
            const float cos_beta = cos(beta);
            const float sin_beta = sin(beta);

            cv::Point p1, p2;

            if (std::abs(sin_beta) > std::abs(cos_beta)) {
                const float y1 = rho / sin_beta;
                const float y2 = (rho - (img.cols - 1.0f) * cos_beta) / sin_beta;
                p1 = cv::Point(0, static_cast<int>(y1));
                p2 = cv::Point(img.cols - 1, static_cast<int>(y2));
            } else {
                const float x1 = rho / cos_beta;
                const float x2 = (rho - (img.rows - 1.0f) * sin_beta) / cos_beta;
                p1 = cv::Point(static_cast<int>(x1), 0);
                p2 = cv::Point(static_cast<int>(x2), img.rows - 1);
            }
            cv::line(img, p1, p2, cv::Scalar(0, 0, 255), 2);
            break;
        }
        default:
            break;
    }
}

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <image>" << std::endl;
        return 1;
    }

    int model{1};
    std::cin >> model;
    const cv::Mat img(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));
    draw_points(img, argv[1], model);

    imshow("s", img);
    cv::waitKey();
    return 0;
}
