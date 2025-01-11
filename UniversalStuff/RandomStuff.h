#ifndef RANDOMSTUFF_H
#define RANDOMSTUFF_H

#include <random>
#include <vector>
#include <string>
#include <variant>

#include "../PlayerStuff/Money/JobStuff.h"
class job;


template <typename T>
concept IsVector = requires(T t) {
    typename T::value_type; // Requires the type to have a value_type
    std::declval<T>().begin(); // Requires the type to have a begin()
};

using AllVariant = std::variant<unsigned short, short, unsigned, int, float, double, std::string, job>;

double random(double min, double max);
std::vector<double> chanceDistribution(std::vector<double> weights);

template <typename Vector>
AllVariant randomElement(const Vector elements, std::vector<int> weights);

#endif // RANDOMSTUFF_H
