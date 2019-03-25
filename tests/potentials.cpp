#include <gtest/gtest.h>
#include "Potential.h"
#include "BasisManager.h"
#include "Solver.h"

TEST(Potentials, widthMustBePositive) {
    Base b;
    try {
        Potential p = Potential::Builder(b).setWidth(-1).build();
        FAIL();
    }
    catch (std::invalid_argument e) {}
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
    Potential V = potentialBuilder.setType(Potential::PotentialType::HARMONIC_OSCILLATOR)
								  .setK(k)
								  .build();

    // Save the Harmonic Hoscillator potential and basis to file
    V.printToFile();

    // Istantiate a potential builder giving a filename in the constructor
    // then get a potential object calling the build method
    Potential::Builder otherPotentialBuilder("potential.dat");
    Potential VfromFile = otherPotentialBuilder.build();

    auto originalValues = V.getValues();
    auto readValues     = VfromFile.getValues();

    if (originalValues.size() != readValues.size())
        FAIL() << "Size of original values ( " << originalValues.size() << ") and read values (" << readValues.size() << ") not corresponding";

    for (int i = 0; i < originalValues.size(); i++) {
        ASSERT_NEAR(originalValues[i], readValues[i], err_thres);
    }
}

