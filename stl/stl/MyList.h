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
std::ostream& operator<<(std::ostream& out, Node<_Value>& node) {
	out << node.value;
	return out;
}

template<class _Value>
class ListIterator;


template<class _Value>
class MyList {
public:
	MyList();
	MyList(MyList& other);
	MyList& operator=(MyList& other);
	void PushBack(const _Value& val);
	ListIterator<_Value> begin() { return ListIterator(head); }
	ListIterator<_Value> end() { 
		return ListIterator<_Value>(nullptr);
	}
	~MyList();
private:
	Node<_Value>* head;
	Node<_Value>* tail;
	size_t count;
};

template<class _Value>
MyList<_Value>::MyList() : head(nullptr), tail(nullptr), count(0) {

}

template<class _Value>
MyList<_Value>::MyList(MyList<_Value>& other) {
	for (auto it = other.begin(); it != other.end(); ++it) {
		PushBack(it->value);
	}
}

template<class _Value>
MyList<_Value>& MyList<_Value>::operator=(MyList& other) {
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
		for (auto it = other.begin(); it != other.end(); ++it) {
			PushBack(it->value);
		}
	}
}

template<class _Value>
void MyList<_Value>::PushBack(const _Value& val) {
	if (head == nullptr) {
		head = new Node(val);
		tail = head;
	}
	else {
		auto newNode = new Node(val);
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
	using pointer =   Node<_Value>*;
	using reference = Node<_Value>&;
	using value =	  Node<_Value>;
public:
	ListIterator(pointer input) : val(input) {}
	reference operator*() { return *val; }
	pointer operator->() { return val; }
	ListIterator& operator++() { val = val->right; return *this; }
	ListIterator operator++(int) { pointer = val; val = val->right; return pointer; }
	friend bool operator==(const ListIterator<_Value>& first, const ListIterator<_Value>& second) { return first.val == second.val; }
	friend bool operator!=(const ListIterator<_Value>& first, const ListIterator<_Value>& second) { return first.val != second.val; }
private:
	pointer val;
};