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

void draw_points(cv::Mat img, const char *file) {
    std::vector<std::pair<float, float> > coords =
            build_coordinates((std::string("../") + file).c_str());
    for (auto [x1, y1]: coords) {
        img.at<cv::Vec3b>(y1, x1)[0] = 0;
        img.at<cv::Vec3b>(y1, x1)[1] = 0;
        img.at<cv::Vec3b>(y1, x1)[2] = 0;
    }

    auto [fst, snd] = model_1(coords);
    cv::Point p1(0, fst * 0 + snd);
    cv::Point p2(img.cols - 1, fst * (img.cols - 1) + snd);
    line(img, p1, p2, cv::Scalar(0, 0, 255));
}

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <image>" << std::endl;
        return 1;
    }

    const cv::Mat img(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));
    draw_points(img, argv[1]);

    imshow("s", img);
    cv::waitKey();
    return 0;
}
