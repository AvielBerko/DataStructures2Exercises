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

	DiscussionTree();
	~DiscussionTree();

	void setRoot(const string& content);
	Node* find(const string& content) const;
	void insert(const string& father, const string& content);
	void deleteSubTree(const string& content);
	void printToSubTree(const string& content) const;
	void printFromSubTree(const string& content) const;

	friend ostream& operator<<(ostream& os, const DiscussionTree& dt);

private:
	Node* _findFather(Node* father, const string& content) const;
	list<const Node&> _findPath(const string& content);
	Node* root;
};

