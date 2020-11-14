#pragma once
#include<iostream>
#include<vector>

// Finds the next prime number from the given number.
inline static size_t getNextPrime(size_t num);
// Checks whether the given number is a prime num or not.
static bool isPrime(size_t num);

// Exception to throw when the table is full while trying to insert.
struct HashTableIsFullException {};

inline std::ostream& operator<< (std::ostream& os, const HashTableIsFullException& e) {
	return os << "Cannot insert to a full hash table.";
}

template<class K, class T>
class HashTable {
public:
	struct Item {
		T data;
		K key;
		Item() : isValid(false) {}
		Item(const K& k, const T& d) : data(d), key(k), isValid(true) {}
		friend class HashTable;

	private:
		bool isValid;
	};

	HashTable(size_t size); // Ctor
	// Virtual dtor for abstract class.
	virtual ~HashTable() {}
	// Finds the index of the item with the given key. If not found returns -1.
	int find(const K& key) const;
	// Inserts the given item to the table.
	// If the table is full, HashTableIsFullException is thrown.
	void insert(const Item& item);
	// Removes the item with the given key.
	void remove(const K& key);
	// Updates an item in the table. If successfully updated returns True, else False.
	bool update(const Item& item);
	// Prints the table into a given output stream.
	virtual void print(std::ostream & = std::cout) const = 0;

protected:
	// Evaluate the hash from the key with a given try.
	// The evaluation algorithm is double hashing.
	size_t hash(const K& key, size_t i = 0) const;
	// Hash functions for the inherited class to implement.
	virtual size_t h1(const K& key) const = 0;
	virtual size_t h2(const K& key) const = 0;

	std::vector<Item> table;

	// Allows access to the item's validation from the inherited class.
	static void setItemValidation(Item& item, bool valid);
	static bool getItemValidation(const Item& item);
};


// Initialize the data vector with the next prime number of the size.
template<class K, class T>
inline HashTable<K, T>::HashTable(size_t size) : table(std::vector<Item>(getNextPrime(size))) { }

template<class K, class T>
inline size_t HashTable<K, T>::hash(const K& key, size_t i) const {
	// Double hashing algorithm.
	return (h1(key) + i * h2(key)) % table.size();
}

template<class K, class T>
inline int HashTable<K, T>::find(const K& key) const {
	for (size_t i = 0; i < table.size(); ++i) {
		size_t result = hash(key, i);
		const Item& item = table[result];

		if (!item.isValid)
			return -1; // Means that the key is not in the table.

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
			// Found the next empty cell.
			table[result] = item;
			return;
		}
	}

	// When the table is full.
	throw HashTableIsFullException();
}

template<class K, class T>
inline void HashTable<K, T>::remove(const K& key) {
	int index = find(key);
	// Checks whether the item was found.
	if (index >= 0)
		table[index].isValid = false;
}

template<class K, class T>
inline bool HashTable<K, T>::update(const Item& item) {
	int index = find(item.key);

	// Checks whether the item was found.
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
	if (isPrime(num)) return num;
	while (!isPrime(++num));
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
