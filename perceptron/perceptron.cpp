#include <stdexcept>
#include <iostream>
#include <iomanip>

#include "perceptron.hpp"

Perceptron::Perceptron(float bias)
: bias{bias}, weights(INPUT_WIDTH * INPUT_HEIGHT, 0.0f), output{0.0f} {
}

Perceptron::Perceptron(float bias, std::vector<float>&& weights) 
: bias{bias}, weights{std::move(weights)} {
}

void Perceptron::fit(const std::vector<LabeledInput>& labeled_input) {
    for (std::size_t x = 0; x < labeled_input.size(); ++x) {
        const Layer& sample = labeled_input[x].first;
        Label label = labeled_input[x].second;
        float total = 0.0f;
        for (std::size_t i = 0; i < sample.size(); ++i) {
            total += sample[i] * this->weights[i];
        }

        bool should_fire = label == Label::CIRCLE;
        bool fired = total > this->bias;
        int factor = -1;

        if ((should_fire && !fired) || (!should_fire && fired)) {
            if (!fired) factor = 1;
            for (std::size_t i = 0; i < sample.size(); ++i) {
                weights[i] += sample[i] * factor;
            }
        }
    }
}

bool Perceptron::predict(const Layer& sample) {
    float total = 0.0f;
    for (std::size_t i = 0; i < sample.size(); ++i) {
        total += sample[i] * this->weights[i];
    }

    bool fired = total > this->bias;
    /* std::cout << "    Total: " << total */
    /*           << "  Bias: " << bias */
    /*           << "  Fired: " << fired << '\n'; */

    return fired;
}

const std::vector<float>& Perceptron::get_weights() const {
    return this->weights;
}

