#ifndef AZ_PERCEPTRON_HPP_
#define AZ_PERCEPTRON_HPP_

#include <cstddef>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "data.hpp"

struct Perceptron {
    Perceptron(float bias);
    void fit(std::vector<LabeledInput>&& labeled_input);
    bool predict(const Input& x);
    void print_weights() const;
private:
    std::vector<float> weights;
    ActivationValue output;
    float bias;
};

#endif // AZ_PERCEPTRON_HPP_
