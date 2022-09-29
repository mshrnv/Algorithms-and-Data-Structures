#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H

#include "TreeNode.h"
using namespace std;

template <typename T>
class BinaryTree
{
public:
    BinaryTree()
    {
        _root = nullptr;
    }

    BinaryTree(T value)
    {
        _root = new TreeNode<T>(value);
    }

    ~BinaryTree()
    {
        while (_root) {
            Remove(_root->_value);
        }
    }

    BinaryTree(const BinaryTree& other)
    {
        if (_root)
            CopyTree(_root);
    }

    BinaryTree(BinaryTree&& other)
    {
        _root = nullptr;
        _root = other._root;
        other._root = nullptr;
    }

    const BinaryTree& operator=(const BinaryTree& other) = delete;
    BinaryTree& operator=(BinaryTree&& other) = delete;

    bool IsEmpty() const
    {
        return !_root;
    }

    bool Insert(const T& value)
    {
        if (IsEmpty()) {
            _root = new TreeNode<T>(value);
            return true;
        }

        auto find = Find(*_root, value);

        if (find->_value == value)
            return false;

        if (value < find->_value)
            find->_left = new TreeNode<T>(value, *find);
        else
            find->_right = new TreeNode<T>(value, *find);

        return true;
    }

    bool Remove(const T& value)
    {
        TreeNode<T>* find = Find(*_root, value);
        auto parent = find->_parent;

        if (!find || find->_value != value)
            return false;

        if (find->_right && find->_left) {
            T minRightValue = GetMinimum(find->_right);
            Remove(minRightValue);
            find->_value = minRightValue;
        }

        else if (!find->_left && find->_right)
            find->InitializeFrom(*find->_right);

        else if (find->_left && !find->_right)
            find->InitializeFrom(*find->_left);

        else {
            if (find == _root) {
                _root = nullptr;
                return true;
            }
            parent->DeleteChild(value < parent->_value);
        }

        return true;
    }

    bool Contains(const T& value)
    {
        return Find(*_root, value)->_value == value;
    }

    vector<T> RoundLRootR() const {
        vector<T> result;
        InOrder(_root, &result);
        return result;
    }

    vector<T> RoundRRootL() const {
        vector<T> result;
        InReverseOrder(_root, &result);
        return result;
    }

    void Print()
    {
        PrintBinaryTree("", _root, false);
    }

    TreeNode<T>* GetRoot() const
    {
        return _root;
    }

protected:
    TreeNode<T>* Find(TreeNode<T>& root, T value)
    {
        if (root._value == value)
            return &root;

        auto side = value < root._value ? root._left : root._right;

        if (side)
            return Find(*side, value);

        return &root;
    }

    void PrintBinaryTree(const string& prefix, const TreeNode<T>* node, bool isLeft) {
        if (node != nullptr) {
            std::cout << prefix;
            std::cout << (isLeft ? "├──" : "└──");
            std::cout << node->_value << std::endl;

            PrintBinaryTree(prefix + (isLeft ? "│   " : "    "), node->_left, true);
            PrintBinaryTree(prefix + (isLeft ? "│   " : "    "), node->_right, false);
        }
    }

    void InOrder(TreeNode<T>* node, vector<T>* values) const {
        if (node->_left != nullptr)
            InOrder(node->_left, values);

        values->push_back(node->_value);

        if (node->_right != nullptr)
            InOrder(node->_right, values);

    }

    void InReverseOrder(TreeNode<T>* node, vector<T>* values) const {
        if (node->_right)
            InReverseOrder(node->_right, values);

        values->push_back(node->_value);

        if (node->_left)
            InReverseOrder(node->_left, values);

    }

    void CopyTree(TreeNode<T>* node)
    {
        Insert(node->value);

        if (node->_left)
            CopyTree(node->_left);

        if (node->_right)
            CopyTree(node->_right);
    }

    T GetMinimum(TreeNode<T>* node) {
        while (node->_left != nullptr) {
            node = node->_left;
        }
        return node->_value;
    }

private:
    TreeNode<T>* _root;
};

#endif //BINARYTREE_BINARYTREE_H
