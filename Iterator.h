#pragma once
#include "Container.h"
#include "BadIteratorException.h"
#include "RemoveException.h"

template<class Value>
class Node;

template<class Value>
class List;

template<class Value>
class ListIterator {
private:
    using pointer = Node<Value>*;
    using valueReference = Value&;
    using valuePointer = Value*;
    friend class List<Value>;
public:
    ListIterator() : val(nullptr), container(nullptr) {}
    explicit ListIterator(pointer input, List<Value>* container = nullptr) : val(input), container(container) {}
    ListIterator& operator=(const ListIterator& other) {
        if (&other == this) {
            return *this;
        }

        val = other.val; container = other.container; return *this;
    }
    ListIterator(const ListIterator& other) : val(other.val), container(other.container) {}
    valueReference operator*() {
        if (val == nullptr) {
            throw BadIteratorException();
        } else {
            return val->value;
        }
    }
    valuePointer operator->() {
        if (val == nullptr) {
            throw BadIteratorException();
        } else {
            return &(val->value);
        }
    }
    const valueReference operator*() const {
        if (val == nullptr) {
            throw BadIteratorException();
        } else {
            return val->value;
        }
    }
    const valuePointer operator->() const {
        if (val == nullptr) {
            throw BadIteratorException();
        } else {
            return &(val->value);
        }
    }

    ListIterator& operator++() {
        if (val == nullptr) {
            throw BadIteratorException();
        } else {
            val = val->right;
        }

        return *this;
    }

    ListIterator operator++(int) {
        auto varPointer = *this;
        if (val == nullptr) {
            throw BadIteratorException();
        } else {
            val = val->right;
        }
        return varPointer;
    }

    ListIterator& operator--() {
        if (val == nullptr) {
            throw BadIteratorException();
        } else {
            val = val->left;
        }

        return *this;
    }

    ListIterator operator--(int) {
        auto varPointer = *this;
        if (val == nullptr) {
            throw BadIteratorException();
        } else {
            val = val->left;
        }
        return varPointer;
    }

    friend bool operator==(const ListIterator& first, const ListIterator& second) { return first.val == second.val && first.container == second.container; }

    friend bool operator!=(const ListIterator& first, const ListIterator& second) { return first.val != second.val || first.container != second.container; }
private:
    List<Value>* container;
    pointer val;
};