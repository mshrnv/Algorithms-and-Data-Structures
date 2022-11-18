#include <gtest/gtest.h>
#include <iostream>
#include "Cone/Cone.h"

TEST(ConeTests, DefaultConstructor) {
    Cone cone;
    ASSERT_EQ(cone.GetHeight(), 0);
    ASSERT_EQ(cone.GetRadius(), 0);
}

TEST(ConeTests, ConstructorWithParameters) {
    Cone cone(5, 10);
    ASSERT_EQ(cone.GetHeight(), 5);
    ASSERT_EQ(cone.GetRadius(), 10);
}

TEST(ConeTests, CopyConstructor) {
    Cone cone1(3.5, 6.3);
    Cone cone2(cone1);

    ASSERT_EQ(cone1.GetHeight(), cone2.GetHeight());
    ASSERT_EQ(cone1.GetRadius(), cone2.GetRadius());
}

TEST(ConeTests, MoveConstructor) {
    Cone cone1(3.5, 6.3);
    Cone cone2 = std::move(cone1);

    ASSERT_EQ(cone1.GetHeight(), 0);
    ASSERT_EQ(cone1.GetRadius(), 0);
    ASSERT_EQ(cone2.GetHeight(), 3.5);
    ASSERT_EQ(cone2.GetRadius(), 6.3);
}

TEST(ConeTests, CopyAssignmentOperator) {
    Cone cone1(3.5, 6.3);
    Cone cone2;

    cone2 = cone1;

    ASSERT_EQ(cone1.GetHeight(), 3.5);
    ASSERT_EQ(cone1.GetRadius(), 6.3);
    ASSERT_EQ(cone2.GetHeight(), 3.5);
    ASSERT_EQ(cone2.GetRadius(), 6.3);
}

TEST(ConeTests, MoveAssignmentOperator) {
    Cone cone1(3.5, 6.3);
    Cone cone2;

    cone2 = std::move(cone1);

    ASSERT_EQ(cone1.GetHeight(), 0);
    ASSERT_EQ(cone1.GetRadius(), 0);
    ASSERT_EQ(cone2.GetHeight(), 3.5);
    ASSERT_EQ(cone2.GetRadius(), 6.3);
}

TEST(ConeTests, SetAndGetMathods) {
    Cone cone;

    cone.SetHeight(1.111);
    cone.SetRadius(9.001);

    ASSERT_EQ(cone.GetHeight(), 1.111);
    ASSERT_EQ(cone.GetRadius(), 9.001);
}

TEST(ConeTests, CalculateSquare) {
    Cone cone(5.45, 7.62);

    ASSERT_NEAR(cone.CalculateSquare(), 406.737, 0.1);
}