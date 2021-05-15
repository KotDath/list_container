#pragma once
#include <utility>

template<class KeyType, class DataType, class Hash>
class UnorderedMap {
public:

private:
    class List {
    public:
        using pairValue   = std::pair<KeyType, DataType>;
        using pairPointer = pairValue*;

    private:
        struct Node {
            Node() : value(), next(nullptr), prev(nullptr) {}
            Node(const pairValue& value, pairPointer next, pairPointer prev) : value(value), next(next), prev(prev) {}
            pairValue value;
            pairPointer next;
            pairPointer prev;
        };
        List();
        explicit List(int count);
        List(int count, pairValue defaultValue);
        Node head;
        Node tail;
        int size;
    };
};

template<class KeyType, class DataType, class Hash>
UnorderedMap<KeyType, DataType, Hash>::List::List() : head(), tail(), size(0) {}

template<class KeyType, class DataType, class Hash>
UnorderedMap<KeyType, DataType, Hash>::List::List(int count) {

}

template<class KeyType, class DataType, class Hash>
UnorderedMap<KeyType, DataType, Hash>::List::List(int count, UnorderedMap::List::pairValue defaultValue) {

}
