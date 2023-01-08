#include <array>
#include <cstdio>
#include <iostream>
#include <iomanip>

#include "data.hpp"
#include "perceptron.hpp"
#include "io.hpp"

inline const float BIAS = 2.0f;
inline const std::size_t TRAIN_DATASET_SIZE = 5000;
inline const std::size_t TEST_DATASET_SIZE = 100;

Perceptron create_perceptron(int argc, char* argv[]) {
    if (argc != 2) {
        Perceptron perceptron{BIAS};
        std::clog << "== Training" << std::endl;
        std::vector<LabeledInput> train_dataset = make_labeled_dataset(TRAIN_DATASET_SIZE);
        perceptron.fit(train_dataset);
        return perceptron;
    }
    return Perceptron{BIAS, load_model(argv[1])};
}

int main(int argc, char* argv[]) {
    auto perceptron = create_perceptron(argc, argv);

    /* save_model(perceptron.get_weights(), "model.bin"); */

    std::cout << "== Tests\n";
    std::vector<LabeledInput> test_dataset = make_labeled_dataset(TEST_DATASET_SIZE);

    std::size_t tp = 0;
    std::size_t fp = 0;
    std::size_t tn = 0;
    std::size_t fn = 0;

    for (auto i : test_dataset) {
        /* print_layer(i.first); */
        /* std::cout << '\n'; */

        bool fired = perceptron.predict(i.first);
        Label y_true = i.second;

        if (y_true == Label::CIRCLE) {
            if (fired) ++tp; else ++fn;
        } else {
            if (fired) ++fp; else ++tn;
        }
    }

    const float accuracy = float(tp + tn) / TEST_DATASET_SIZE;
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

