#ifndef SET_SET_H
#define SET_SET_H

#include <exception>
#include <iostream>

using namespace std;

template<typename T>
class Set {
public:
    Set();
    Set(int capacity);
    Set(const Set& other);
    Set(Set&& other);
    ~Set();
    void InitializeFrom(const Set<T>& other);

    bool Contains(T value) const;
    bool Push(T value);
    void Erase(T value);
    template<typename F> T Search(F functor, T element);

    size_t GetCapacity() const;
    size_t GetSize() const;

    Set& operator=(const Set& other);
    Set& operator=(Set&& other);
    Set operator+(const Set& other);
    Set operator*(const Set& other);
    Set operator-(const Set& other);
    bool operator==(const Set& other) const;
    bool operator!=(const Set& other) const;

    friend ostream& operator<<(ostream& out, const Set<T>& other) {
        out << "Set(";
        for (size_t i = 0; i < other._size - 1; ++i) {
            out << other._data[i] << ", ";
        }
        out << other._data[other._size - 1];
        out << ")";

        return out;
    }

private:
    T* _data;
    size_t _capacity;
    size_t _size;
};

template<typename T>
Set<T>::Set()
{
    _capacity = 0;
    _size = 0;
    _data = nullptr;
}

template<typename T>
Set<T>::Set(int capacity)
{
    _capacity = capacity;
    _size = 0;
    _data = new T[_capacity];
}

template<typename T>
void Set<T>::InitializeFrom(const Set<T>& other)
{
    _capacity = other._capacity;
    _size = other._size;

    _data = new T[_capacity];
    std::copy(other._data, other._data + _size, _data);
}

template<typename T>
Set<T>::Set(const Set& other)
{
    InitializeFrom(other);
}

template<typename T>
Set<T>::Set(Set&& other)
{
    _capacity = other._capacity;
    _size = other._size;
    _data = other._data;

    _capacity = 0;
    _size = 0;
    _data = nullptr;
}

template<typename T>
Set<T>::~Set()
{
    _capacity = 0;
    _size = 0;
    delete[] _data;
}

template<typename T>
bool Set<T>::Contains(T value) const {
    for (size_t i = 0; i < _size; ++i) {
        if (value == _data[i])
            return true;
    }
    return false;
}

template<typename T>
bool Set<T>::Push(T value)
{
    if (_size == _capacity) {
        throw std::overflow_error("Overflow");
    }

    if (Contains(value)) {
        return false;
    }

    _data[_size++] = value;
    return true;
}

template<typename T>
void Set<T>::Erase(T value)
{
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] == value) {
            swap(_data[i], _data[_size-1]);
            _size--;
        }
    }
}

template<typename T>
Set<T>& Set<T>::operator=(const Set& other)
{

    if (this != &other) {
        InitializeFrom(other);
    }

    return *this;
}

template<typename T>
Set<T>& Set<T>::operator=(Set&& other)
{
    if (this == &other) {
        return *this;
    }

    _capacity = other._capacity;
    _size = other._size;
    _data = other._data;

    other._size = 0;
    other._capacity = 0;
    other._data = nullptr;

    return *this;
}

template<typename T>
Set<T> Set<T>::operator+(const Set& other)
{
    Set<T> result(_capacity + other._capacity);

    for (size_t i = 0; i < _size; ++i) {
        result.Push(_data[i]);
    }

    for (size_t i = 0; i < other._size; ++i) {
        try {
            result.Push(other._data[i]);
        } catch (std::invalid_argument const &error) {
            continue;
        }
    }

    return result;
}

template<typename T>
Set<T> Set<T>::operator*(const Set& other)
{
    Set<T> result(std::min(_capacity, other._capacity));

    for (size_t i = 0; i < _size; ++i) {
        if (other.Contains(_data[i]))
            result.Push(_data[i]);
    }

    return result;
}

template<typename T>
Set<T> Set<T>::operator-(const Set& other)
{
    Set<T> result(_capacity);

    for (size_t i = 0; i < _size; ++i) {
        if (!other.Contains(_data[i]))
            result.Push(_data[i]);
    }

    return result;
}

template<typename T>
size_t Set<T>::GetCapacity() const
{
    return _capacity;
}

template<typename T>
size_t Set<T>::GetSize() const
{
    return _size;
}

template<typename T>
template<typename F>
T Set<T>::Search(F f, T element)
{
    T result;

    for (int i = 0; i < _size; ++i) {
        if (f(_data[i], element))
            result = _data[i];
    }

    return result;
}

template<typename T>
bool Set<T>::operator==(const Set& other) const
{
    return _data == other._data && _capacity == other._capacity && _size == other._size;
}

template<typename T>
bool Set<T>::operator!=(const Set& other) const
{
    return !(other == *this);
}

#endif //SET_SET_H
