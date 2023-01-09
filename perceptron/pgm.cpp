#include <algorithm>
#include <cstddef>

#include "pgm.hpp"

PgmFile::PgmFile(const char* file_path, unsigned img_width, unsigned img_height)
: file_path{file_path}, img_width{img_width}, img_height{img_height}
{
}

int map_to_8bit_value(float v, float min, float max) {
    return (v - min) * 255 / (max - min);
}

void PgmFile::write(const std::vector<float>& img_data) {
    std::ofstream pgm_file;
    pgm_file.open(file_path);
    write_headers(pgm_file);
    auto min_max = std::minmax_element(img_data.begin(), img_data.end());
    for (std::size_t row = 0; row < img_height; ++row) {
        for (std::size_t col = 0; col < img_width; ++col) {
            float original_value = img_data[row * img_width + col];
            auto pixel_value = map_to_8bit_value(original_value, *min_max.first, *min_max.second);
            pgm_file << pixel_value;
            if (col < img_width - 1) {
                pgm_file << ' ';
            }
        }
        if (row < img_height - 1) {
            pgm_file << '\n';
        }
    }
    pgm_file.close();
}

void PgmFile::write_headers(std::ofstream& pgm_file) {
    pgm_file << "P2\n";
    pgm_file << img_width << ' ' << img_height << '\n';
}
