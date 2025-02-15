//
// Created by jbrui on 17.12.2024.
//

#include "RandomStuff.h"

using namespace std;

double random(double min, double max) { // this thing is generated by chatGPT but basically just float between input1 & input2
    static random_device rd;  // Seed
    static mt19937 gen(rd()); // Random number generator
    uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

vector<double> chanceDistribution(vector<double> weights) { // converts weights from absolute to relative values
    int sum = 0;
    for (int weight : weights) {
        sum += weight;
    }
    for (int weight : weights) {
        weight /= sum;
    }
    return weights;
}

// from chatGPT - dunno how it works, but it does (part 3/3)
// This is an explicit template instantiation (not needed if inline in header)
template AllVariant randomElement<vector<job>>(const vector<job>, vector<int>);
template AllVariant randomElement<vector<int>>(const vector<int>, vector<int>);
template AllVariant randomElement<vector<string>>(const vector<string>, vector<int>);

template <typename Vector> AllVariant randomElement(const Vector elements, vector<int> weights) {

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
//until here