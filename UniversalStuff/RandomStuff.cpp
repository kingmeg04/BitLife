#include "RandomStuff.h"
#include <stdexcept> // Für std::invalid_argument
#include <random>
#include <vector>

using namespace std;

double random(double min, double max) {
    static random_device rd;  // Seed
    static mt19937 gen(rd()); // Zufallszahlengenerator
    uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

vector<double> chanceDistribution(vector<double> weights) {
    int sum = 0;
    for (double weight : weights) {
        sum += weight;
    }
    for (double& weight : weights) {
        weight /= sum;
    }
    return weights;
}

template <typename Vector>
AllVariant randomElement(const Vector& elements, vector<double> weights) {
    // Überprüfen, ob Elemente und Gewichte gleich groß sind
    if (elements.size() != weights.size()) {
        throw invalid_argument("Elements and weights must have the same size.");
    }

    // Zufallszahlengenerator
    random_device rd;
    mt19937 gen(rd());

    // Diskrete Verteilung basierend auf den Gewichten
    discrete_distribution<> dist(weights.begin(), weights.end());

    // Zufälliges Element basierend auf der Verteilung zurückgeben
    return elements[dist(gen)];
}

// Explizite Template-Instanziierung
template AllVariant randomElement<std::vector<job>>(const std::vector<job>&, std::vector<double>);
