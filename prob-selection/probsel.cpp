/**
 * Algorithm for picking a random element from a collection taking selection
 * probability into account. The motivation came from my studies of genetic
 * algorithms.
 *
 * Given an indexable collection of elements with associated probabilities,
 * a random number between 0 and the sum of all probabilities is generated.
 * The idea is to think of the elements as being stacked and then to find
 * on which element that random number falls. As the elements on the stack
 * are iterated upon, their probability is accumulated and the previously
 * generated random number is comparted to the accumulated probability.
 *
 * Andre Zunino <neyzunino@gmail.com>
 * 20 October 2020
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>

namespace {
    std::random_device rd;
    std::mt19937 rng{rd()};
}

struct Character {
    const char* name;
    float prob;

    int count = 0;
};

template <typename Dist>
std::size_t prob_select(const std::vector<Character>& coll, Dist& dist) {
    float rand_prob = dist(rng);
    std::size_t idx = 0;
    for (float stacked_prob = 0.0f; idx < coll.size(); ++idx) {
        auto& elem = coll[idx];
        stacked_prob += elem.prob;
        if (rand_prob < stacked_prob) {
            break;
        }
    }
    return idx;
}

float sum_of_probabilites(const std::vector<Character>& coll) {
    return std::accumulate(
        std::begin(coll),
        std::end(coll),
        0.0f,
        [](float total, const auto& e) { return total + e.prob; }
    );
}

int main() {
    std::vector<Character> characters{
        Character{"John", 0.5f},
        Character{"Dutch", 0.2f},
        Character{"Sadie", 0.3f}
    };
    
    std::uniform_real_distribution<float> dist{0.0f, sum_of_probabilites(characters)};
    const std::size_t picks = 10000;
    for (std::size_t i = 0; i < picks; ++i) {
        std::size_t pick = prob_select(characters, dist);
        ++characters[pick].count;
    }

    for (const auto& c : characters) {
        std::cout << c.name << " picked " << c.count << " out of " << picks <<
            " times (" << std::setprecision(4) << (c.count*100.0f / picks) << "%)\n";
    }
}

