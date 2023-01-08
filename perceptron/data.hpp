#ifndef AZ_DATA_HPP_
#define AZ_DATA_HPP_

#include <vector>
#include <utility>
#include <iostream>

inline const std::size_t INPUT_WIDTH = 200;
inline const std::size_t INPUT_HEIGHT = 200;

enum class Label {
    RECTANGLE,
    CIRCLE
};

using Layer = std::vector<float>;
using Labels = std::vector<Label>;
using LabeledInput = std::pair<Layer, Label>;

struct Point {
    int x;
    int y;
};

Layer generate_random_rectangle();
Layer generate_random_circle();
std::vector<LabeledInput> make_labeled_dataset(std::size_t size);

#endif // AZ_DATA_HPP_
