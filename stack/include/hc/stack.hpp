////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Braden Hitchcock - MIT License (https://opensource.org/licenses/MIT)                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef HC_STACK_H
#define HC_STACK_H

#include <algorithm>
#include <stdexcept>

namespace hc {

/// Contains a dynamically-sized list of elements of type `T` that can only be accessed in Last-In First-Out order.
///
template <typename T>
class Stack {
   public:
    Stack() {
        _capacity = cInitialCapacity;
        _pData = new T[_capacity];
        _size = 0;
    }

    Stack(const Stack<T>& other) {
        _capacity = other._capacity;
        _size = other._size;
        _pData = new T[_capacity];
        std::copy(other._pData, other._pData + other._pSize, _pData);
    }

    Stack(Stack<T>&& other) : Stack() { swap(*this, other); }

    ~Stack() { delete[] _pData; }

    friend void swap(Stack<T>& first, Stack<T>& second) noexcept {
        using std::swap;
        swap(first._pData, second._pData);
        swap(first._capacity, second._capacity);
        swap(first._size, second._size);
    }

    Stack<T>& operator=(Stack<T> other) {
        swap(*this, other);
        return *this;
    }    

    const T& top() const {
        assertNotEmpty();
        return _pData[_size - 1];
    }

    T& top() {
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

    void push(T value) {
        if (_size == _capacity) {
            reserve(_capacity * cCapacityStep);
        }
        _pData[_size] = std::move(value);
        ++_size;
    }

    void pop() {
        assertNotEmpty();
        --_size;
    }

   private:
    static constexpr size_t cInitialCapacity = 2;
    static constexpr size_t cCapacityStep = 2;

    T* _pData;
    size_t _size;
    size_t _capacity;

    void assertNotEmpty() {
        if (empty()) {
            throw std::out_of_range("stack is empty");
        }
    }
};

}  // namespace hc

#endif