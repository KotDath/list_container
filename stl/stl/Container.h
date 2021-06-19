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
	//!!!добавить копирование
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

	hash;
	nodeCount;
	bucketCount;
	maxLoad;
	buckets = nullptr; //!!!добавить копирование
	return *this;
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>& UnorderedMap<_KeyType, _DataType, _Hash>::operator=(const UnorderedMap&& other) {
	if (this == &other) {
		return *this;
	}
}

template <class _KeyType, class _DataType, class _Hash>
_DataType& UnorderedMap<_KeyType, _DataType, _Hash>::operator[](const _KeyType& key) {

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
UnorderedMapIterator<_KeyType, _DataType> UnorderedMap<_KeyType, _DataType, _Hash>::begin() {

}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType> UnorderedMap<_KeyType, _DataType, _Hash>::end() {

}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType> UnorderedMap<_KeyType, _DataType, _Hash>::insert(const bucketCell& insertData) {

}

template <class _KeyType, class _DataType, class _Hash>
void UnorderedMap<_KeyType, _DataType, _Hash>::erase(_KeyType key) {

}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType> UnorderedMap<_KeyType, _DataType, _Hash>::erase(iterator pos) {

}