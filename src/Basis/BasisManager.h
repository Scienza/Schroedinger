#include <Base.h>
class BasisManager
{
private:
	static inline BasisManager* instance = 0;
	std::vector<Base> basis;

	// @TODO: add here a list of basis
	BasisManager();

public:
	static BasisManager* getInstance();
	// @TODO: add here methods to create basis, to get basis list, and then get a single base
	BasisManager(const BasisManager&)			 = delete;
	BasisManager& operator=(const BasisManager&) = delete;
};
