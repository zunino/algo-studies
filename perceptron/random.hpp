#ifndef AZ_RANDOM_HPP_
#define AZ_RANDOM_HPP_

#include <cstddef>

int random(std::size_t from, std::size_t to);
int random(std::size_t to);

int random(int from, int to);
int random(int to);

float random(float from, float to);
float random(float to);

#endif // AZ_RANDOM_HPP_
