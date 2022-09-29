#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include "IFunction/FunctionFactory.h"
#include "IFunction/EllipseFunction.h"
#include "IFunction/HyperbolaFunction.h"
#include <cmath>

using namespace std;

bool Save(const string& fileName, FunctionPtr* object, int count)
{
    ofstream outFile;
    outFile.open(fileName);

    Save(outFile, object, count);

    return true;
}

vector<FunctionPtr> Load(const char* filename)
{
    ifstream inFile;
    inFile.open(filename);

    auto objects = Load(inFile);

    return objects;
}

double GetRandomDouble()
{
    double fMin = -10.0;
    double fMax = 10.0;

    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

class TestFactory : public ::testing::Test
{
protected:
    void SetUp() {
        RegisterLoaders();
    }
    void TearDown() {}
};

TEST_F(TestFactory, EmptyFile)
{
    FunctionPtr objects[] = {};
    Save("EmptyFile.txt", objects, 0);

    vector<FunctionPtr> loadedObject = Load("EmptyFile.txt");

    ASSERT_EQ(loadedObject.size(), 0);
}

TEST_F(TestFactory, TooMuchObjectsFile)
{
    FunctionPtr objects[1000] = {};
    for (int i = 0; i < 1000; ++i) {
        FunctionPtr tempPtr(new EllipseFunction(GetRandomDouble(), GetRandomDouble()));
        objects[i] = tempPtr;
    }
    Save("ObjectsFile.txt", objects, 1000);

    vector<FunctionPtr> loadedObject = Load("ObjectsFile.txt");

    ASSERT_EQ(loadedObject.size(), 1000);
}

TEST_F(TestFactory, IntValues)
{
    FunctionPtr firstPtr(new EllipseFunction(2, 3));
    FunctionPtr secondPtr(new HyperbolaFunction(5, 10));

    FunctionPtr objects[] = { firstPtr, secondPtr };
    Save("IntFile.txt", objects, 2);

    vector<FunctionPtr> loadedObject = Load("IntFile.txt");

    ASSERT_NEAR(loadedObject[0]->Solve(0).first, 3, 0.01);
    ASSERT_NEAR(loadedObject[0]->Solve(0).second, -3, 0.01);
    ASSERT_NEAR(loadedObject[0]->Solve(2).first, 0, 0.01);
    ASSERT_NEAR(loadedObject[0]->Solve(2).second, 0, 0.01);
    ASSERT_NEAR(loadedObject[0]->Solve(-2).first, 0, 0.01);
    ASSERT_NEAR(loadedObject[0]->Solve(-2).second, 0, 0.01);

    ASSERT_NEAR(loadedObject[1]->Solve(5).first, 0, 0.01);
    ASSERT_NEAR(loadedObject[1]->Solve(5).second, 0, 0.01);
    ASSERT_NEAR(loadedObject[1]->Solve(-5).first, 0, 0.01);
    ASSERT_NEAR(loadedObject[1]->Solve(-5).second, 0, 0.01);
}

TEST_F(TestFactory, DoubleValues)
{
    FunctionPtr firstPtr(new EllipseFunction(3.456, 7.777));
    FunctionPtr secondPtr(new HyperbolaFunction(M_PI, 4.000001));

    FunctionPtr objects[] = { firstPtr, secondPtr };
    Save("DoubleFile.txt", objects, 2);

    vector<FunctionPtr> loadedObject = Load("DoubleFile.txt");

    ASSERT_NEAR(loadedObject[0]->Solve(0.93).first, 7.49, 0.01);
    ASSERT_NEAR(loadedObject[0]->Solve(0.93).second, -7.49, 0.01);
    ASSERT_NEAR(loadedObject[0]->Solve(-2.85).first, 4.399, 0.01);
    ASSERT_NEAR(loadedObject[0]->Solve(-2.85).second, -4.399, 0.01);

    ASSERT_NEAR(loadedObject[1]->Solve(7.67).first, 8.909, 0.01);
    ASSERT_NEAR(loadedObject[1]->Solve(7.67).second, -8.909, 0.01);
    ASSERT_NEAR(loadedObject[1]->Solve(-61.44).first, 78.126, 0.01);
    ASSERT_NEAR(loadedObject[1]->Solve(-61.44).second, -78.126, 0.01);
}

TEST_F(TestFactory, NotFromDefinitionRangeValues)
{
    FunctionPtr firstPtr(new EllipseFunction(4.5, 3.9));
    FunctionPtr secondPtr(new HyperbolaFunction(3.5, 6.3));

    FunctionPtr objects[] = { firstPtr, secondPtr };
    Save("NanFile.txt", objects, 2);

    vector<FunctionPtr> loadedObject = Load("NanFile.txt");


    ASSERT_TRUE(isnan(loadedObject[0]->Solve(4.50001).first));
    ASSERT_TRUE(isnan(loadedObject[0]->Solve(4.50001).second));
    ASSERT_TRUE(isnan(loadedObject[0]->Solve(123456789).first));
    ASSERT_TRUE(isnan(loadedObject[0]->Solve(123456789).second));

    ASSERT_TRUE(isnan(loadedObject[1]->Solve(0).first));
    ASSERT_TRUE(isnan(loadedObject[1]->Solve(0).second));
    ASSERT_TRUE(isnan(loadedObject[1]->Solve(3.4999).first));
    ASSERT_TRUE(isnan(loadedObject[1]->Solve(3.4999).second));
}