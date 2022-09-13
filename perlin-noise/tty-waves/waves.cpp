#include <thread>
#include <chrono>
#include <iostream>

#define DB_PERLIN_IMPL
#include "db_perlin.hpp"

int main() {
    using namespace std::chrono_literals;

    const int rows = 500;
    const auto sleep_duration = 10ms;
    const int max_length = 150;
    const float xinc = 0.02f;

    float xoff = 0.1;
    for (int row; row < rows; ++row) {
        float noise = 0.5 + (0.5 * db::perlin(xoff));
        for (int rep = 0; rep < noise * max_length; ++rep) {
            std::cout << '#';
        }
        std::cout << '\n';
        xoff += xinc;
        std::this_thread::sleep_for(sleep_duration);
    }
}

