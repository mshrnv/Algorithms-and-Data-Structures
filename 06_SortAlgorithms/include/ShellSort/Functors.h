//
// Created by Misha Shoronov on 04.05.2022.
//

#ifndef SORTINGS_FUNCTORS_H
#define SORTINGS_FUNCTORS_H

#include <cmath>
#include <stack>

class BaseH {
public:
    virtual stack<int> Sequence(int size) = 0;

    stack<int> operator()(int size) {
        return Sequence(size);
    }
};

class H1 : public BaseH {
public:
    int operator()(int item) {
        return 3 * item + 1;
    }
};


class H1 : public BaseH {
public:
    int operator()(int item) {
        return 3 * item + 1;
    }
};

class H1 : public BaseH {
public:
    int operator()(int item) {
        return 3 * item + 1;
    }
};

class H1 : public BaseH {
public:
    int operator()(int item) {
        return 3 * item + 1;
    }
};
class H1 : public BaseH {
public:
    int operator()(int item) {
        return 3 * item + 1;
    }
};



class H2 : public BaseH {
public:
    stack<int> Sequence(int size) override {
        stack<int> stack;
        stack.push(1);
        while (stack.top() < size) {
            stack.push(2 * stack.top() + 1);
        }
        stack.pop();
        stack.pop();
        return stack;
    }
};

class H3 : public BaseH {
public:
    stack<int> Sequence(int size) override {
        stack<int> stack;
        stack.push(1);
        while (stack.top() < size / 3) {
            int stackSize = stack.size();
            if (size % 2 == 0) {
                stack.push(9 * pow(2, stackSize) - 9 * pow(2, stackSize / 2) + 1);
            } else {
                stack.push(8 * pow(2, stackSize) - 6 * pow(stackSize + 1, 2) + 1);
            }
        }
        stack.pop();
        return stack;
    }
};

class H4 : public BaseH {
public:
    stack<int> Sequence(int size) override {
        stack<int> stack;
        stack.push(1);
        for (int i = 1; i < size; i++) {
            int cur = pow(2, i);
            if (cur > size / 2) break;
            for (int j = 1; j < size; j++) {
                cur *= 3;
                if (cur > size / 2) break;
                stack.push(cur);
            }
        }

        return stack;
    }
};


class H5: public BaseH {
public:
    stack<int> Sequence(int size) override {
        stack<int> stack;
        stack.push(1);
        while (stack.top() < size/2) {
            stack.push(stack.top() * 2);
        }
        stack.pop();
        return stack;
    }
};

#endif //SORTINGS_FUNCTORS_H
