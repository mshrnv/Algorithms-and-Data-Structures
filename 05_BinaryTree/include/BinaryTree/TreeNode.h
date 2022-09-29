#ifndef BINARYTREE_TREENODE_H
#define BINARYTREE_TREENODE_H

template <typename T>
class TreeNode
{
public:
    TreeNode(T value) : _value(value), _left(nullptr), _right(nullptr), _parent(nullptr) {}
    TreeNode(T value, TreeNode& parent) : _value(value), _left(nullptr), _right(nullptr), _parent(&parent) {}

    void InitializeFrom(TreeNode& other)
    {
        _value = other._value;
        _left = other._left;
        _right = other._right;
        _parent = other._parent;

        if (_left)
            _left->_parent = this;

        if (_right)
            _right->_parent = this;
    }

    void DeleteChild(bool isLeft)
    {
        if (isLeft)
            _left = nullptr;
        else
            _right = nullptr;
    }

    ~TreeNode()
    {
        _value = 0;
        _left = nullptr;
        _right = nullptr;
        _parent = nullptr;
    }

    T _value;
    TreeNode* _left;
    TreeNode* _right;
    TreeNode* _parent;
};

#endif //BINARYTREE_TREENODE_H
