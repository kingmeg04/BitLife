//
// Created by jbrui on 17.12.2024.
/

#include "RandomStuff.h"

using namespace std;

double random(double min, double max) {
    static random_device rd;  // Seed
    static mt19937 gen(rd()); // Random number generator
    uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

vector<double> chanceDistribution(vector<double> weights) {
    int sum = 0;
    for(int i = 0; i < weights.size(); i++) {
        sum += weights[i];
    }
    for(int i = 0; i < weights.size(); i++) {
        weights[i] /= sum;
    }
    return weights;
}

// This is an explicit template instantiation (not needed if inline in header)
template AllVariant randomElement<std::vector<job>>(const std::vector<job>&, std::vector<double>);

template <typename Vector> AllVariant randomElement(const Vector& elements, vector<double> weights) {

    // Ensure the weights and elements are the same size
    if (elements.size() != weights.size()) {
        throw invalid_argument("Elements and weights must have the same size.");
    }

    // Random number generator
    random_device rd;
    mt19937 gen(rd());

    // Create a discrete distribution based on the weights
    discrete_distribution<> dist(weights.begin(), weights.end());

    // Select and return a random element based on the distribution
    return elements[dist(gen)];
}