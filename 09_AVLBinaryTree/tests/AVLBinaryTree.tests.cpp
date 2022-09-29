#include <gtest/gtest.h>
#include <AVLBinaryTree/AVLBinaryTree.h>

using namespace std;

TEST(AVL_Binary_Tree, DefaultConstructor)
{
    AVLBinaryTree<int> emptyTree;
    ASSERT_TRUE(emptyTree.IsEmpty());
}

TEST(AVL_Binary_Tree, ParameterConstructor)
{
    AVLBinaryTree<int> oneElemTree(5);
    ASSERT_FALSE(oneElemTree.IsEmpty());
    ASSERT_EQ(oneElemTree.GetRoot()->_value, 5);
}

TEST(AVL_Binary_Tree, IsEmpty)
{
    AVLBinaryTree<int> emptyTree;
    ASSERT_TRUE(emptyTree.IsEmpty());

    AVLBinaryTree<int> tree(5);
    ASSERT_FALSE(tree.IsEmpty());
}

TEST(AVL_Binary_Tree, Contains)
{
    AVLBinaryTree<int> tree(5);
    vector<int> values{10, 20, 7, 3, 21, 22, 23};

    for (int item: values) {
        tree.Insert(item);
    }

    for (int item: values) {
        ASSERT_TRUE(tree.Contains(item));
    }

    tree.Print();
}

TEST(AVL_Binary_Tree, Insert)
{
    AVLBinaryTree<int> testTree(1);
    ASSERT_TRUE(testTree.Insert(2));
    ASSERT_TRUE(testTree.Insert(3));

    ASSERT_EQ(testTree.GetRoot()->_value, 2);
    ASSERT_EQ(testTree.GetRoot()->_left->_value, 1);
    ASSERT_EQ(testTree.GetRoot()->_right->_value, 3);
}

TEST(AVL_Binary_Tree, LRootR)
{
    AVLBinaryTree<int> tree;
    vector<int> values{3, 5, 7, 10, 20};

    for (int item: values) {
        tree.Insert(item);
    }

    tree.Print();

    vector<int> lrootr = tree.RoundLRootR();
    vector<int> order = vector<int>{3, 5, 7, 10, 20};

    ASSERT_EQ(order, lrootr);
}

TEST(AVL_Binary_Tree, RRootL)
{
    AVLBinaryTree<int> tree;
    vector<int> values{3, 5, 7, 10, 20};

    for (int item: values) {
        tree.Insert(item);
    }

    tree.Print();

    vector<int> rrootl = tree.RoundRRootL();
    vector<int> order = vector<int>{20, 10, 7, 5, 3};

    ASSERT_EQ(order, rrootl);
}

TEST(AVL_Binary_Tree, Balance)
{
    AVLBinaryTree<int> tree;
    vector<int> values{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    for (int item: values) {
        tree.Insert(item);
    }

    ASSERT_EQ(tree.GetRoot()->_height, 4);
    tree.Print();
}

TEST(AVL_Binary_Tree, Find)
{
    AVLBinaryTree<int> tree;
    vector<int> values{3, 5, 7, 10, 20};

    for (int item: values) {
        tree.Insert(item);
    }

    ASSERT_TRUE(tree.Find(5)->_value == 5);
    ASSERT_FALSE(tree.Find(6)->_value == 6);
}