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

	// iterates the string, builds a new node if it doesn't exist.
	for (; it != str.end(); ++it) {
		if (!current->children[TRIE_INDEX(*it)]) {
			current->children[TRIE_INDEX(*it)] = new TrieNode(current);
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

	// checks for children.
	// if found, unset end word.
	for (size_t i = 0; i < ALPHABET_COUNT; i++) {
		if (end->children[i]) {
			end->isEndNode = false;
			return true;
		}
	}

	// removes the nodes recoursively.
	rec_remove(end);
	return true;
}

void Trie::rec_remove(TrieNode* current) {
	// first breaking condition, when got to the root.
	if (current == root) return;

	// second breaking condition, if it has children.
	for (size_t i = 0; i < ALPHABET_COUNT; i++) {
		if (current->children[i]) {
			return;
		}
	}

	// save the parent and delete the current node.
	TrieNode* parent = current->parent;
	delete current;

	// recoursive call to delete the parent.
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

	// creates the string to build and print all auto-complete subjects recoursively.
	std::string s = str;
	rec_print(end, s);

	return true;
}

void Trie::rec_print(TrieNode* current, std::string& str) const {
	if (current->isEndNode) {
		std::cout << str << '\n';
	}

	// finds the next node and builds the string according to the character.
	for (size_t i = 0; i < ALPHABET_COUNT; i++) {
		if (current->children[i]) {
			str += TRIE_CHAR(i);
			rec_print(current->children[i], str);
		}
	}

	// erases the last character.
	str.erase(str.size() - 1, 1);
}

Trie::TrieNode* Trie::find(const std::string& str) const {
	if (!root) return NULL;

	TrieNode* current = root;
	std::string::const_iterator it = str.begin();

	// checks if the path of the word exists in the trie.
	for (; it != str.end(); ++it) {
		if (!current->children[TRIE_INDEX(*it)]) {
			return NULL;
		}

		current = current->children[TRIE_INDEX(*it)];
	}

	return current;
}

Trie::TrieNode::TrieNode() : parent(NULL), children(), isEndNode(false) {
}

Trie::TrieNode::TrieNode(TrieNode* parent) : parent(parent), children(), isEndNode(false) {
}

Trie::TrieNode::~TrieNode() {
	// deletes recoursively all children.
	for (size_t i = 0; i < ALPHABET_COUNT; i++) {
		delete children[i];
	}

	if (!parent) return;

	// remove the child from parent's children.
	for (size_t i = 0; i < ALPHABET_COUNT; i++) {
		if (parent->children[i] == this) {
			parent->children[i] = NULL;
			break;
		}
	}
}
