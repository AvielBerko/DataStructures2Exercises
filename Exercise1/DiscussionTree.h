#pragma once
#include <list>
#include <string>
#include <iostream>

using namespace std;

class DiscussionTree {
public:
	struct Node {
		string content;
		list<Node> responses;
		Node(const string& content) : content(content) {}
	};

	DiscussionTree() = default;											// 2.1
	DiscussionTree(const DiscussionTree& copy);
	~DiscussionTree();													// 2.2

	void setRoot(const string& content);								// 2.3
	Node* getRoot() const;
	bool addResponse(const string& father, const string& content);		// 2.5
	bool deleteResponse(const string& content);							// 2.6
	void printPathToResponse(const string& content) const;				// 2.8
	bool printFromResponse(const string& content) const;				// 2.9
	void printToFromResponse(const string& content) const;

	friend ostream& operator<<(ostream& os, const DiscussionTree& dt);	// 2.7

private:
	Node* _find(const string& content) const;							// 2.4
	Node* _findFather(Node* father, const string& content) const;
	list<Node*> _findPath(Node* father, const string& content) const;
	void _printNode(const Node& node, ostream& os = cout, size_t indentations = 0) const;
	Node* root;
};

