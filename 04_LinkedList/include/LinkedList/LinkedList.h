#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

#include <iterator>
#include <iostream>

using namespace std;

template <typename T>
const class LinkedList
{
private:
    struct ListNode
    {
        ListNode()
        {
            _value = T();
            _next = _prev = this;
        }

        ListNode(ListNode* prev, ListNode* next, T value): _next(next), _prev(prev), _value(value) {}

        T _value;
        ListNode* _prev;
        ListNode* _next;
    };

public:

    class Iterator: public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        friend class LinkedList;

        Iterator(ListNode* node): _item(node) {}

        Iterator operator++(int) {
            _item = _item->_next;
            return Iterator(_item->_prev);
        }

        Iterator& operator++() {
            _item = _item->_next;
            return *this;
        }

        Iterator operator--(int) {
            _item = _item->_prev;
            return Iterator(_item->_next);
        }

        Iterator& operator--() {
            _item = _item->_prev;
            return *this;
        }

        bool operator==(const Iterator& other) {
            return _item == other._item;
        }

        bool operator!=(const Iterator& other) {
            return _item != other._item;
        }

        T& operator*() {
            return _item->_value;
        }

        T* operator->() {
            return &(_item->_value);
        }

        ListNode* _item;
    };

    class ConstIterator: public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        friend class LinkedList;

        ConstIterator(ListNode* node): _item(node) {}

        ConstIterator operator++(int) {
            _item = _item->_next;
            return Iterator(_item->_prev);
        }

        ConstIterator& operator++() {
            _item = _item->_next;
            return *this;
        }

        ConstIterator operator--(int) {
            _item = _item->_prev;
            return Iterator(_item->_next);
        }

        ConstIterator& operator--() {
            _item = _item->_prev;
            return *this;
        }

        bool operator==(const ConstIterator& other) const {
            return _item == other._item;
        }

        bool operator!=(const ConstIterator& other) const {
            return _item != other._item;
        }

        T& operator*() const {
            return _item->_value;
        }

        T* operator->() const {
            return &(_item->_value);
        }

        ListNode* _item;
    };

    class ReverseIterator: public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        friend class LinkedList;

        ReverseIterator(ListNode* node): _item(node) {}

        ReverseIterator operator++(int) {
            _item = _item->_prev;
            return Iterator(_item->_next);
        }

        ReverseIterator& operator++() {
            _item = _item->_prev;
            return *this;
        }

        ReverseIterator operator--(int) {
            _item = _item->_next;
            return Iterator(_item->_prev);
        }

        ReverseIterator& operator--() {
            _item = _item->_next;
            return *this;
        }

        bool operator==(const ReverseIterator& other) {
            return _item == other._item;
        }

        bool operator!=(const ReverseIterator& other) {
            return _item != other._item;
        }

        T& operator*() {
            return _item->_value;
        }

        T* operator->() {
            return &(_item->_value);
        }

        ListNode* _item;
    };

    class ConstReverseIterator: public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        friend class LinkedList;

        ConstReverseIterator(ListNode* node): _item(node) {}

        ConstReverseIterator operator++(int) {
            _item = _item->_prev;
            return Iterator(_item->_next);
        }

        ConstReverseIterator& operator++() {
            _item = _item->_prev;
            return *this;
        }

        ConstReverseIterator operator--(int) {
            _item = _item->_next;
            return Iterator(_item->_prev);
        }

        ConstReverseIterator& operator--() {
            _item = _item->_next;
            return *this;
        }

        bool operator==(const ConstReverseIterator& other) const {
            return _item == other._item;
        }

        bool operator!=(const ConstReverseIterator& other) const {
            return _item != other._item;
        }

        T& operator*() const {
            return _item->_value;
        }

        T* operator->() const {
            return &(_item->_value);
        }

        ListNode* _item;
    };

    LinkedList()
    {
        _head = new ListNode(nullptr, nullptr, T());
        _head->_next = _head->_prev = _head;
        _nodeCounter = 0;
    }

    ~LinkedList()
    {
        while (begin() != end()) {
            Erase(begin());
        }
    }

    void InitializeFrom(const LinkedList& other)
    {
        _head = new ListNode(nullptr, nullptr, T());
        _head->_next = _head->_prev = _head;

        for (T item: other) {
            PushBack(item);
        }
    }

    LinkedList(const LinkedList& other)
    {
        InitializeFrom(other);
        _nodeCounter = other._nodeCounter;
    }

    LinkedList(LinkedList&& other)
    {
        _head = other._head;
        _nodeCounter = other._nodeCounter;
    }

    LinkedList& operator=(const LinkedList& other)
    {
        if (this != &other) {
            InitializeFrom(other);
            _nodeCounter = other._nodeCounter;
        }

        return *this;
    }

    LinkedList& operator=(LinkedList&& other)
    {
        if (this != &other) {
            _head = other._head;
            delete other._head;
        }

        return *this;
    }

    size_t GetSize() const
    {
        return _nodeCounter;
    }

    bool operator==(LinkedList& other) const {
        if (GetSize() != other.GetSize()) {
            return false;
        }

        ConstIterator it = begin();
        Iterator otherIt = other.begin();
        for (; it != end(); ++it, ++otherIt) {
            if (it._item->_value != otherIt._item->_value) {
                return false;
            }
        }

        return true;
    }

    T operator[](int index)
    {
        Iterator it = begin();
        for (int i = 0; i < index; ++i) {
            it = it._item->_next;
        }

        return *it;
    }

    Iterator begin()
    {
        return Iterator(_head->_next);
    }

    const ConstIterator begin() const
    {
        return ConstIterator(_head->_next);
    }

    ReverseIterator rbegin()
    {
        return ReverseIterator(_head->_prev);
    }

    const ConstReverseIterator rbegin() const
    {
        return ConstReverseIterator(_head->_prev);
    }

    Iterator end()
    {
        return Iterator(_head);
    }

    ConstIterator end() const
    {
        return ConstIterator(_head);
    }

    ReverseIterator rend()
    {
        return ReverseIterator(_head);
    }

    ConstReverseIterator rend() const
    {
        return ConstReverseIterator(_head);
    }

    bool IsEmpty() const
    {
        return _head == _head->_next;
    }

    Iterator Insert(Iterator where, const T& value)
    {
        ListNode* node = new ListNode(where._item->_prev, where._item, value);

        where._item->_prev->_next = node;
        where._item->_prev = node;

        _nodeCounter++;

        return node;
    }

    void PushBack(const T& value)
    {
        Insert(end(), value);
    }

    void PushFront(const T& value)
    {
        Insert(begin(), value);
    }

    Iterator Erase(Iterator where)
    {
        where._item->_prev->_next = where._item->_next;
        where._item->_next->_prev = where._item->_prev;

        _nodeCounter--;

        auto next = where._item->_next;
        delete where._item;
        return Iterator(next);
    }

    void Remove(const T& value)
    {
        auto current = begin();
        while (current != end()) {
            if (*current == value) {
                Erase(current);
                return;
            }
            current++;
        }
    }

    void Reverse()
    {
        swap(_head->_next, _head->_prev);
        for (auto it = begin(); it != end(); ++it) {
            swap(it._item->_next, it._item->_prev);
        }
    }

    void Print()
    {
        for (T item: *this) {
            cout << item << " ";
        }
        cout << endl;
    }

private:
    ListNode* _head;
    int _nodeCounter;
};

#endif //LINKEDLIST_LINKEDLIST_H
