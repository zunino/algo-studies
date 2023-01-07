#include <stdexcept>
#include <iostream>
#include <iomanip>

#include "perceptron.hpp"

Perceptron::Perceptron(float bias) : output{0.0f}, bias{bias} {
    /* std::generate(this->weights.begin(), this->weights.end(), random_normalized_float); */
}

void Perceptron::fit(std::vector<LabeledInput>&& labeled_input) {
    this->weights.resize(INPUT_WIDTH * INPUT_HEIGHT);
    for (std::size_t x = 0; x < labeled_input.size(); ++x) {
        Input& sample = labeled_input[x].first;
        Label label = labeled_input[x].second;
        float total = 0.0f;
        for (std::size_t i = 0; i < sample.size(); ++i) {
            total += sample[i].value * this->weights[i];
        }

        bool should_fire = label == Label::CIRCLE;
        bool fired = total > this->bias;
        int factor = -1;

        if (should_fire && !fired || !should_fire && fired) {
            if (!fired) {
                factor = 1;
            }
            for (std::size_t i = 0; i < sample.size(); ++i) {
                weights[i] += sample[i].value * factor;
            }
        }
    }
}

bool Perceptron::predict(const Input& sample) {
    float total = 0.0f;
    for (std::size_t i = 0; i < sample.size(); ++i) {
        total += sample[i].value * this->weights[i];
    }

    bool fired = total > this->bias;
    std::cout << "    Total: " << total
              << "  Bias: " << bias
              << "  Fired: " << fired << '\n';

    return fired;
}

void Perceptron::print_weights() const {
    std::size_t char_count = 0;
    for (auto w : this->weights) {
        std::cout << std::setw(3) << std::right << w << ' ';
        ++char_count;
        if (char_count > 19) {
            char_count = 0;
            std::cout << '\n';
        }
    }
    std::cout << '\n';
}
