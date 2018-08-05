#include <iostream>
#include <string>
#include <BasisManager.h>
#include <Potential.h>
#include <Schroedinger.h>

int main(int argc, char **argv) {

	BasisManager::Builder b = BasisManager::Builder();
	BasisManager::getInstance()->addBase( b.addDiscrete(0, 5, 1)
					   .addContinuous(-5.0, 5.0, 0.01)
					   .build()
	);
	std::vector<Base> basis = BasisManager::getInstance()->getBasisList();
	return 0;
}