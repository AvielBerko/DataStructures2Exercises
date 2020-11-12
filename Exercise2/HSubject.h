#pragma once
#include "HashTable.h"
#include<list>
class HSubject : public HashTable<std::string, std::list<std::string>> {
public:
	HSubject(size_t size) : HashTable(size) { }
	void initTable();
	void printSubject(const std::string& subject) const;
	void addSubjectAndTitle(const std::string& subject, const std::string& title);
	void printFirstN(const std::string& subject, size_t N) const;
	void print(std::ostream & = std::cout) const override;

private:
	size_t h1(const std::string& key) const override;
	size_t h2(const std::string& key) const override;
	static size_t stringToNum(const std::string& str);
};


