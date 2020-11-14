#pragma once
#include "HashTable.h"
#include<list>

class HSubject : public HashTable<std::string, std::list<std::string> > {
public:
	// Ctor with a given size.
	HSubject(size_t size) : HashTable(size) { }
	// Resets the table.
	void initTable();
	// Prints the titles of a given subject.
	void printSubject(const std::string& subject) const;
	// Adds a title to the subject's list.
	// If the subject wasn't found, it adds it into the table.
	void addSubjectAndTitle(const std::string& subject, const std::string& title);
	// Prints the first N titles of the subject.
	void printFirstN(const std::string& subject, size_t N) const;
	// Prints the whole table.
	void print(std::ostream & = std::cout) const override;

private:
	// Implementation of the double hashing functions.
	size_t h1(const std::string& key) const override;
	size_t h2(const std::string& key) const override;
	// Converts the string key into a number in order to hash the key.
	// Parameter chars: The amount of chars to convert to num.
	static size_t stringToNum(const std::string& str, size_t chars = 3);
};

// Calls hs.print function with this stream.
std::ostream& operator<<(std::ostream& os, const HSubject& hs);

