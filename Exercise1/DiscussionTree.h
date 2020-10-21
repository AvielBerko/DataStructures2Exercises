#pragma once
#include <list>
#include <string>
#include <iostream>

using namespace std;

class DiscussionList;
class DiscussionTree {
public:
	struct Node {
		string content; 
		list<Node> responses;
		Node(const string& content) : content(content) {}				// ctor
	};
	
	DiscussionTree() : root (NULL) {}									// default ctor (2.1)
	DiscussionTree(const DiscussionTree& copy);							// copy ctor
	//DiscussionTree(DiscussionTree&& move);							// move ctor
	~DiscussionTree();													// dtor (2.2)

	void setRoot(const string& content);								// root setter (2.3)
	Node* getRoot() const;												// root getter
	bool addResponse(const string& father, const string& content);		// adds a response to an existing response (2.5)
	bool deleteResponse(const string& content);							// deletes an existing response (2.6)
	void printPathToResponse(const string& content) const;				// prints the path from root to response (2.8)
	bool printResponseTree(const string& content) const;				// prints the response's subtree (2.9)
	void printToFromResponse(const string& content) const;				// prints from root to response and forward

	friend ostream& operator<<(ostream& os, const DiscussionTree& dt);	// operator << - to print a complete tree (2.7)
	friend class DiscussionList;
private:
	Node* _find(const string& content) const;							// finds a node with given content (2.4)
	Node* _findFather(Node* father, const string& content) const;		// finds a node's father
	list<Node*> _findPath(Node* father, const string& content) const;	// finds a node's path
	void _printNode(const Node& node, ostream& os = cout, size_t indentations = 0) const; // prints a node and it's responses
	Node* root;
};

