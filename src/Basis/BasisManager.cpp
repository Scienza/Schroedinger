#include <BasisManager.h>

BasisManager * BasisManager::getInstance()
{
	static BasisManager* instance;

	if (!instance) {
		instance = new BasisManager();
	};
	return instance;
};