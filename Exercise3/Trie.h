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

	TrieNode* find(const std::string& str) const;
	void rec_remove(TrieNode* current);
	void rec_print(TrieNode* current, std::string& str) const;
};

