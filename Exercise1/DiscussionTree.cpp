#include "DiscussionTree.h"

#define INDENTATION "   "

// copy ctor
DiscussionTree::DiscussionTree(const DiscussionTree& copy) : root(NULL) {
	setRoot(copy.root->content); // sets the root
	root->responses = copy.root->responses; // copys the responses
}

/*// move ctor
DiscussionTree::DiscussionTree(DiscussionTree&& move) : root(move.root) {
	move.root = NULL;
}*/

// dtor
DiscussionTree::~DiscussionTree() { 
	delete root; // deletes root's pointer
}

// root setter
void DiscussionTree::setRoot(const string& content) {
	delete root; // deletes root's pointer

	root = new Node(content); // sets a new root
}

// root getter 
DiscussionTree::Node* DiscussionTree::getRoot() const {
	return root;
}

// adds a response to an existing response (2.5)
bool DiscussionTree::addResponse(const string& father, const string& content) {
	Node* fatherNode = _find(father); // finds the father's node
	if (fatherNode) {
		fatherNode->responses.push_back(Node(content)); // pushes the content to father's list of responses
		return true;
	}

	return false;
}

// deletes an existing response (2.6)
bool DiscussionTree::deleteResponse(const string& content) {
	if (root->content == content) { // found
		delete root; // deletes root's pointer
		return true;
	}

	Node* father = _findFather(root, content); // finds node's father node
	if (father) {
		list<Node>::iterator it = father->responses.begin();
		list<Node>::iterator end = father->responses.end();
		for (; it != end; ++it) {
			if (it->content == content) { 
				// finds the node and deletes it
				father->responses.erase(it);
				return true;
			}
		}
	}

	return false;
}

// prints the path from root to response (2.8)
void DiscussionTree::printPathToResponse(const string& content) const {
	list<Node*> path = _findPath(root, content); // finds the path to content's node
	if (!path.empty()) {
		for (list<Node*>::reverse_iterator it = ++path.rbegin(); it != path.rend(); ++it) {
			cout << "=>" << (*it)->content; // prints the path (using iterators)
		}

		cout << endl;
	}
}

// prints the response's subtree (2.9)
bool DiscussionTree::printResponseTree(const string& content) const {
	Node* node = _find(content); // finds content's node
	if (node) {
		_printNode(*node); // prints the node and it's subtree
	}
	
	return node;
}

// prints from root to response and forward
void DiscussionTree::printToFromResponse(const string& content) const {
	list<Node*> path = _findPath(root, content); // finds the path to content's node
	if (!path.empty()) {
		size_t indentations = 0; // number of indentations for each response
		list<Node*>::iterator end = --path.end(); // exclucing the node itself

		for (list<Node*>::iterator it = path.begin(); it != end; ++it) {
			for (size_t i = 0; i < indentations; i++) {
				cout << INDENTATION; // prints all indentations
			}

			cout << (*it)->content << endl; // prints the response
			indentations++;
		}

		Node* node = *path.rbegin(); // node = content's node
		_printNode(*node, cout, indentations); // prints the node and it's subtree
	}
}

// operator << - to print a complete tree (2.7)
ostream& operator<<(ostream& os, const DiscussionTree& dt) {
	if (dt.root) {
		dt._printNode(*dt.root, os); // prints root and it's subtree (the hole tree)
	}
	return os;
}


// finds a node with given content (2.4)
DiscussionTree::Node* DiscussionTree::_find(const string& content) const {
	if (root->content == content) return root; // checks the root node

	Node* father = _findFather(root, content); // finds node's father node
	if (father) {
		for (Node& node : father->responses) { // foreach node in responses list
			if (node.content == content) { // if found
				return &node;
			}
		}
	}
}

// finds a node's father
DiscussionTree::Node* DiscussionTree::_findFather(Node* father, const string& content) const {
	if (father) {
		for (Node& node : father->responses) { // foreach node in father's responses list
			if (node.content == content) { // if found
				return father;
			}
			else {
				Node* result = _findFather(&node, content); // recursive call

				if (result) {
					return result; // returns the found father
				}
			}
		}
	}

	return NULL;
}

// finds a node's path
list<DiscussionTree::Node*> DiscussionTree::_findPath(Node* father, const string& content) const {
	list<Node*> lst; // list of nodes in the path
	if (father) {
		if (father->content == content) { // if found
			lst.push_back(father); // pushes the node to the list
		}
		else {
			for (Node& child : father->responses) { // foreach node in father's responses list
				list<Node*> childLst = _findPath(&child, content); // recursive call
				if (!childLst.empty()) { // if the child node was found
					lst.push_back(father); // pushes the father to the list 
					lst.splice(lst.end(), childLst); // merges the 2 lists to lst
					break;
				}
			}
		}
	}
	return lst; // returns the path as list of nodes
}

// prints a node and it's responses
void DiscussionTree::_printNode(const Node& node, ostream& os, size_t indentations) const {
	for (size_t i = 0; i < indentations; i++) {
		os << INDENTATION; // prints all indentations
	}

	os << node.content << endl; // prints the node's content

	for (const Node& child : node.responses) { // foreach node in node's responses list
		_printNode(child, os, indentations + 1); //recursive print the subtree
	}
}
