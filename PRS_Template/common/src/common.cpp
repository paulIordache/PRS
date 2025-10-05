#include <cstdio>
#include <vector>

#include "Log.h"
Log logger("logger.txt");

size_t build_coordinates_from_file(const char *file_path, std::vector<std::pair<float, float>> &coordinates) {
    FILE *file = fopen(file_path, "r");
    if (file == nullptr) {
        logger.log(ERROR, "Models::build_coordinates(): File not found.");
        return 0;
    }

    int no_coord = 0;
    if (fscanf(file, "%d", &no_coord) != 1) {
        logger.log(ERROR, "Models::build_coordinates(): Failed to read number of coordinates.");
        fclose(file);
        return 0;
    }

    logger.log(INFO, "Reading coordinates count = " + std::to_string(no_coord));

    float x, y;
    coordinates.resize(no_coord);

    for (int i = 0; i < no_coord; ++i) {
        if (fscanf(file, "%f %f", &x, &y) != 2) {
            logger.log(ERROR, "Models::build_coordinates(): Failed reading coordinates line " + std::to_string(i));
            break;
        }
        coordinates[i] = std::make_pair(x, y);
    }

    fclose(file);
    return coordinates.size();
}