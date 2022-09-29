#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <iostream>
#include <vector>

#define DEFAULT_SIZE 5

using namespace std;

enum class Status {
    FREE,
    IN_USE,
    DELETED
};

template<typename ValueType>
struct Node {
    size_t    _key;
    ValueType _value;
    Status    _status = Status::FREE;

    void InitializeFrom(size_t key, ValueType value, Status status)
    {
        _key = key;
        _value = value;
        _status = status;
    }

    void Print()
    {
        cout << _key << " - ";
        cout << _value << " - ";

        if (_status == Status::FREE)
            cout << "FREE" << endl;
        else if (_status == Status::IN_USE)
            cout << "IN USE" << endl;
        else
            cout << "DELETED" << endl;
    }
};


template<typename ValueType, typename Hash = std::hash<ValueType> >
class HashTable {
public:
    HashTable(size_t _capacity): _capacity(_capacity), _size(0), _deletedCount(0)
    {
        _nodes = new Node<ValueType>*[_capacity];

        for (size_t i = 0; i < _capacity; i++)
            _nodes[i] = new Node<ValueType>();
    }

    HashTable(): HashTable(DEFAULT_SIZE) {}

    ~HashTable() {
        delete[] _nodes;
        _size = 0;
        _capacity = 0;
        _deletedCount = 0;
    }

    HashTable(const HashTable& other) = delete;
    HashTable(HashTable&& other) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable& operator=(HashTable&& src) = delete;

    bool Insert(const ValueType& value)
    {
        if (_deletedCount > _size)
            Rehash(false);
        else if (2 * _size > _capacity)
            Rehash(true);

        int key = ComputeHash(value);
        for (int i = 0, index = key; i < _capacity; ++i, ++index) {
            if (_nodes[index]->_status == Status::FREE || _nodes[index]->_status == Status::DELETED) {
                _nodes[index]->InitializeFrom(key, value, Status::IN_USE);
                _size++;
                return true;
            }

            if (_nodes[index]->_value == value)
                return false;

            if (index == _capacity - 1)
                index = -1;
        }

        return false;
    }

    bool Remove(const ValueType& value)
    {
        int index = FindIndex(value);

        if (index == -1)
            return false;

        _nodes[index]->_status = Status::DELETED;

        _size--;
        _deletedCount++;

        return true;
    }

    bool Contains(const ValueType& value)
    {
        return FindIndex(value) != -1;
    }

    ValueType& operator[](size_t index)
    {
        return _nodes[index]->_value;
    }

    size_t GetSize()
    {
        return _size;
    }

    size_t GetCapacity()
    {
        return _capacity;
    }

    void Print()
    {
        cout << "Key - Value - Status:" << endl;
        for (size_t i = 0; i < _capacity; ++i) {
            _nodes[i]->Print();
        }
        cout << endl;
    }

    int FindIndex(const ValueType& value)
    {
        int key = ComputeHash(value);

        for (int i = 0, index = key; i < _capacity; ++i, ++index) {
            if (_nodes[index]->_status == Status::FREE || _nodes[index]->_status == Status::DELETED) {
                break;
            }

            if (_nodes[index]->_value == value)
                return index;

        }

        return -1;
    }

protected:

    void Rehash(bool isIncrease)
    {
        vector<ValueType> values;

        for (int i = 0; i < _capacity; ++i) {
            if (_nodes[i]->_status == Status::IN_USE)
                values.push_back(_nodes[i]->_value);
        }

        _capacity = isIncrease ? _capacity << 1 : _capacity;
        _size = 0;
        _deletedCount = 0;

        delete[] _nodes;
        _nodes = new Node<ValueType>*[_capacity];
        for (size_t i = 0; i < _capacity; i++)
            _nodes[i] = new Node<ValueType>();

        for (ValueType item: values) {
            Insert(item);
        }
    }

    int ComputeHash(const ValueType& value)
    {
        return h(value) % _capacity;
    }

private:
    size_t _capacity;
    size_t _size;
    size_t _deletedCount;

    Node<ValueType>** _nodes;
    Hash h;
};

#endif //HASHTABLE_HASHTABLE_H
