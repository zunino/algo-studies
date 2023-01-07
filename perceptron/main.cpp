#include <array>
#include <iostream>
#include <iomanip>

#include "data.hpp"
#include "perceptron.hpp"

void print_input(const Input& input, std::ostream& os = std::cout) {
    for (std::size_t row = 0; row < INPUT_HEIGHT; ++row) {
        os << std::setw(3) << std::right << row << ' ';
        for (std::size_t col = 0; col < INPUT_WIDTH; ++col) {
            float value = input[row * INPUT_WIDTH + col].value;
            os << (value == 1.0f ? "\u2588\u2588" : "..");
        }
        os << '\n';
    }
}

std::vector<LabeledInput> make_labeled_dataset(std::size_t quantity) {
    std::vector<LabeledInput> dataset;
    dataset.reserve(quantity);
    for (std::size_t i = 0; i < (quantity / 2); ++i) {
        dataset.push_back({generate_random_rectangle(), Label::RECTANGLE});
        dataset.push_back({generate_random_circle(), Label::CIRCLE});
    };
    return dataset;
}

int main() {
    std::vector<LabeledInput> train_dataset = make_labeled_dataset(10000);

    auto p = Perceptron{2.0f};

    std::cout << "== Training" << std::endl;
    p.fit(std::move(train_dataset));

    std::cout << "== Tests\n";

    const std::size_t n_test_samples = 100;
    std::vector<LabeledInput> test_dataset = make_labeled_dataset(n_test_samples);

    std::size_t tp = 0;
    std::size_t fp = 0;
    std::size_t tn = 0;
    std::size_t fn = 0;

    for (auto i : test_dataset) {
        print_input(i.first);
        bool fired = p.predict(i.first);
        Label expected = i.second;
        if (fired) {
            if (expected == Label::CIRCLE) {
                ++tp;
            } else {
                ++fp;
            }
        } else {
            if (expected == Label::RECTANGLE) {
                ++tn;
            } else {
                ++fn;
            }
        }
        std::cout << '\n';
    }

    const float accuracy = float(tp + tn) / n_test_samples;
    const float precision = tp / float(tp + fp);
    const float recall = tp / float(tp + fn);
    const float f1_score = 2 * (precision * recall / (precision + recall));

    std::cout << "== Summary\n";
    std::cout << "TP:        " << tp << '\n';
    std::cout << "FP:        " << fp << '\n';
    std::cout << "TN:        " << tn << '\n';
    std::cout << "FN:        " << fn << '\n';
    std::cout << "Accuracy:  " << std::setprecision(3) << accuracy << '\n';
    std::cout << "Precision: " << std::setprecision(3) << precision << '\n';
    std::cout << "Recall:    " << std::setprecision(3) << recall << '\n';
    std::cout << "F1-Score:  " << std::setprecision(3) << f1_score << '\n';
}

