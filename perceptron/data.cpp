#include <stdexcept>
#include <cmath>

#include "random.hpp"
#include "data.hpp"

constexpr int MIN_FIGURE_WIDTH = 0.5f * INPUT_WIDTH;
constexpr int MIN_FIGURE_HEIGHT = 0.5f * INPUT_HEIGHT;

constexpr int MAX_FIGURE_WIDTH = 0.95f * INPUT_WIDTH;
constexpr int MAX_FIGURE_HEIGHT = 0.95f * INPUT_HEIGHT;

NormalizedFloat::NormalizedFloat() : value{0.0f} {
}

NormalizedFloat::NormalizedFloat(float n) {
    if (n < -1.0f || n > 1.0f) {
        throw std::invalid_argument{"Value out of range"};
    }
    this->value = n;
}

ActivationValue::ActivationValue() : value{0.0f} {
}

ActivationValue::ActivationValue(float value) {
    if (value < 0.0f || value > 1.0f) {
        throw std::invalid_argument{"Activation value out of range"};
    }
    this->value = value;
}

Input generate_random_rectangle() {
    std::size_t w = random(MIN_FIGURE_WIDTH, MAX_FIGURE_WIDTH);
    std::size_t h = random(MIN_FIGURE_HEIGHT, MAX_FIGURE_HEIGHT);
    std::size_t x = random(std::size_t{0}, INPUT_WIDTH - w);
    std::size_t y = random(std::size_t{0}, INPUT_HEIGHT - h);
    Input input(INPUT_HEIGHT * INPUT_WIDTH, ActivationValue{0.0f});
    for (std::size_t row = 0; row < INPUT_HEIGHT; ++row) {
        for (std::size_t col = 0; col < INPUT_WIDTH; ++col) {
            if (row >= y && row < y + h &&
                    col >= x && col < x + w) {
                input[row * INPUT_WIDTH + col] = ActivationValue{1.0f};
            }
        }
    }
    return input;
}

Input generate_random_circle() {
    std::size_t r = random(MIN_FIGURE_WIDTH / 2, MAX_FIGURE_WIDTH / 2);    
    std::size_t x = random(r, INPUT_WIDTH - r);
    std::size_t y = random(r, INPUT_HEIGHT - r);
    Input input(INPUT_HEIGHT * INPUT_WIDTH, ActivationValue{0.0f});
    for (std::size_t row = 0; row < INPUT_HEIGHT; ++row) {
        int dy = row - y;
        for (std::size_t col = 0; col < INPUT_WIDTH; ++col) {
            int dx = col - x;
            if (dy * dy + dx * dx < int(r * r)) {
                input[row * INPUT_WIDTH + col] = ActivationValue{1.0f};
            }
        }
    }
    return input;
}
