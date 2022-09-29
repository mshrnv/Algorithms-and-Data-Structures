#include <gtest/gtest.h>
#include "BinaryTree/BinaryTree.h"


class BinaryTreeTest : public ::testing::Test
{
protected:
    BinaryTree<int>* tree;
    virtual void SetUp()
    {
        tree = new BinaryTree<int>(10);
        tree->Insert(5);
        tree->Insert(20);
        tree->Insert(3);
        tree->Insert(7);
    }

    virtual void TearDown()
    {
        delete tree;
    }
};

TEST_F(BinaryTreeTest, DefaultConstructor)
{
    BinaryTree<int> emptyTree;
    ASSERT_TRUE(emptyTree.IsEmpty());
}

TEST_F(BinaryTreeTest, ParameterConstructor)
{
    BinaryTree<int> oneElemTree(5);
    ASSERT_FALSE(oneElemTree.IsEmpty());
    ASSERT_EQ(oneElemTree.GetRoot()->_value, 5);
}

TEST_F(BinaryTreeTest, CopyConstructor)
{
    auto copy = tree;
    ASSERT_FALSE(copy->IsEmpty());
    ASSERT_EQ(copy->GetRoot()->_value, 10);
}

TEST_F(BinaryTreeTest, IsEmpty)
{
    BinaryTree<int> emptyTree;
    ASSERT_TRUE(emptyTree.IsEmpty());
    ASSERT_FALSE(tree->IsEmpty());
}

TEST_F(BinaryTreeTest, Contains)
{
    ASSERT_TRUE(tree->Contains(10));
    ASSERT_TRUE(tree->Contains(20));
    ASSERT_TRUE(tree->Contains(5));
    ASSERT_TRUE(tree->Contains(7));
    ASSERT_TRUE(tree->Contains(3));
    ASSERT_FALSE(tree->Contains(2));
    ASSERT_FALSE(tree->Contains(4));
}

TEST_F(BinaryTreeTest, Insert)
{
    BinaryTree<int> testTree(5);
    ASSERT_TRUE(testTree.Insert(1));
    ASSERT_TRUE(testTree.Insert(11));
    ASSERT_EQ(testTree.GetRoot()->_value, 5);
    ASSERT_EQ(testTree.GetRoot()->_left->_value, 1);
    ASSERT_EQ(testTree.GetRoot()->_right->_value, 11);

    ASSERT_FALSE(testTree.Insert(11));
}

TEST_F(BinaryTreeTest, Remove)
{
    ASSERT_FALSE(tree->Remove(2));
    ASSERT_TRUE(tree->Remove(5));
    ASSERT_TRUE(tree->Remove(20));
    ASSERT_TRUE(tree->Remove(10));
}

TEST_F(BinaryTreeTest, LRootR)
{
    vector<int> values = tree->RoundLRootR();
    vector<int> lrootr = vector<int>{3, 5, 7, 10, 20};
    ASSERT_EQ(values, lrootr);
}

TEST_F(BinaryTreeTest, RRootL)
{
    vector<int> values = tree->RoundRRootL();
    vector<int> rrootl = vector<int>{20, 10, 7, 5, 3};
    ASSERT_EQ(values, rrootl);
}

TEST_F(BinaryTreeTest, Print)
{
    tree->Print();
}