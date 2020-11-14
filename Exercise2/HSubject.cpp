#include "HSubject.h"
#include <cmath>

void HSubject::initTable() {
	// Sets every item on the table to invalid.
	for (std::vector<Item>::iterator it = table.begin(); it != table.end(); it++)
		setItemValidation(*it, false);
}

void HSubject::printSubject(const std::string& subject) const {
	int index = find(subject);

	// Checks whether the item was found.
	if (index >= 0) {
		const Item& item = table[index];
		// Prints the item's titles.
		for (std::list<std::string>::const_iterator it = item.data.begin(); it != item.data.end(); it++)
			std::cout << *it << " ";
	}
	else
		std::cout << "ERROR" << std::endl;
}

void HSubject::addSubjectAndTitle(const std::string& subject, const std::string& title) {
	int index = find(subject);
	if (index >= 0)
		// If the subject is already in the table, pushes the title.
		table[index].data.push_front(title);
	else {
		// If the subject wasn't in the list, adds a new item with the subject and the title.
		std::list<std::string> lst;
		lst.push_back(title);
		insert(Item(subject, lst));
	}
}

void HSubject::printFirstN(const std::string& subject, size_t N) const {
	int index = find(subject);

	// Checks whether the item was found.
	if (index >= 0) {
		const Item& item = table[index];
		N = fmin(N, item.data.size());

		// Prints first N titles.
		std::list<std::string>::const_iterator it = item.data.begin();
		for (size_t i = 0; i < N; i++) {
			std::cout << *(it++) << ' ';
		}
	}
	else
		std::cout << "ERROR" << std::endl;
}

void HSubject::print(std::ostream& os) const {
	// Loops on every subject.
	for (std::vector<Item>::const_iterator it = table.begin(); it != table.end(); it++) {
		// Checks that the item is valid.
		if (getItemValidation(*it)) {
			os << it->key << ':';
			// Prints the subject's titles.
			for (std::list<std::string>::const_iterator it2 = it->data.begin(); it2 != it->data.end(); it++)
				os << *it2 << " ";
			os << std::endl;
		}
	}
}

size_t HSubject::h1(const std::string& subject) const {
	return stringToNum(subject) % table.size();
}

size_t HSubject::h2(const std::string& subject) const {
	return (1 + stringToNum(subject) % (table.size() * 2 / 3));
}

size_t HSubject::stringToNum(const std::string& str, size_t chars) {
	size_t range = fmin(chars, str.size());
	size_t val = 0;
	for (size_t i = 0; i < range; i++) {
		// Convert the char from base 128 into base 10.
		val += pow(128, i) * str[i];
	}
	return val;
}

std::ostream& operator<<(std::ostream& os, const HSubject& hs) {
	hs.print(os);
	return os; 
}
