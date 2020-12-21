#pragma once
#include <iostream>
#include <string>

#define ALPHABET_COUNT 26

class Trie {
public:
	Trie();
	~Trie();

	void insert(const std::string& str);
	bool remove(const std::string& str);
	bool search(const std::string& str) const;
	bool printAutoComplete(const std::string& str) const;

private:

	struct TrieNode {
		TrieNode* parent;
		TrieNode* children[ALPHABET_COUNT];
		bool isEndNode;

		TrieNode();
		TrieNode(TrieNode* parent);
		~TrieNode();
	} * root;

	// finds the TrieNode for the end of the string.
	// if not found returns null.
	TrieNode* find(const std::string& str) const;
	// removes the TrieNode and its parents from the trie
	// until found another path recursively.
	void rec_remove(TrieNode* current);
	// builds a string to print recursively.
	// when got to the end prints the string.
	// when returns, it erases the string.
	void rec_print(TrieNode* current, std::string& str) const;
};

