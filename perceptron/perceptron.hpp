#ifndef AZ_PERCEPTRON_HPP_
#define AZ_PERCEPTRON_HPP_

#include <vector>

#include "data.hpp"

struct Perceptron {
    Perceptron(float bias);
    Perceptron(float bias, std::vector<float>&& weigths);
    void fit(const std::vector<LabeledInput>& labeled_input);
    bool predict(const Layer& x);
    const std::vector<float>& get_weights() const;
private:
    float bias;
    std::vector<float> weights;
    float output;
};

#endif // AZ_PERCEPTRON_HPP_
