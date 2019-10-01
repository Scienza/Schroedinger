#include "Base.h"
#include "BasisManager.h"
#include "LogManager.h"

#include <spdlog/fmt/bundled/format.h>

Base::Base(const std::vector<double>& coords) {
    this->dimensions = 1;
    this->continuous.emplace_back(coords);
    this->boundary = ZEROEDGE;
}

Base::Base(basePreset t, int n_dimension, std::vector<ContinuousBase> c_base,
           std::vector<DiscreteBase> d_base) {

    switch (t) {
        // TODO: add here, for each base type, a control for dimensions
        case Custom:
            S_INFO("Initializing custom basis");
            break;
        case Cartesian:
            S_INFO("Initializing cartesian basis");
            break;
        case Spherical:
            S_INFO("Initializing Spherical Basis");
            break;
        case Cylindrical:
            S_INFO("Initializing Cylindrical Basis");
            break;
        default:
            throw std::invalid_argument("Wrong basis type or initialization meaningless!");
            break;
    }

    this->dimensions = n_dimension;
    this->continuous.insert(continuous.end(), c_base.begin(), c_base.end());
    this->discrete.insert(discrete.end(), d_base.begin(), d_base.end());
    this->boundary = ZEROEDGE;

    BasisManager::getInstance()->selectBase(*this);
};

std::string Base::toString() const {
    std::vector<std::vector<double>> arr;
    for (auto& c : getContinuous()) {
        arr.emplace_back(c.getCoords());
    }

    // number of arrays
    int n = arr.size();

    // to keep track of next element in each of
    // the n arrays
    std::vector<int> indices(n, 0);
    fmt::memory_buffer writer;

    while (1) {
        // print current combination
        for (int i = 0; i < n; i++) format_to(writer, "{} ", arr[i][indices[i]]);
        format_to(writer, "\n");

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

const Base operator+(const Base& base1, const Base& base2) {
    std::vector<DiscreteBase> discrete_dimension{};
    discrete_dimension.insert(discrete_dimension.begin(), base1.getDiscrete().begin(),
                              base1.getDiscrete().end());
    discrete_dimension.insert(discrete_dimension.begin(), base2.getDiscrete().begin(),
                              base2.getDiscrete().end());

    std::vector<ContinuousBase> continuous_dimension{};
    continuous_dimension.insert(continuous_dimension.begin(), base1.getContinuous().begin(),
                                base1.getContinuous().end());
    continuous_dimension.insert(continuous_dimension.begin(), base2.getContinuous().begin(),
                                base2.getContinuous().end());

    return {Base::basePreset::Custom, (base1.getDim() + base2.getDim()), continuous_dimension,
            discrete_dimension};
}

Base& Base::operator+=(const Base& base2) {
    discrete.insert(discrete.begin(), base2.getDiscrete().begin(), base2.getDiscrete().end());

    continuous.insert(continuous.begin(), base2.getContinuous().begin(),
                      base2.getContinuous().end());

    // You have to upload also the dimension HERE
    return *this;
}

// This method let you get basis coords when it has only one dimension
std::vector<double> Base::getCoords() const {
    if (this->getContinuous().size() == 1) {
        std::vector<double> toreturn = this->getContinuous().at(0).getCoords();
        return toreturn;
    } else if (this->getDiscrete().size() == 1) {
        // tricky conversion taking each std::vector<int> value and returning a final
        // std::vector<double>
        std::vector<int> original_coords = this->getDiscrete().at(0).getCoords();
        std::vector<double> toreturn =
            std::vector<double>(original_coords.begin(), original_coords.end());
        return toreturn;
    } else {
        throw std::runtime_error(
            "Can't get coords from multidimensional basis using this method. ");
    }
}
