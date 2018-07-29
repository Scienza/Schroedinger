#include <Base.h>
class BasisManager
{

public:
	enum Source { MEMORY = 0, FILE = 1 };

	static BasisManager *getInstance();
	std::vector<Base> getBasisList(Source);
	std::vector<Base> getBasisList();
	Base selected;
	void selectBase(Base);
	void addBase(Base);

    class Builder {
		std::vector< DiscreteBase > d_base;
		std::vector< ContinuousBase > c_base;
	public:
        Base build();
        Base build(Base::basePreset, int dimension);
        Base build(Base::basePreset, int, double, int);

        Builder addDiscrete(int, int, int);
		Builder addContinuous(double, unsigned int);
		Builder addContinuous(double, double, double);
		Builder addContinuous(double, double, unsigned int);
	};

	BasisManager(const BasisManager&) = delete;
	BasisManager& operator=(const BasisManager) = delete;

private:
	std::vector<Base> bases;
	static BasisManager* instance;
	BasisManager() {}
};
