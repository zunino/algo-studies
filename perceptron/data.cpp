#include <cmath>
#include <iomanip>

#include "random.hpp"
#include "data.hpp"

constexpr int MIN_FIGURE_WIDTH = 0.5f * INPUT_WIDTH;
constexpr int MIN_FIGURE_HEIGHT = 0.5f * INPUT_HEIGHT;

constexpr int MAX_FIGURE_WIDTH = 0.95f * INPUT_WIDTH;
constexpr int MAX_FIGURE_HEIGHT = 0.95f * INPUT_HEIGHT;

Layer generate_random_rectangle() {
    std::size_t w = random(MIN_FIGURE_WIDTH, MAX_FIGURE_WIDTH);
    std::size_t h = random(MIN_FIGURE_HEIGHT, MAX_FIGURE_HEIGHT);
    std::size_t x = random(std::size_t{0}, INPUT_WIDTH - w);
    std::size_t y = random(std::size_t{0}, INPUT_HEIGHT - h);
    Layer input(INPUT_HEIGHT * INPUT_WIDTH, 0.0f);
    for (std::size_t row = 0; row < INPUT_HEIGHT; ++row) {
        for (std::size_t col = 0; col < INPUT_WIDTH; ++col) {
            if (row >= y && row < y + h &&
                    col >= x && col < x + w) {
                input[row * INPUT_WIDTH + col] = 1.0f;
            }
        }
    }
    return input;
}

Layer generate_random_circle() {
    std::size_t r = random(MIN_FIGURE_WIDTH / 2, MAX_FIGURE_WIDTH / 2);    
    std::size_t x = random(r, INPUT_WIDTH - r);
    std::size_t y = random(r, INPUT_HEIGHT - r);
    Layer input(INPUT_HEIGHT * INPUT_WIDTH, 0.0f);
    for (std::size_t row = 0; row < INPUT_HEIGHT; ++row) {
        int dy = row - y;
        for (std::size_t col = 0; col < INPUT_WIDTH; ++col) {
            int dx = col - x;
            if (dy * dy + dx * dx < int(r * r)) {
                input[row * INPUT_WIDTH + col] = 1.0f;
            }
        }
    }
    return input;
}

std::vector<LabeledInput> make_labeled_dataset(std::size_t size) {
    std::vector<LabeledInput> dataset;
    dataset.reserve(size);
    for (std::size_t i = 0; i < (size / 2); ++i) {
        dataset.push_back({generate_random_rectangle(), Label::RECTANGLE});
        dataset.push_back({generate_random_circle(), Label::CIRCLE});
    };
    return dataset;
}
