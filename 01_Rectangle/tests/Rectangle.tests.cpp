#include <gtest/gtest.h>
#include <Rectangle/Rectangle.h>
#include <iostream>


class RectangleTest : public ::testing::Test {
protected:
    void SetUp() {}
    void TearDown() {}

    Rectangle rectangle;
    Rectangle rect1 = Rectangle(0, 4, 2, 3);
    Rectangle rect2 = Rectangle(4, 3, 6, 2);
};


TEST_F(RectangleTest, DefaultConstructor) {
    ASSERT_EQ(rectangle.GetHeight(), 0);
    ASSERT_EQ(rectangle.GetWidth(), 0);
    ASSERT_EQ(rectangle.GetPoint().x, 0);
    ASSERT_EQ(rectangle.GetPoint().y, 0);
    ASSERT_STREQ(rectangle.GetName(), "Rectangle_1");
}


TEST_F(RectangleTest, ConstructorWithParameters) {
    ASSERT_EQ(rect1.GetHeight(), 2);
    ASSERT_EQ(rect1.GetWidth(), 3);
    ASSERT_EQ(rect1.GetPoint().x, 0);
    ASSERT_EQ(rect1.GetPoint().y, 4);
    ASSERT_STREQ(rect1.GetName(), "Rectangle_2");
}

TEST_F(RectangleTest, CopyConstructor) {
    Rectangle rect3(rect1);
    ASSERT_TRUE(rect3 == rect1);
}

TEST_F(RectangleTest, MoveConstructor) {
    // Copy rect1 to temp
    Rectangle temp(rect1);
    // And move rect1 to test
    Rectangle test(std::move(rect1));

    // test should be equal temp
    ASSERT_TRUE(test == temp);
    // and rect1 should be equal empty rectangle
    ASSERT_TRUE(rect1 == rectangle);
}

TEST_F(RectangleTest, SetAndGetMethods) {
    rectangle.SetHeight(3);
    rectangle.SetWidth(5);
    rectangle.SetPoint(Point(-1, 1));
    rectangle.SetName("My Rectangle");

    ASSERT_EQ(rectangle.GetHeight(), 3);
    ASSERT_EQ(rectangle.GetWidth(), 5);
    ASSERT_EQ(rectangle.GetPoint().x, -1);
    ASSERT_EQ(rectangle.GetPoint().y, 1);
    ASSERT_STREQ(rectangle.GetName(), "My Rectangle");
}

TEST_F(RectangleTest, ComparisonOperatorEqual) {
    ASSERT_FALSE(rect1 == rect2);
    rect2 = rect1;
    ASSERT_TRUE(rect1 == rect2);
}

TEST_F(RectangleTest, ComparisonOperatorNonEqual) {
    ASSERT_TRUE(rect1 != rect2);
    rect1 = rect2;
    ASSERT_FALSE(rect1 != rect2);
}

TEST_F(RectangleTest, AssignmentOperator) {
    Rectangle rectangle2;
    ASSERT_TRUE(rectangle == rectangle2);
}

TEST_F(RectangleTest, AdditionOperatorPositive) {
    Rectangle result = rect1 + 5;
    ASSERT_EQ(result.GetHeight(), 7);
    ASSERT_EQ(result.GetWidth(), 8);
    ASSERT_EQ(result.GetPoint().x, 0);
    ASSERT_EQ(result.GetPoint().y, 4);

    Rectangle result2 = 14 + rect2;
    ASSERT_EQ(result2.GetHeight(), 20);
    ASSERT_EQ(result2.GetWidth(), 16);
    ASSERT_EQ(result2.GetPoint().x, 4);
    ASSERT_EQ(result2.GetPoint().y, 3);
}

TEST_F(RectangleTest, AdditionOperatorNegative) {
    Rectangle result = rect2 + (-2);
    ASSERT_EQ(result.GetHeight(), 4);
    ASSERT_EQ(result.GetWidth(), 0);
    ASSERT_EQ(result.GetPoint().x, 4);
    ASSERT_EQ(result.GetPoint().y, 3);
}

TEST_F(RectangleTest, SmallestRectangleContainingTwoOther) {
    Rectangle result = Rectangle::GetSmallestRectangleContaining(rect1, rect2);
    Rectangle answer = Rectangle(0, 4, 7, 6);
    ASSERT_TRUE(result == answer);
}

TEST_F(RectangleTest, NoIntersection) {
    Rectangle result = Rectangle::GetIntersection(rect1, rect2);
    ASSERT_TRUE(result == rectangle);
}

TEST_F(RectangleTest, Intersection) {
    rect1 = rect1 + 2;
    Rectangle result = Rectangle::GetIntersection(rect1, rect2);
    Rectangle answer = Rectangle(4, 3, 3, 1);
    ASSERT_TRUE(result == answer);
}

TEST_F(RectangleTest, Area) {
    ASSERT_EQ(rect1.getArea(), 6);
    ASSERT_EQ(rect2.getArea(), 12);
}

TEST_F(RectangleTest, Perimeter) {
    ASSERT_EQ(rect1.getPerimeter(), 10);
    ASSERT_EQ(rect2.getPerimeter(), 16);
}

TEST_F(RectangleTest, InvalidSetWidth) {
    ASSERT_THROW(rectangle.SetWidth(-3), std::exception) ;
}

TEST_F(RectangleTest, InvalidSetHeigth) {
    ASSERT_THROW(rectangle.SetHeight(-999), std::exception) ;
}

TEST_F(RectangleTest, InvalidConstructor) {
    ASSERT_THROW(Rectangle(-10, 10, -5, 5), std::exception) ;
}