#ifndef BINARYTREE_AVLBINARYTREE_H
#define BINARYTREE_AVLBINARYTREE_H

#include <iostream>
#include <string>

using namespace std;

template<typename T>
class AVLBinaryTree {
public:

    struct TreeNode
    {
        TreeNode(T value)
        {
            _value = value;
        }

        T _value;
        unsigned int _height = 0;
        TreeNode* _left = nullptr;
        TreeNode* _right = nullptr;
    };

    AVLBinaryTree()
    {
        _root = nullptr;
    }

    AVLBinaryTree(T value)
    {
        _root = new TreeNode(value);
    }

    ~AVLBinaryTree()
    {
        Destruct(_root);
        _root = nullptr;
    }

    AVLBinaryTree(const AVLBinaryTree& other)
    {
        CopyTree(_root);
    }

    AVLBinaryTree(AVLBinaryTree&& other)
    {
        _root = nullptr;
        _root = other._root;
        other._root = nullptr;
    }

    const AVLBinaryTree& operator=(const AVLBinaryTree& other) = delete;
    AVLBinaryTree& operator=(AVLBinaryTree&& other) = delete;

    bool IsEmpty()
    {
        return !_root;
    }

    TreeNode* Find(const T& value)
    {
        return FindNode(_root, value);
    }

    TreeNode* Balance(TreeNode* node)
    {
        UpdateHeight(node);
        auto balanceFactor = GetBalanceFactor(node);

        if (balanceFactor == 2) {
            if (GetBalanceFactor(node->_right) == -1)
                node->_right = RotateRight(node->_right);

            return RotateLeft(node);
        }

        if (balanceFactor == -2) {
            if (GetBalanceFactor(node->_left) == 1)
                node->_left = RotateLeft(node->_left);

            return RotateRight(node);
        }

        return node;
    }

    bool Insert(const T& value)
    {
        if (IsEmpty()) {
            _root = new TreeNode(value);
            return true;
        }

        return InsertNode(_root, value);
    }

    bool Contains(const T& value)
    {
        return Find(value)->_value == value;
    }

    vector<T> RoundLRootR() const
    {
        vector<T> result;
        InOrder(_root, &result);
        return result;
    }

    vector<T> RoundRRootL() const
    {
        vector<T> result;
        InReverseOrder(_root, &result);
        return result;
    }

    void Print()
    {
        PrintBinaryTree("", _root, false);
    }

    TreeNode* GetRoot()
    {
        return _root;
    }

protected:


    void CopyTree(TreeNode* node)
    {
        if (node) {
            Insert(node);
            CopyTree(node->_left);
            CopyTree(node->_right);
        }
    }

    TreeNode* FindNode(TreeNode* node, const T& value)
    {
        if (node->_value == value)
            return node;

        TreeNode* side = value < node->_value ? node->_left : node->_right;

        if (side)
            return FindNode(side, value);

        return node;
    }


    TreeNode* RotateRight(TreeNode* node)
    {
        TreeNode* child = node->_left;

        node->_left = child->_right;
        child->_right = node;

        UpdateHeight(node);
        UpdateHeight(child);

        if (node == _root)
            _root = child;

        return child;
    }

    TreeNode* RotateLeft(TreeNode* node)
    {
        TreeNode* child = node->_right;

        node->_right = child->_left;
        child->_left = node;

        UpdateHeight(node);
        UpdateHeight(child);

        if (node == _root)
            _root = child;

        return child;
    }

    TreeNode* InsertNode(TreeNode* node, const T& value)
    {
        if (!node)
            return new TreeNode(value);

//        TODO: Doesn't work
//        TreeNode* side = value < node->_value ? node->_left : node->_right;
//        side = InsertNode(side, value);

        if (value < node->_value)
            node->_left = InsertNode(node->_left, value);
        else
            node->_right = InsertNode(node->_right, value);

        return Balance(node);
    }

    void PrintBinaryTree(const string& prefix, const TreeNode* node, bool isLeft)
    {
        if (node != nullptr) {
            cout << prefix;
            cout << (isLeft ? "├──" : "└──");
            cout << node->_value << endl;

            PrintBinaryTree(prefix + (isLeft ? "│   " : "    "), node->_left, true);
            PrintBinaryTree(prefix + (isLeft ? "│   " : "    "), node->_right, false);
        }
    }

    void InOrder(TreeNode* node, vector<T>* values) const
    {
        if (node->_left != nullptr)
            InOrder(node->_left, values);

        values->push_back(node->_value);

        if (node->_right != nullptr)
            InOrder(node->_right, values);

    }

    void InReverseOrder(TreeNode* node, vector<T>* values) const
    {
        if (node->_right)
            InReverseOrder(node->_right, values);

        values->push_back(node->_value);

        if (node->_left)
            InReverseOrder(node->_left, values);

    }

    unsigned int GetHeight(TreeNode* node)
    {
        return (node) ? node->_height : 0;
    }

    int GetBalanceFactor(TreeNode* node)
    {
        return GetHeight(node->_right) - GetHeight(node->_left) + 1;
    }

    void UpdateHeight(TreeNode* node)
    {
        node->_height = 1 + max(GetHeight(node->_left), GetHeight(node->_right));
    }

private:
    TreeNode* _root;
};

#endif //BINARYTREE_AVLBINARYTREE_H
