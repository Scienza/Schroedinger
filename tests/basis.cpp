#include <algorithm>

#include <gtest/gtest.h>
#include "BasisManager.h"

#define err 1E-10

TEST(Basis, IsSingleton)
{
    BasisManager *m1 = BasisManager::getInstance();
    BasisManager *m2 = BasisManager::getInstance();
    ASSERT_EQ(m1, m2);
}

TEST(Basis, Dimension_1_continuous_mesh_nbox)
{
    unsigned int nbox = 1000;
    double mesh = 0.1;
    int dimension = 1;

    BasisManager::Builder b = BasisManager::Builder();
    Base base = b.addContinuous(mesh, nbox).build(dimension);

    ContinuousBase firstContinuousBase = base.getContinuous().at(0);
    std::vector<double> baseCoords = firstContinuousBase.getCoords();

    std::vector<double> groundTruthCoords; 
    groundTruthCoords.reserve(1001);

    double value = -50.0;
    for (int i = 0; i <= nbox; i++)  {
        groundTruthCoords.push_back(value);
        value+=mesh;
    }

    for (std::vector<int>::size_type i = 0; i <= baseCoords.size(); i++) 
        ASSERT_NEAR(groundTruthCoords[i], baseCoords[i], err);
}

TEST(Basis, Dimension_1_continuous_start_end_mesh)
{
    unsigned int nbox = 1000;
    double start = 0;
    double end = 100;
    double mesh = 0.1;
    int dimension = 1;

    BasisManager::Builder b = BasisManager::Builder();
    Base base = b.addContinuous(start, end, mesh).build(dimension);

    ContinuousBase firstContinuousBase = base.getContinuous().at(0);
    std::vector<double> baseCoords = firstContinuousBase.getCoords();

    std::vector<double> groundTruthCoords; 
    groundTruthCoords.reserve(1001);

    double value = 0.0;
    for (int i = 0; i <= nbox; i++)  {
        groundTruthCoords.push_back(value);
        value+=mesh;
    }

    for (std::vector<int>::size_type i = 0; i <= baseCoords.size(); i++)
        ASSERT_NEAR(groundTruthCoords[i], baseCoords[i], err);
}

TEST(Basis, Dimension_1_continuous_start_end_nbox)
{
    unsigned int nbox = 1000;
    double start = 0;
    double end = 100;
    double mesh = 0.1;
    int dimension = 1;

    BasisManager::Builder b = BasisManager::Builder();
    Base base = b.addContinuous(start, end, nbox).build(dimension);

    ContinuousBase firstContinuousBase = base.getContinuous().at(0);
    std::vector<double> baseCoords = firstContinuousBase.getCoords();

    std::vector<double> groundTruthCoords; 
    groundTruthCoords.reserve(1001);

    double value = 0.0;
    for (int i = 0; i <= nbox; i++)  {
        groundTruthCoords.push_back(value);
        value+=mesh;
    }

    for (std::vector<int>::size_type i = 0; i <= baseCoords.size(); i++)
        ASSERT_NEAR(groundTruthCoords[i], baseCoords[i], err);
}
