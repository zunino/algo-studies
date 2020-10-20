/**
 * Algorithm for picking a random element from a collection taking
 * selection probability into account. The motivation came from my
 * studies of genetic algorithms.
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

std::size_t prob_select(const std::vector<Character>& coll) {
    float prob_sum = std::accumulate(
        std::begin(coll),
        std::end(coll),
        0.0f,
        [](float total, const auto& e) { return total + e.prob; }
    );
    std::uniform_real_distribution<float> dist{0.0f, prob_sum};
    std::size_t idx = 0;
    float stacked_prob = 0.0f;
    for (float rand_prob = dist(rng); idx < coll.size(); ++idx) {
        auto& elem = coll[idx];
        stacked_prob += elem.prob;
        if (rand_prob < stacked_prob) {
            break;
        }
    }
    return idx;
}

int main() {
    std::vector<Character> characters{
        Character{"John", 0.5f},
        Character{"Dutch", 0.2f},
        Character{"Sadie", 0.3f}
    };
    
    const std::size_t picks = 10000;
    for (std::size_t i = 0; i < picks; ++i) {
        std::size_t pick = prob_select(characters);
        ++characters[pick].count;
    }

    for (const auto& c : characters) {
        std::cout << c.name << " picked " << c.count << " out of " << picks <<
            " times (" << std::setprecision(4) << (c.count*100.0f / picks) << "%)\n";
    }
}

