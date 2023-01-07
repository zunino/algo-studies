#ifndef AZ_DATA_HPP_
#define AZ_DATA_HPP_

#include <cstddef>
#include <vector>
#include <utility>

inline constexpr std::size_t INPUT_WIDTH = 60;
inline constexpr std::size_t INPUT_HEIGHT = 60;

struct NormalizedFloat {
    NormalizedFloat();
    NormalizedFloat(float n);
    float value;
};

struct ActivationValue {
    ActivationValue();
    ActivationValue(float value);
    float value;
};

enum class Label {
    RECTANGLE,
    CIRCLE
};

using Input = std::vector<ActivationValue>;
using Labels = std::vector<Label>;
using LabeledInput = std::pair<Input, Label>;

struct Point {
    int x;
    int y;
};

Input generate_random_rectangle();
Input generate_random_circle();

#endif // AZ_DATA_HPP_
