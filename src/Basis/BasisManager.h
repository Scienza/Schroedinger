#include <Base.h>
class BasisManager
{

public:
	enum Source { MEMORY = 0, FILE = 1 }; 
	
	static BasisManager *getInstance();
	const std::vector<Base>& getBasisList(Source);
	const std::vector<Base>& getBasisList();
	void addBase(Base);

	class Builder {
		std::vector<DiscreteDimension> d_dim;
		std::vector<ContinuousDimension> c_dim;
	public:
		 Base build(Base::BaseType, int dimension);
		 Builder addDiscreteDimension(int, int, int);
		 Builder addContinuousDimension(double, unsigned int);
		 Builder addContinuousDimension(double, double, double);
		 Builder addContinuousDimension(double, double, unsigned int);
	};
	
	BasisManager(const BasisManager&)           = delete;
	BasisManager& operator=(const BasisManager) = delete;

private:
	std::vector<Base> basis;
	static BasisManager* instance;
	BasisManager() {}
};
