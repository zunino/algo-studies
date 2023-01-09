#include "random.hpp"

#include <random>
#include <utility>

inline const int SEED = 117;

namespace {
    std::default_random_engine randEng{SEED};
}

int random(std::size_t from, std::size_t to) {
    if (from > to) {
        std::swap(from, to);
    }
    std::uniform_int_distribution<int> dist(from, to);
    return dist(randEng);
}

int random(std::size_t to) {
    return random(std::size_t{0}, to);
}

int random(int from, int to) {
    if (from > to) {
        std::swap(from, to);
    }
    std::uniform_int_distribution<int> dist(from, to);
    return dist(randEng);
}

int random(int to) {
    return random(0, to);
}

float random(float from, float to) {
    std::uniform_real_distribution<float> dist(from, to);
    return dist(randEng);
}

float random(float to) {
    return random(0.0f, to);
}
