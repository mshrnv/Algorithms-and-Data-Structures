#ifndef OBST_OBST_H
#define OBST_OBST_H

#include <iostream>
#include <vector>
#include <exception>

#define NMAX 20

using namespace std;

class OBSTree {
public:

    struct Node {
        int _value;
        Node *_left;
        Node *_right;
    };

    OBSTree(int numberOfKeys, const int *keys, const int *frequencies, const int *unsuccessful) {
        _numberOfKeys = numberOfKeys;

        for (int i = 0; i < _numberOfKeys; ++i) {
            _keys[i + 1] = keys[i];
        }

        for (int i = 0; i < _numberOfKeys; ++i) {
            _p[i + 1] = frequencies[i];
        }

        for (int i = 0; i < _numberOfKeys + 1; ++i) {
            _q[i + 1] = unsuccessful[i];
        }

        ComputeWCR();
        _root = ConstructTree(0, _numberOfKeys);
    }

    ~OBSTree() {
        Destruct(_root);
        _root = nullptr;
    }

    bool IsEmpty()
    {
        return !_root;
    }

    Node* Find(const int value)
    {
        return FindNode(_root, value);
    }

    bool Contains(const int value)
    {
        return Find(value)->_value == value;
    }

    vector<int> RoundLRootR() const
    {
        vector<int> result;
        InOrder(_root, &result);
        return result;
    }

    vector<int> RoundRRootL() const
    {
        vector<int> result;
        InReverseOrder(_root, &result);
        return result;
    }

    void Print() {
        PrintBinaryTree("", _root, false);
    }

    Node *GetRoot() {

        return _root;
    }

private:

    void Destruct(Node* node)
    {
        if (node) {
            Destruct(node->_left);
            Destruct(node->_right);
            delete[] node;
        }
    }

    Node* FindNode(Node* node, int value)
    {
        if (node->_value == value)
            return node;

        Node* side = value < node->_value ? node->_left : node->_right;

        if (side)
            return FindNode(side, value);

        return node;
    }

    void InOrder(Node* node, vector<int>* values) const
    {
        if (node->_left != nullptr)
            InOrder(node->_left, values);

        values->push_back(node->_value);

        if (node->_right != nullptr)
            InOrder(node->_right, values);

    }

    void InReverseOrder(Node* node, vector<int>* values) const
    {
        if (node->_right)
            InReverseOrder(node->_right, values);

        values->push_back(node->_value);

        if (node->_left)
            InReverseOrder(node->_left, values);

    }

    void PrintBinaryTree(const string &prefix, const Node *node, bool isLeft) {
        if (node) {
            std::cout << prefix;
            std::cout << (isLeft ? "├──" : "└──");
            std::cout << node->_value << std::endl;

            PrintBinaryTree(prefix + (isLeft ? "│   " : "    "), node->_left, true);
            PrintBinaryTree(prefix + (isLeft ? "│   " : "    "), node->_right, false);
        }
    }

    Node *ConstructTree(int i, int j) {
        Node *p;

        if (i == j)
            p = nullptr;
        else {
            p = (Node *) calloc(1, sizeof(Node));
            p->_value = _keys[_roots[i][j]];
            p->_left = ConstructTree(i, _roots[i][j] - 1);
            p->_right = ConstructTree(_roots[i][j], j);
        }

        return p;
    }

    void ComputeWCR() {
        int x, min, i, j, k, h, m;

        for (i = 0; i <= _numberOfKeys; i++) {
            _weights[i][i] = _q[i];
            for (j = i + 1; j <= _numberOfKeys; j++)
                _weights[i][j] = _weights[i][j - 1] + _p[j] + _q[j];
        }

        for (i = 0; i <= _numberOfKeys; i++)
            _costs[i][i] = _weights[i][i];

        for (i = 0; i <= _numberOfKeys - 1; i++) {
            j = i + 1;
            _costs[i][j] = _costs[i][i] + _costs[j][j] + _weights[i][j];
            _roots[i][j] = j;
        }

        for (h = 2; h <= _numberOfKeys; h++) {
            for (i = 0; i <= _numberOfKeys - h; i++) {
                j = i + h;
                m = _roots[i][j - 1];
                min = _costs[i][m - 1] + _costs[m][j];
                for (k = m + 1; k <= _roots[i + 1][j]; k++) {
                    x = _costs[i][k - 1] + _costs[k][j];
                    if (x < min) {
                        m = k;
                        min = x;
                    }
                }
                _costs[i][j] = _weights[i][j] + min;
                _roots[i][j] = m;
            }
        }

    }

    Node *_root;

    int _numberOfKeys;
    int _keys[NMAX] = {};
    int _p[NMAX] = {};
    int _q[NMAX] = {};

    int _costs[NMAX][NMAX] = {};
    int _weights[NMAX][NMAX] = {};
    int _roots[NMAX][NMAX] = {};
};

#endif //OBST_OBST_H
