#include <gtest/gtest.h>
#include <OBST/OBST.h>
#include <iostream>

using namespace std;

TEST(OBST, Constructor) {
    int k[] = {1, 2, 3, 4, 5};
    int p[] = {1, 2, 10, 5, 3};
    int q[] = {0, 0, 0, 0, 0, 0};

    OBSTree tree(5, k, p, q);
    tree.Print();
    ASSERT_EQ(tree.GetRoot()->_value, 3);
    ASSERT_EQ(tree.GetRoot()->_left->_value, 2);
    ASSERT_EQ(tree.GetRoot()->_right->_value, 4);
}

TEST(OBST, Destructor) {
    int k[] = {1, 2, 3, 4, 5};
    int p[] = {1, 2, 10, 5, 3};
    int q[] = {0, 0, 0, 0, 0, 0};

    OBSTree* tree = new OBSTree(5, k, p, q);
    delete tree;
}

TEST(OBST, Contains) {
    int k[] = {1, 2, 3, 4, 5};
    int p[] = {1, 2, 10, 5, 3};
    int q[] = {0, 0, 0, 0, 0, 0};

    OBSTree tree(5, k, p, q);
    ASSERT_TRUE(tree.Contains(1));
    ASSERT_TRUE(tree.Contains(2));
    ASSERT_TRUE(tree.Contains(3));
    ASSERT_TRUE(tree.Contains(4));
    ASSERT_TRUE(tree.Contains(5));
}

TEST(OBST, IsEmptyFalse) {
    int k[] = {1, 2, 3, 4, 5};
    int p[] = {1, 2, 10, 5, 3};
    int q[] = {0, 0, 0, 0, 0, 0};

    OBSTree tree(5, k, p, q);
    ASSERT_FALSE(tree.IsEmpty());
}

TEST(OBST, IsEmptyTrue) {
    int k[] = {};
    int p[] = {};
    int q[] = {0};

    OBSTree tree(0, k, p, q);
    ASSERT_TRUE(tree.IsEmpty());
}

TEST(OBST, LRootR) {
    int k[] = {2, 4, 6, 8, 10};
    int p[] = {13, 5, 3, 25, 10};
    int q[] = {7, 10, 5, 0, 5, 10};

    OBSTree tree(5, k, p, q);
    vector<int> values = {2, 4, 6, 8, 10};
    ASSERT_EQ(tree.RoundLRootR(), values);
}

TEST(OBST, RRootL) {
    int k[] = {2, 4, 6, 8, 10};
    int p[] = {13, 5, 3, 25, 10};
    int q[] = {7, 10, 5, 0, 5, 10};

    OBSTree tree(5, k, p, q);
    vector<int> values = {10, 8, 6, 4, 2};
    ASSERT_EQ(tree.RoundRRootL(), values);
}

TEST(OBST, BigData) {
    int k[] = {13, 2, 19, 25, 100, 1,
               35, 10, 101, 15, 55, 54,
               56, 70, 9, 19, 16, 111};

    int p[] = {13, 5, 3, 25, 10, 222,
               100, 10, 9, 14, 30,
               40, 55, 17, 18, 1, 5, 21};

    int q[] = {7, 10, 5, 0, 5, 10,
               0, 0, 11, 25, 19,
               30, 0, 4, 0, 2, 2, 2, 0};

    OBSTree tree(17, k, p, q);

    tree.Print();

    set<int> topValues = {
            tree.GetRoot()->_value,
            tree.GetRoot()->_left->_value,
            tree.GetRoot()->_right->_value
    };

    ASSERT_TRUE(topValues.count(1));
    ASSERT_TRUE(topValues.count(35));
    ASSERT_TRUE(topValues.count(54));
}