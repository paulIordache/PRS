//
// Created by paul on 10/2/25.
//

#ifndef LAB_1_MODELS_H
#define LAB_1_MODELS_H
#include <vector>


class Models {
public:
    explicit Models(const char *argv);

    ~Models() = default;

    std::pair<float, float> model_1() const;

    std::pair<float, float> model_2() const;

    void init();

private:
    void build_coordinates();

    const char *file_path;

    std::vector<std::pair<float, float> > coordinates;
    float sum_xy{},
            sum_x{},
            sum_y{},
            sum_sqrt_x{},
            sum_x_sqrt{};
    float sum_y2_minus_x2{};
    float sum_y_sqrt{};
    std::size_t coordinates_size{};

};


#endif //LAB_1_MODELS_H
