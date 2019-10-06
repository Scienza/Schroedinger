/*
 * Schroedinger - Scienza (c) 2019
 * Released under the GNU LGPL2.1
 * See the included LICENSE for details
 */
#include <gtest/gtest.h>
#include "BasisManager.h"
#include "Potential.h"
#include "Solver.h"

TEST(Potentials, widthMustBePositive) {
    Base b;
    try {
        Potential p = Potential::Builder(b).setWidth(-1).build();
        FAIL();
    } catch (std::invalid_argument e) {
    }
}

// Check if finite well potential written to file can be
// successfully created from it
TEST(Potentials, createAndReadFromFile) {
    unsigned int nbox = 1000;
    double mesh       = 0.01;
    double k          = 1.0;
    int dimension     = 1;

    BasisManager::Builder baseBuilder;
    Base base = baseBuilder.addContinuous(mesh, nbox).build(dimension);

    Potential::Builder potentialBuilder(base);
    Potential V =
        potentialBuilder.setType(Potential::PotentialType::HARMONIC_OSCILLATOR).setK(k).build();

    V.printToFile();

    // Istantiate a potential builder giving a filename in the constructor
    // then get a potential object calling the build method
    Potential::Builder otherPotentialBuilder("potential.dat", base);
    Potential VfromFile = otherPotentialBuilder.build();

    std::vector<double> originalValues = V.getValues().at(0);
    std::vector<double> readValues     = VfromFile.getValues().at(0);

    if (originalValues.size() != readValues.size())
        FAIL() << "Size of original values ( " << originalValues.size() << ") and read values ("
               << readValues.size() << ") not corresponding";

    for (int i = 0; i < originalValues.size(); i++) {
        ASSERT_NEAR(originalValues[i], readValues[i], err_thres);
    }
}

TEST(Potentials, PotentialsConcatenation) {
    unsigned int nbox = 1000;
    double mesh       = 0.01;
    double k          = 1.0;
    int dimension     = 1;

    BasisManager::Builder baseBuilder;
    Base base  = baseBuilder.addContinuous(mesh, nbox).build(dimension);
    Base base2 = baseBuilder.addContinuous(mesh, nbox).build(dimension);

    Potential::Builder potentialBuilder(base);
    Potential V1 =
        potentialBuilder.setType(Potential::PotentialType::HARMONIC_OSCILLATOR).setK(k).build();

    Potential V2 =
        potentialBuilder.setType(Potential::PotentialType::HARMONIC_OSCILLATOR).setK(k).build();

    Potential V3 = V1 + V2;

    std::vector<double> firstPotentialValues  = V1.getValues().at(0);
    std::vector<double> secondPotentialValues = V2.getValues().at(0);

    if (V3.getValues().size() != 2) FAIL() << "Size of final values vector is not corresponding";

    // Check if the values matches
    for (int i = 0; i < V3.getValues().at(0).size(); i++) {
        ASSERT_NEAR(firstPotentialValues[i], V3.getValues().at(0).at(i), err_thres);
    }

    for (int i = 0; i < V3.getValues().at(1).size(); i++) {
        ASSERT_NEAR(secondPotentialValues[i], V3.getValues().at(1).at(i), err_thres);
    }
}
TEST(Potentials, PotentialsConcatenationAndAssignment) {
    unsigned int nbox = 1000;
    double mesh       = 0.01;
    double k          = 1.0;
    int dimension     = 1;

    BasisManager::Builder baseBuilder;
    Base base  = baseBuilder.addContinuous(mesh, nbox).build(dimension);
    Base base2 = baseBuilder.addContinuous(mesh, nbox).build(dimension);

    Potential::Builder potentialBuilder(base);
    Potential V1 =
        potentialBuilder.setType(Potential::PotentialType::HARMONIC_OSCILLATOR).setK(k).build();
    std::vector<double> firstPotentialValues = V1.getValues().at(0);

    Potential V2 =
        potentialBuilder.setType(Potential::PotentialType::HARMONIC_OSCILLATOR).setK(k).build();
    std::vector<double> secondPotentialValues = V2.getValues().at(0);

    V1 += V2;

    if (V1.getValues().size() != 2) FAIL() << "Size of final values vector is not corresponding";

    // Check if the values matches
    for (int i = 0; i < V1.getValues().at(0).size(); i++) {
        ASSERT_NEAR(firstPotentialValues[i], V1.getValues().at(0).at(i), err_thres);
    }

    for (int i = 0; i < V1.getValues().at(1).size(); i++) {
        ASSERT_NEAR(secondPotentialValues[i], V1.getValues().at(1).at(i), err_thres);
    }
}
