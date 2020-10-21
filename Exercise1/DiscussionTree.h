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

	DiscussionTree() = default;
	~DiscussionTree();

	void setRoot(const string& content);
	Node* find(const string& content) const;
	void insert(const string& father, const string& content);
	void deleteResponse(const string& content);
	void printToResponse(const string& content) const;
	void printFromResponse(const string& content) const;

	friend ostream& operator<<(ostream& os, const DiscussionTree& dt);

private:
	Node* _findFather(Node* father, const string& content) const;
	list<Node*> _findPath(Node* father, const string& content) const;
	void _printNode(const Node& node, ostream& os = cout, size_t indentations = 0) const;
	Node* root;
};

