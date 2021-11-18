////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Braden Hitchcock - MIT License (https://opensource.org/licenses/MIT)                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef HC_VECTOR_H
#define HC_VECTOR_H

#include <algorithm>
#include <stdexcept>

namespace hc {

/// Contains a dynamically-sized list of elements of type `T`.
///
/// The `Vector` allocates enough room for two elements immediately on construction. As the size increases, if the
/// capacity needs to increase, it is doubled.
///
template <typename T>
class Vector {
   public:
    Vector() {
        _capacity = cInitialCapacity;
        _pData = new T[_capacity];
        _size = 0;
    }

    Vector(const Vector<T>& other) {
        _capacity = other._capacity;
        _size = other._size;
        _pData = new T[_capacity];
        std::copy(other._pData, other._pData + other._pSize, _pData);
    }

    Vector(Vector<T>&& other) : Vector() { swap(*this, other); }

    ~Vector() { delete[] _pData; }

    friend void swap(Vector<T>& first, Vector<T>& second) noexcept {
        using std::swap;
        swap(first._pData, second._pData);
        swap(first._capacity, second._capacity);
        swap(first._size, second._size);
    }

    Vector<T>& operator=(Vector<T> other) {
        swap(*this, other);
        return *this;
    }

    const T& operator[](size_t index) const {
        assertInRange(index);
        return _pData[index];
    }

    T& operator[](size_t index) {
        assertInRange(index);
        return _pData[index];
    }

    const T& front() const {
        assertNotEmpty();
        return _pData[0];
    }

    T& front() {
        assertNotEmpty();
        return _pData[0];
    }

    const T& back() const {
        assertNotEmpty();
        return _pData[_size - 1];
    }

    T& back() {
        assertNotEmpty();
        return _pData[_size - 1];
    }

    bool empty() const noexcept { return _size == 0; }

    size_t size() const noexcept { return _size; }

    size_t capacity() const noexcept { return _capacity; };

    void reserve(size_t newCapacity) {
        auto tailIndex = _size;
        if (newCapacity < _size) {
            tailIndex = newCapacity;
        }
        auto tmp = _pData;
        _pData = new T[newCapacity];
        std::copy(tmp, tmp + tailIndex, _pData);
        delete[] tmp;
        _capacity = newCapacity;
    }

    void pushBack(const T& value) {
        if (_size == _capacity) {
            reserve(_capacity * cCapacityStep);
        }
        _pData[_size] = value;
        ++_size;
    }

    void insert(size_t index, const T& value) {
        if (index > _size) {
            throw std::out_of_range();
        }
        if (_size == _capacity) {
            reserve(_capacity * cCapacityStep);
        }
        for (size_t i = _size; i >= 0; --i) {
            _pData[i + 1] = _pData[i];
            if (i == index) {
                _pData[i] = value;
                break;
            }
        }
        ++_size;
    }

    void erase(size_t index) {
        assertInRange(index);
        for (size_t i = index + 1; i < _size; ++i) {
            _pData[i - 1] = _pData[i];
        }
        --_size;
    }

    void popBack() {
        assertNotEmpty();
        --_size;
    }

   private:
    static constexpr size_t cInitialCapacity = 2;
    static constexpr size_t cCapacityStep = 2;

    T* _pData;
    size_t _size;
    size_t _capacity;

    void assertInRange(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("index out of vector range");
        }
    }

    void assertNotEmpty() {
        if (empty()) {
            throw std::out_of_range("vector is empty");
        }
    }
};

}  // namespace hc

#endif