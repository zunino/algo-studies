#include <iomanip>
#include <fstream>

#include "bmp.hpp"
#include "data.hpp"
#include "pgm.hpp"
#include "io.hpp"

void print_layer(const Layer& layer, std::ostream& os) {
    for (std::size_t row = 0; row < INPUT_HEIGHT; ++row) {
        os << std::setw(3) << std::right << row << ' ';
        for (std::size_t col = 0; col < INPUT_WIDTH; ++col) {
            float value = layer[row * INPUT_WIDTH + col];
            os << (value == 1.0f ? "\u2588\u2588" : "..");
        }
        os << '\n';
    }
}

void print_weights(const std::vector<float>& weights, std::ostream& os) {
    for (std::size_t row = 0; row < INPUT_HEIGHT; ++row) {
        os << std::setw(3) << std::right << row << ' ';
        for (std::size_t col = 0; col < INPUT_WIDTH; ++col) {
            float w = weights[row * INPUT_WIDTH + col];
            os << std::setw(3) << std::right << w << ' ';
        }
    }
    os << '\n';
}

void save_layer_as_bmp(const Layer& layer, const char* file_path) {
    BmpFile bmp_file{file_path, INPUT_WIDTH, INPUT_HEIGHT};
    bmp_file.write(layer);
}

void save_weights_as_pgm(const std::vector<float>& weights, const char* file_path) {
    PgmFile pgm_file{file_path, INPUT_WIDTH, INPUT_HEIGHT};
    pgm_file.write(weights);
}

void save_model(const std::vector<float>& weights, const char* file_path) {
    std::ofstream bin_file;
    bin_file.open(file_path, std::ios::out | std::ios::binary);
    bin_file.write(reinterpret_cast<const char*>(weights.data()), sizeof (float) * weights.size());
    bin_file.close();
}

std::vector<float> load_model(const char* file_path) {
    std::ifstream bin_file;
    bin_file.open(file_path, std::ios::binary);
    std::vector<float> weights;
    float value;
    while (bin_file.read(reinterpret_cast<char*>(&value), sizeof (float))) {
        weights.push_back(value);
    }
    bin_file.close();
    return weights;
}
