#pragma once
#include <istream>
#include <ostream>

template<class _Value>
struct Node {
    Node() : value(), left(nullptr), right(nullptr) {}
    explicit Node(_Value value) : value(value), left(nullptr), right(nullptr) {}
    ~Node() {
        left = nullptr;
        right = nullptr;
    }
    _Value value;
    Node* left;
    Node* right;
};

template<class _Value>
std::istream& operator>>(std::istream& in, Node<_Value>& node) {
    in >> node.value;
    return in;
}

template<class _Value>
std::ostream& operator<<(std::ostream& out, const Node<_Value>& node) {
    out << node.value;
    return out;
}

template<class _Value>
class ListIterator;


template<class _Value>
class MyList {
private:
    using iterator = ListIterator<_Value>;
    using constIterator = ListIterator<const _Value>;
public:
    MyList();
    MyList(const MyList& other);
    MyList& operator=(const MyList& other);
    void PushBack(const _Value& val);
    iterator begin() {
        return head;
    }

    constIterator cbegin() const {
        return head;
    }

    iterator end() {
        return nullptr;
    }

    constIterator cend() const {
        return nullptr;
    }
    ~MyList();
private:
    Node<_Value>* head;
    Node<_Value>* tail;
    size_t count{};
};

template<class _Value>
MyList<_Value>::MyList() : head(nullptr), tail(nullptr), count(0) {

}

template<class _Value>
MyList<_Value>::MyList(const MyList& other) {
    auto* node = other.head;
    if (node != nullptr) {
        while (node != other.tail) {
            PushBack(node->value);
            node = node->right;
        }

        PushBack(tail->value);
    }
}

template<class _Value>
MyList<_Value>& MyList<_Value>::operator=(const MyList& other) {
    if (this == &other) {
        return *this;
    }
    else {
        auto* removableNode = head;
        while (removableNode != tail) {
            auto* nextPtr = removableNode->right;
            delete removableNode;
            removableNode = nextPtr;
        }
        delete tail;
        head = nullptr;
        tail = nullptr;
        count = 0;
        auto* node = other.head;
        if (node != nullptr) {
            while (node != other.tail) {
                PushBack(node->value);
                node = node->right;
            }

            PushBack(tail->value);
        }
    }
}

template<class _Value>
void MyList<_Value>::PushBack(const _Value& val) {
    if (head == nullptr) {
        head = new Node<_Value>(val);
        tail = head;
    }
    else {
        auto newNode = new Node<_Value>(val);
        if (head == tail) {
            tail = newNode;
            tail->left = head;
            head->right = tail;
        }
        else {
            auto* tmp = tail;
            tail = newNode;
            tmp->right = tail;
            tail->left = tmp;
        }
    }

    ++count;
}

template<class _Value>
MyList<_Value>::~MyList() {
    auto* removableNode = head;
    while (removableNode != tail) {
        auto* nextPtr = removableNode->right;
        delete removableNode;
        removableNode = nextPtr;
    }

    delete tail;
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template<class _Value>
class ListIterator {
private:
    using pointer = Node<_Value>*;
    using valueReference = _Value&;
    using valuePointer = _Value*;
public:
    ListIterator(pointer input) : val(input) {}
    valueReference operator*() { return val->value; }
    valuePointer operator->() { return &(val->value); }
    const valueReference operator*() const { return val->value; }
    const valuePointer operator->() const { return &(val->value); }
    ListIterator& operator++() { val = val->right; return *this; }
    ListIterator operator++(int) { auto varPointer = val; val = val->right; return varPointer; }
    friend bool operator==(const ListIterator& first, const ListIterator& second) { return first.val == second.val; }
    friend bool operator!=(const ListIterator& first, const ListIterator& second) { return first.val != second.val; }
private:
    pointer val;
};