#pragma once

#include <utility>
#include <initializer_list>

#include "Iterator.h"
#include "MyList.h"

template <class _KeyType, class _DataType, class _Hash = std::hash<_KeyType>>
class UnorderedMap {
public:
	using iterator = UnorderedMapIterator<_KeyType, _DataType>;
	using bucketCell = std::pair<_KeyType, _DataType>;

	explicit UnorderedMap(size_t bucketCount = 0);
	UnorderedMap(std::initializer_list<bucketCell> values);
	UnorderedMap(const UnorderedMap& other);
	UnorderedMap(UnorderedMap&& other);

	~UnorderedMap();

	UnorderedMap& operator=(const UnorderedMap& other);
	UnorderedMap& operator=(const UnorderedMap&& other);
	_DataType& operator[](const _KeyType& key);
	const _DataType& operator[](const _KeyType& key) const;

	size_t maxLoadFactor();
	void maxLoadFactor(size_t val);
	_DataType& at(const _KeyType& key);
	const _DataType& at(const _KeyType& key);
	iterator begin();
	iterator end();
	iterator insert(const bucketCell& insertData);
	void erase(_KeyType key);
	iterator erase(iterator pos);	
	void reserve(size_t num);
	bool empty();
	size_t size();
	void clear();
private:
	void rehash();
	_Hash hash;
	size_t nodeCount;
	size_t bucketCount;
	float maxLoad;
	MyList<std::pair<_KeyType, _DataType>>* buckets;
};

template <class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::UnorderedMap(size_t bucketCount) : hash(_Hash()), nodeCount(0), bucketCount(bucketCount), maxLoad(4), buckets(nullptr) {
	if (bucketCount > 0) {
		buckets = new MyList[bucketCount];
	}
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::UnorderedMap(std::initializer_list<bucketCell> values) : UnorderedMap() {
	for (auto it = values.begin(); it != values.end(); ++it) {
		insert(*it);
	}
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::UnorderedMap(const UnorderedMap& other) : hash(other.hash), 
																					nodeCount(other.nodeCount), bucketCount(other.bucketCount), 
																					maxLoad(other.maxLoad), buckets(nullptr) {
	if (bucketCount > 0) {
		buckets = new MyList[bucketCount];

	}
	for (size_t i = 0; i < bucketCount; ++i) {
		buckets[i] = other.buckets[i];
	}
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::UnorderedMap(UnorderedMap&& other) : hash(other.hash), nodeCount(other.nodeCount),
																			   bucketCount(other.bucketCount), maxLoad(other.maxLoad), 
																			   buckets(other.buckets) {
	other.nodeCount = 0;
	other.bucketCount = 0;
	other.maxLoad = 4;
	other.buckets = nullptr;
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::~UnorderedMap() {
	delete[] buckets;
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>& UnorderedMap<_KeyType, _DataType, _Hash>::operator=(const UnorderedMap& other) {
	if (this == &other) {
		return *this;
	}

	hash = other.hash;
	nodeCount = other.nodeCount;
	if (bucketCount != other.bucketCount && other.bucketCount != 0) {
		delete[] buckets;
	}
	bucketCount = other.bucketCount;
	maxLoad = other.maxLoad;
	if (bucketCount > 0) {
		buckets = new MyList[bucketCount];

	}
	for (size_t i = 0; i < bucketCount; ++i) {
		buckets[i] = other.buckets[i];
	}
	return *this;
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>& UnorderedMap<_KeyType, _DataType, _Hash>::operator=(const UnorderedMap&& other) {
	if (this == &other) {
		return *this;
	}

	delete[] buckets;
	hash = other.hash;
	nodeCount = other.nodeCount;
	bucketCount = other.bucketCount;
	maxLoad = other.maxLoad;
	buckets = other.buckets;
	other.nodeCount = 0;
	other.bucketCount = 0;
	other.maxLoad = 4;
	other.buckets = nullptr;
}

template <class _KeyType, class _DataType, class _Hash>
_DataType& UnorderedMap<_KeyType, _DataType, _Hash>::operator[](const _KeyType& key) {
	size_t position = hash(key) % bucketCount;
	buckets[position];
}

template <class _KeyType, class _DataType, class _Hash>
const _DataType& UnorderedMap<_KeyType, _DataType, _Hash>::operator[](const _KeyType& key) const {

}

template <class _KeyType, class _DataType, class _Hash>
size_t UnorderedMap<_KeyType, _DataType, _Hash>::maxLoadFactor() {
	return maxLoad;
}

template <class _KeyType, class _DataType, class _Hash>
void  UnorderedMap<_KeyType, _DataType, _Hash>::maxLoadFactor(size_t val) {
	maxLoad = val;
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::iterator UnorderedMap<_KeyType, _DataType, _Hash>::begin() {
	return;
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::iterator UnorderedMap<_KeyType, _DataType, _Hash>::end() {
	return;
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::iterator UnorderedMap<_KeyType, _DataType, _Hash>::insert(const bucketCell& insertData) {
	if (static_cast<float>(nodeCount) / bucketCount >= maxLoad) {
		rehash();
	}

	size_t position = hash(insertData.first) % bucketCount;
	buckets[position].PushBack(insertData);
	++nodeCount;
	return;
}

template <class _KeyType, class _DataType, class _Hash>
void UnorderedMap<_KeyType, _DataType, _Hash>::erase(_KeyType key) {

}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::iterator UnorderedMap<_KeyType, _DataType, _Hash>::erase(iterator pos) {

}

template<class _KeyType, class _DataType, class _Hash>
size_t UnorderedMap<_KeyType, _DataType, _Hash>::size() {
	return nodeCount;
}

template<class _KeyType, class _DataType, class _Hash>
bool UnorderedMap<_KeyType, _DataType, _Hash>::empty() {
	return nodeCount == 0;
}
