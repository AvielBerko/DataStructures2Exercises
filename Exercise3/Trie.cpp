#include "Trie.h"

#define TRIE_INDEX(x) x - 97
#define TRIE_CHAR(x) x + 97

Trie::Trie() : root(NULL) {
}

Trie::~Trie() {
	delete root;
}

void Trie::insert(const std::string& str) {
	if (!root) root = new TrieNode;

	TrieNode* current = root;
	std::string::const_iterator it = str.begin();
	for (; it != str.end(); ++it) {
		if (!current->children[TRIE_INDEX(*it)]) {
			current->children[TRIE_INDEX(*it)] = new TrieNode{ current };
		}

		current = current->children[TRIE_INDEX(*it)];
	}

	current->isEndNode = true;
}

bool Trie::remove(const std::string& str) {
	TrieNode* end = find(str);

	if (!end || !end->isEndNode) {
		return false;
	}

	for (size_t i = 0; i < ALPHABET_COUNT; i++) {
		if (end->children[i]) {
			end->isEndNode = false;
			return true;
		}
	}

	rec_remove(end);
	return true;
}

void Trie::rec_remove(TrieNode* current) {
	if (current == root) return;

	for (size_t i = 0; i < ALPHABET_COUNT; i++) {
		if (current->children[i]) {
			return;
		}
	}

	TrieNode* parent = current->parent;
	delete current;

	rec_remove(parent);
}

bool Trie::search(const std::string& str) const {
	TrieNode* end = find(str);

	if (!end) return false;
	return end->isEndNode;
}

bool Trie::printAutoComplete(const std::string& str) const {
	TrieNode* end = find(str);

	if (!end) return false;

	std::string s = str;
	rec_print(end, s);

	return true;
}

void Trie::rec_print(TrieNode* current, std::string& str) const {
	if (current->isEndNode) {
		std::cout << str << '\n';
	}

	for (size_t i = 0; i < ALPHABET_COUNT; i++) {
		if (current->children[i]) {
			str += TRIE_CHAR(i);
			rec_print(current->children[i], str);
		}
	}

	str.erase(str.size() - 1, 1);
}

Trie::TrieNode* Trie::find(const std::string& str) const {
	if (!root) return NULL;

	TrieNode* current = root;
	std::string::const_iterator it = str.begin();
	for (; it != str.end(); ++it) {
		if (!current->children[TRIE_INDEX(*it)]) {
			return NULL;
		}

		current = current->children[TRIE_INDEX(*it)];
	}

	return current;
}

Trie::TrieNode::~TrieNode() {
	for (size_t i = 0; i < ALPHABET_COUNT; i++) {
		delete children[i];
	}

	if (!parent) return;

	for (size_t i = 0; i < ALPHABET_COUNT; i++) {
		if (parent->children[i] == this) {
			parent->children[i] = NULL;
			break;
		}
	}
}
