#pragma once
#include<iostream>
#include<vector>
//#include<algorithm>

inline static size_t getNextPrime(size_t num);
static bool isPrime(size_t num);

template<class K, class T>
class HashTable {
public:
	struct Item {
		T data;
		K key;
		Item() {}
		Item(const K& k, const T& d) : data(d), key(k), isValid(true) {}
		friend class HashTable;

	private:
		bool isValid = false;
	};

	HashTable(size_t size);
	virtual ~HashTable() {}
	int find(const K& key) const;
	void insert(const Item& item);
	void remove(const K& key);
	bool update(const Item& item);
	virtual void print(std::ostream & = std::cout) const = 0;

protected:
	size_t hash(const K& key, size_t i = 0) const;
	virtual size_t h1(const K& key) const = 0;
	virtual size_t h2(const K& key) const = 0;
	std::vector<Item> table;
	static void setItemValidation(Item& item, bool valid);
	static bool getItemValidation(const Item& item);
};


template<class K, class T>
inline HashTable<K, T>::HashTable(size_t size) : table(std::vector<Item>(getNextPrime(size))) { }

template<class K, class T>
inline size_t HashTable<K, T>::hash(const K& key, size_t i) const {
	return (h1(key) + i * h2(key)) % table.size();
}

template<class K, class T>
inline int HashTable<K, T>::find(const K& key) const {
	for (size_t i = 0; i < table.size(); ++i) {
		size_t result = hash(key, i);
		const Item& item = table[result];

		if (!item.isValid)
			return -1;
		if (item.key == key)
			return result;
	}
	return -1;
}

template<class K, class T>
inline void HashTable<K, T>::insert(const Item& item) {
	for (size_t i = 0; i < table.size(); ++i) {
		size_t result = hash(item.key, i);
		const Item& currentItem = table[result];

		if (!currentItem.isValid) {
			table[result] = item;
			return;
		}
	}
	throw "Couldn't insert to table (table is full)";
}

template<class K, class T>
inline void HashTable<K, T>::remove(const K& key) {
	int index = find(key);
	if (index >= 0)
		table[index].isValid = false;
}

template<class K, class T>
inline bool HashTable<K, T>::update(const Item& item) {
	int index = find(item.key);
	if (index >= 0) {
		table[index] = item;
		return true;
	}
	return false;
}

template<class K, class T>
inline void HashTable<K, T>::setItemValidation(Item& item, bool valid) {
	item.isValid = valid;
}

template<class K, class T>
inline bool HashTable<K, T>::getItemValidation(const Item& item) {
	return item.isValid;
}

inline static size_t getNextPrime(size_t num) {
	while (!isPrime(num++));
	return num;
}

static bool isPrime(size_t num) {
	// Corner cases 
	if (num <= 1)
		return false;
	if (num <= 3)
		return true;

	// This is checked so that we can skip 
	// middle five numbers in below loop 
	if (num % 2 == 0 || num % 3 == 0)
		return false;

	for (int i = 5; i * i <= num; i = i + 6)
		if (num % i == 0 || num % (i + 2) == 0)
			return false;

	return true;
}
