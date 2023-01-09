#ifndef AZ_IO_HPP_
#define AZ_IO_HPP_

#include <vector>
#include <iostream>

#include "data.hpp"

void print_layer(const Layer& layer, std::ostream& os = std::cout);
void print_weights(const std::vector<float>& weights, std::ostream& os = std::cout);
void save_layer_as_bmp(const Layer& layer, const char* file_path);
void save_weights_as_pgm(const std::vector<float>& weights, const char* file_path);
void save_model(const std::vector<float>& weights, const char* file_path);
std::vector<float> load_model(const char* file_path);

#endif // AZ_IO_HPP_
