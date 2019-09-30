#include "Potential.h"

#include <utility>
#include <spdlog/fmt/bundled/format.h>

Potential::Potential(Base i_base, std::vector<std::vector<double>> potentialValues)
    : base(std::move(i_base)), values(std::move(potentialValues)) {}

Potential::Potential(Base i_base, PotentialType i_type, double i_k, double i_width, double i_height)
    : base(std::move(i_base)), type(i_type), k(i_k), width(i_width), height(i_height) {

    // Evaluation
    switch (type) {
        case BOX_POTENTIAL:
            this->box_potential();
            break;
        case HARMONIC_OSCILLATOR:
            this->ho_potential();
            break;
        case FINITE_WELL_POTENTIAL:
            this->finite_well_potential();
            break;
        default:
            throw std::invalid_argument("Wrong potential type or initialization meaningless!");
    }
}

void Potential::ho_potential() {

    for (ContinuousBase b : this->base.getContinuous()) {
        std::vector<double> x = b.getCoords();
        std::vector<double> v = std::vector<double>(b.getCoords().size(), 0);

        int i = 0;
        for (double value : x) {
            v[i] = (value * value * this->k);
            i++;
        }

        this->values.push_back(v);
    }

    for (DiscreteBase b : this->base.getDiscrete()) {
        std::vector<int> x = b.getCoords();
        std::vector<double> v(x.begin(), x.end());
        std::fill(v.begin(), v.end(), 0.0);

        int i = 0;
        for (double value : x) {
            v[i] = (value * value * this->k);
            i++;
        }

        this->values.push_back(v);
    }
}

void Potential::box_potential() {

    for (ContinuousBase b : this->base.getContinuous()) {
        std::vector<double> v = std::vector<double>(b.getCoords().size());
        std::fill(v.begin(), v.end(), 0.0);
        this->values.push_back(v);
    }

    for (DiscreteBase b : this->base.getDiscrete()) {
        std::vector<int> x = b.getCoords();
        std::vector<double> v(x.begin(), x.end());
        std::fill(v.begin(), v.end(), 0.0);
        this->values.push_back(v);
    }
}

void Potential::finite_well_potential() {

    for (ContinuousBase b : this->base.getContinuous()) {
        std::vector<double> v = std::vector<double>(b.getCoords().size(), 0);

        int i = 0;
        for (double value : b.getCoords()) {
            v[i] = (value > -this->width / 2.0 && value < this->width / 2.0) ? 0.0 : this->height;
            i++;
        }
        this->values.push_back(v);
    }

    for (DiscreteBase b : this->base.getDiscrete()) {
        std::vector<int> x = b.getCoords();
        std::vector<double> v(x.begin(), x.end());
        std::fill(v.begin(), v.end(), 0.0);
        int i = 0;
        for (double value : x) {
            v[i] = (value > -this->width / 2.0 && value < this->width / 2.0) ? 0.0 : this->height;
            i++;
        }
        this->values.push_back(v);
    }
}

void Potential::printToFile() {
    std::ofstream myfile("potential.dat");
    if (myfile.is_open()) {
        myfile << toString();
    }
}

std::string Potential::toString() const {
    std::vector<std::vector<double>> arr = getValues();
    // number of arrays
    int n = arr.size();

    // to keep track of next element in each of
    // the n arrays
    std::vector<int> indices(n, 0);
    fmt::memory_buffer writer;

    while (1) {

        // print current combination
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr[i][indices[i]];
        }
        format_to(writer, "{} \n", sum);

        // find the rightmost array that has more
        // elements left after the current element
        // in that array
        int next = n - 1;
        while (next >= 0 && (indices[next] + 1 >= arr[next].size())) next--;

        // no such array is found so no more
        // combinations left
        if (next < 0) break;

        // if found move to next element in that
        // array
        indices[next]++;

        // for all arrays to the right of this
        // array current index again points to
        // first element
        for (int i = next + 1; i < n; i++) indices[i] = 0;
    }

    return to_string(writer);
}

// Create a potential having all vectors of both potentials
const Potential operator+(const Potential& potential1, const Potential& potential2) {
    std::vector<std::vector<double>> potential_values{};

    for (std::vector<double> dimensions : potential1.getValues())
        potential_values.push_back(dimensions);

    for (std::vector<double> dimensions : potential2.getValues())
        potential_values.push_back(dimensions);

    return {potential1.getBase() + potential2.getBase(), potential_values};
}

Potential& Potential::operator+=(const Potential& potential2) {
    for (std::vector<double> vals : potential2.getValues()) this->values.push_back(vals);

    return *this;
}
