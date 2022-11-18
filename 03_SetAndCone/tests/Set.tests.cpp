#include <gtest/gtest.h>
#include <iostream>
#include <Set/Set.h>
#include <Cone/Cone.h>
#include <Functors/IntFunctor.h>
#include <Functors/ConeFunctor.h>

using namespace std;

class SetTest : public ::testing::Test {
protected:
    Set<int> *intSet1;
    Set<int> *intSet2;
    Set<Cone *> *coneSet1;
    Set<Cone *> *coneSet2;

    Cone *cone1 = new Cone(5, 12);
    Cone *cone2 = new Cone();
    Cone *cone3 = new Cone(4.4, 5.5);
    Cone *cone4 = new Cone(1, 100);

    virtual void SetUp() {
        intSet1 = new Set<int>(5);
        intSet2 = new Set<int>(4);
        coneSet1 = new Set<Cone *>(3);
        coneSet2 = new Set<Cone *>(2);

        intSet1->Push(5);
        intSet1->Push(100);
        intSet1->Push(-11);
        intSet1->Push(19);

        intSet2->Push(100);
        intSet2->Push(19);
        intSet2->Push(3);

        coneSet1->Push(cone1);
        coneSet1->Push(cone2);
        coneSet1->Push(cone3);

        coneSet2->Push(cone3);
        coneSet2->Push(cone4);
    }

    virtual void TearDown() {
        delete intSet1;
        delete intSet2;
        delete coneSet1;
        delete coneSet2;
    }
};


TEST_F(SetTest, DefaultConstructor) {
    Set<int> set1;
    Set<Cone *> set2;

    ASSERT_EQ(set1.GetCapacity(), 0);
    ASSERT_EQ(set1.GetSize(), 0);
    ASSERT_EQ(set2.GetCapacity(), 0);
    ASSERT_EQ(set2.GetSize(), 0);
}

TEST_F(SetTest, ConstructorWithParameters) {
    Set<int> *set1 = new Set<int>(4);
    Set<Cone *> *set2 = new Set<Cone *>(2);

    ASSERT_EQ(set1->GetCapacity(), 4);
    ASSERT_EQ(set1->GetSize(), 0);
    ASSERT_EQ(set2->GetCapacity(), 2);
    ASSERT_EQ(set2->GetSize(), 0);
}

TEST_F(SetTest, Push) {
    ASSERT_EQ(intSet1->GetCapacity(), 5);
    ASSERT_EQ(intSet1->GetSize(), 4);
    ASSERT_EQ(coneSet1->GetCapacity(), 3);
    ASSERT_EQ(coneSet1->GetSize(), 3);
}

TEST_F(SetTest, Contains) {
    ASSERT_TRUE(intSet1->Contains(5));
    ASSERT_TRUE(intSet1->Contains(100));
    ASSERT_TRUE(intSet1->Contains(-11));
    ASSERT_FALSE(intSet1->Contains(11));
    ASSERT_TRUE(coneSet1->Contains(cone1));
    ASSERT_TRUE(coneSet1->Contains(cone2));
    ASSERT_FALSE(coneSet1->Contains(new Cone(5, 12)));
}

TEST_F(SetTest, Erase) {
    intSet1->Erase(5);
    ASSERT_EQ(intSet1->GetSize(), 3);
    ASSERT_FALSE(intSet1->Contains(5));
    ASSERT_TRUE(intSet1->Contains(100));
    ASSERT_TRUE(intSet1->Contains(-11));
    ASSERT_TRUE(intSet1->Contains(19));

    coneSet1->Erase(cone2);
    ASSERT_EQ(coneSet1->GetSize(), 2);
    ASSERT_TRUE(coneSet1->Contains(cone1));
    ASSERT_TRUE(coneSet1->Contains(cone3));
    ASSERT_FALSE(coneSet1->Contains(cone2));
}

TEST_F(SetTest, EraseNotExist) {
    intSet1->Erase(55);
    ASSERT_EQ(intSet1->GetSize(), 4);
    ASSERT_TRUE(intSet1->Contains(5));
    ASSERT_TRUE(intSet1->Contains(100));
    ASSERT_TRUE(intSet1->Contains(-11));
    ASSERT_TRUE(intSet1->Contains(19));

    coneSet1->Erase(cone4);
    ASSERT_EQ(coneSet1->GetSize(), 3);
    ASSERT_TRUE(coneSet1->Contains(cone1));
    ASSERT_TRUE(coneSet1->Contains(cone2));
    ASSERT_TRUE(coneSet1->Contains(cone3));
}

TEST_F(SetTest, UnionOperator) {
    Set<int> unionSet = *intSet1 + *intSet2;
    ASSERT_EQ(unionSet.GetSize(), 5);
    ASSERT_TRUE(unionSet.Contains(5));
    ASSERT_TRUE(unionSet.Contains(100));
    ASSERT_TRUE(unionSet.Contains(-11));
    ASSERT_TRUE(unionSet.Contains(19));
    ASSERT_TRUE(unionSet.Contains(3));

    Set<Cone *> unionConeSet = *coneSet1 + *coneSet2;
    ASSERT_EQ(unionConeSet.GetSize(), 4);
    ASSERT_TRUE(unionConeSet.Contains(cone1));
    ASSERT_TRUE(unionConeSet.Contains(cone2));
    ASSERT_TRUE(unionConeSet.Contains(cone3));

    cout << unionSet;
    ASSERT_TRUE(unionConeSet.Contains(cone4));
}

TEST_F(SetTest, IntersectionOperator) {
    Set<int> intersectionSet = *intSet1 * *intSet2;
    ASSERT_EQ(intersectionSet.GetSize(), 2);
    ASSERT_TRUE(intersectionSet.Contains(19));
    ASSERT_TRUE(intersectionSet.Contains(100));

    Set<Cone *> intersectionConeSet = *coneSet1 * *coneSet2;
    ASSERT_EQ(intersectionConeSet.GetSize(), 1);
    ASSERT_TRUE(intersectionConeSet.Contains(cone3));
}

TEST_F(SetTest, DifferenceOperator) {
    Set<int> diffSet = *intSet1 - *intSet2;
    ASSERT_EQ(diffSet.GetSize(), 2);
    ASSERT_TRUE(diffSet.Contains(5));
    ASSERT_TRUE(diffSet.Contains(-11));

    Set<Cone *> diffConeSet = *coneSet1 - *coneSet2;
    ASSERT_EQ(diffConeSet.GetSize(), 2);
    ASSERT_TRUE(diffConeSet.Contains(cone1));
    ASSERT_TRUE(diffConeSet.Contains(cone2));
}

TEST_F(SetTest, Search) {
    int intRes = intSet1->Search(IntFunctor(), -11);
    ASSERT_EQ(intRes, -11);

    Cone *coneRes = coneSet1->Search(ConeFunctor(), new Cone(4.4, 5.5));
    ASSERT_EQ(coneRes, cone3);
}