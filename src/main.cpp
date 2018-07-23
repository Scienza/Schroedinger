#include <iostream>
#include <string>
#include <BasisManager.h>
#include <Potential.h>
#include <Schroedinger.h>

int main(int argc, char **argv) {

	BasisManager::Builder b = BasisManager::Builder();
	BasisManager *manager = BasisManager::getInstance();

	manager->addBase( b.addDiscreteDimension(0, 5, 1)
					   .addContinuousDimension(-5.0, 5.0, 0.01)
					   .build(Base::BaseType::Cartesian, 1)
	);

	std::vector<Base> basis = manager->getBasisList();

	return 0;
}