#pragma once

#include "Iterator.h"
#include <iostream>
#include "BadIteratorException.h"
#include "RemoveException.h"

template<class Value>
class ListIterator;

template<class Value>
struct Node {
    Node() : value(), left(nullptr), right(nullptr) {}
    explicit Node(const Value& value) : value(value), left(nullptr), right(nullptr) {
    }
    ~Node() {
        left = nullptr;
        right = nullptr;
    }
    Value value;
    Node<Value>* left;
    Node<Value>* right;
};

template<class Value>
class List {
public:
    using iterator = ListIterator<Value>;
    using constIterator = ListIterator<const Value>;

    List();
    explicit List(size_t count);
    List(size_t count,const Value& defaultValue);
    List(iterator begin, iterator end);
    List(std::initializer_list<Value> init);
    List(const List& other);
    List(List&& other);

    ~List();

    List& operator=(const List& other);
    List& operator=(List&& other);

    iterator begin();
    iterator begin() const;

    iterator end();
    iterator end() const;

    void pushBack(const Value& elem);
    void popBack();
    void pushFront(const Value& elem);
    void popFront();

    iterator insert(iterator pos, const Value& elem);
    iterator insert(iterator pos, iterator begin, iterator end);
    iterator erase(iterator pos);

    void resize(size_t num);
    bool empty();
    size_t size();
    void clear();
private:
    Node<Value>* head;
    Node<Value>* tail;
    size_t count{};
};

template<class Value>
List<Value>::List() : head(nullptr), tail(nullptr), count(0) {

}

template<class Value>
List<Value>::List(size_t count) : head(nullptr), tail(nullptr), count(0) {
    for (int i = 0; i < count; ++i) {
        pushBack(Value());
    }
}

template<class Value>
List<Value>::List(size_t count, const Value& defaultValue) : head(nullptr), tail(nullptr), count(0) {
    for (int i = 0; i < count; ++i) {
        pushBack(defaultValue);
    }
}

template<class Value>
List<Value>::List(iterator begin, iterator end) : head(nullptr), tail(nullptr), count(0) {
    for (auto it = begin; it != end; ++it) {
        pushBack(*it);
    }
}

template<class Value>
List<Value>::List(std::initializer_list<Value> init) : head(nullptr), tail(nullptr), count(0) {
    for (auto it = init.begin(); it != init.end(); ++it) {
        pushBack(*it);
    }
}

template<class Value>
List<Value>::List(const List& other) : head(nullptr), tail(nullptr), count(0) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        pushBack(*it);
    }
}

template<class Value>
List<Value>::List(List&& other) : head(other.head), tail(other.tail), count(other.count) {
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

template<class Value>
List<Value>& List<Value>::operator=(const List& other) {
    if (&other == this) {
        return *this;
    }

    clear();
    for (auto it = other.begin(); it != other.end(); ++it) {
        pushBack(*it);
    }

    return *this;
}

template<class Value>
List<Value>& List<Value>::operator=(List&& other) {
    if (&other == this) {
        return *this;
    }

    head = other.head;
    tail = other.tail;
    count = other.count;
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;

    return *this;
}

template<class Value>
void List<Value>::clear() {
    while (count != 0) {
        popFront();
    }
}

template<class Value>
ListIterator<Value> List<Value>::begin() {
    return iterator(head, this);
}

template<class Value>
ListIterator<Value> List<Value>::begin() const {
    return iterator(head, this);
}

template<class Value>
ListIterator<Value> List<Value>::end() {
    return iterator(nullptr, this);
}

template<class Value>
ListIterator<Value> List<Value>::end() const {
    return iterator(nullptr, this);
}

template<class Value>
void List<Value>::pushBack(const Value& elem) {
    auto newNode = new Node{elem};
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else if (head == tail) {
        tail = newNode;
        tail->left = head;
        head->right = tail;
    } else {
        auto* tmp = tail;
        tail = newNode;
        tmp->right = tail;
        tail->left = tmp;
    }

    ++count;
}

template<class Value>
void List<Value>::popBack() {
    if (head == nullptr) {
        throw RemoveException();
    } else if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else if (head->right == tail) {
        delete tail;
        head->right = nullptr;
        tail = head;
    } else {
        auto* tmp = tail->left;
        delete tail;
        tmp->right = nullptr;
        tail = tmp;
    }

    --count;
}

template<class Value>
void List<Value>::pushFront(const Value& elem) {
    auto newNode = new Node{elem};
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else if (head == tail) {
        head = newNode;
        head->right = tail;
        tail->left = head;
    } else {
        auto* tmp = head;
        head = newNode;
        tmp->left = head;
        head->right = tmp;
    }

    ++count;
}

template<class Value>
void List<Value>::popFront() {
    if (tail == nullptr) {
        throw RemoveException();
    } else if (head == tail) {
        delete tail;
        head = nullptr;
        tail = nullptr;
    } else if (tail->left == head) {
        delete head;
        tail->left = nullptr;
        head = tail;
    } else {
        auto* tmp = head->right;
        delete head;
        tmp->left = nullptr;
        head = tmp;
    }

    --count;
}

template<class Value>
ListIterator<Value> List<Value>::insert(iterator pos, const Value& elem) {
    if (pos.container != this) {
        throw BadIteratorException();
    }
    Node<Value>* newNode = new Node{elem};
    if (pos.val->left == nullptr) {
        auto* tmp = head;
        head = newNode;
        head->right = tmp;
        tmp->left = head;
    } else {
        auto* tmpLeft = pos.val->left;
        auto* tmp = pos.val;
        tmp->left = newNode;
        tmpLeft->right = newNode;
        newNode->left = tmpLeft;
        newNode->right = tmp;
    }

    ++count;
    return ListIterator(newNode, this);
}

template<class Value>
ListIterator<Value> List<Value>::insert(iterator pos, iterator begin, iterator end) {
    if (pos.container != this) {
        throw BadIteratorException();
    }
    if(begin == end) {
        return pos;
    }

    auto it = begin;
    insert(pos, *it);
    auto result = it;
    ++it;
    for (; it != end; ++it) {
        insert(pos, *it);
    }

    return result;
}

template<class Value>
ListIterator<Value> List<Value>::erase(iterator pos) {
    if (pos.container != this) {
        throw BadIteratorException();
    }

    if (head == nullptr) {
        throw RemoveException();
    }

    if (pos.val->left == nullptr) {
        popFront();
        return ListIterator(head, this);
    } else if (pos.val->right == nullptr) {
        popBack();
        return ListIterator(tail, this);
    } else {
        auto tmpLeft = pos.val->left;
        auto tmpRight = pos.val->right;
        delete pos.val;
        tmpLeft->right = tmpRight;
        tmpRight->left = tmpLeft;
        --count;
        return ListIterator(tmpRight, this);
    }

}

template<class Value>
void List<Value>::resize(size_t num) {
    if (num < count) {
        for (int i = 0; i < count - num; ++i) {
            popFront();
        }
    } else {
        for(int i = 0; i < num - count; ++i) {
            pushBack(Value());
        }
    }
}

template<class Value>
bool List<Value>::empty() {
    return count == 0;
}

template<class Value>
size_t List<Value>::size() {
    return count;
}

template<class Value>
List<Value>::~List() {
    clear();
}
