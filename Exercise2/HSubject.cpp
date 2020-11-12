#include "HSubject.h"

void HSubject::initTable() {
	//std::for_each(table.begin(), table.end(), [](Item& item) ); });
	for (std::vector<Item>::iterator it = table.begin(); it != table.end(); it++)
		setItemValidation(*it, false);
}

void HSubject::printSubject(const std::string& subject) const {
	int index = find(subject);
	if (index >= 0) {
		const Item& item = table[index];
		//std::for_each(item.data.begin(), item.data.end(), [](const std::string& title) { std::cout << title << " "; });
		for (std::list<std::string>::const_iterator it = item.data.begin(); it != item.data.end(); it++)
			std::cout << *it << " ";
	}
	else
		std::cout << "ERROR" << std::endl;
}

void HSubject::addSubjectAndTitle(const std::string& subject, const std::string& title) {
	int index = find(subject);
	if (index >= 0)
		table[index].data.push_front(title);
	else {
		std::list<std::string> lst;
		lst.push_back(title);
		insert(Item(subject, lst));
	}
}

void HSubject::printFirstN(const std::string& subject, size_t N) const {
	int index = find(subject);
	if (index >= 0) {
		const Item& item = table[index];
		N = std::min(N, item.data.size());
		std::list<std::string>::const_iterator it = item.data.begin();
		for (size_t i = 0; i < N; i++) {
			std::cout << *(it++) << ' ';
		}
	}
	else
		std::cout << "ERROR" << std::endl;
}

void HSubject::print(std::ostream& os) const {
	for (std::vector<Item>::const_iterator it = table.begin(); it != table.end(); it++) {
		os << it->key << ':';
		//std::for_each(it->data.begin(), it->data.end(), [&](const std::string& title) { os << title << " "; });
		for (std::list<std::string>::const_iterator it2 = it->data.begin(); it2 != it->data.end(); it++)
			os << *it2 << " ";
		os << std::endl;
	}
}

size_t HSubject::h1(const std::string& subject) const {
	return stringToNum(subject) % table.size();
}

size_t HSubject::h2(const std::string& subject) const {
	return (1 + stringToNum(subject) % 7);
}

std::ostream& operator<<(std::ostream& os, const HSubject& hs) {
	hs.print(os);
	return os; 
}

size_t HSubject::stringToNum(const std::string& str) {
	size_t range = std::min(3u, str.size());
	size_t val = 0;
	for (size_t i = 0; i < range; i++) {
		val += std::pow(128, i) * str[i];
	}
	return val;
}