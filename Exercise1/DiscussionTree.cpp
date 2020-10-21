#include "DiscussionTree.h"

#define INDENTATION "   "

// copy ctor
DiscussionTree::DiscussionTree(const DiscussionTree& copy) : root(nullptr) {
	setRoot(copy.root->content); // sets the root
	root->responses = copy.root->responses; // copys the responses
}

//dtor
DiscussionTree::~DiscussionTree() { 
	delete root; // deletes root's pointer
}

void DiscussionTree::setRoot(const string& content) {
	delete root; // deletes root's pointer

	root = new Node(content); // sets a new root
}

DiscussionTree::Node* DiscussionTree::getRoot() const {
	return root;
}

DiscussionTree::Node* DiscussionTree::_find(const string& content) const {
	if (root->content == content) return root;

	auto father = _findFather(root, content);
	if (father) {
		for (auto& node : father->responses) {
			if (node.content == content) {
				return &node;
			}
		}
	}
}

bool DiscussionTree::addResponse(const string& father, const string& content) {
	auto fatherNode = _find(father);
	if (fatherNode) {
		fatherNode->responses.push_back(Node(content));
		return true;
	}

	return false;
}

bool DiscussionTree::deleteResponse(const string& content) {
	if (root->content == content) {
		delete root;
		return true;
	}

	auto father = _findFather(root, content);
	if (father) {
		auto it = father->responses.begin();
		auto end = father->responses.end();
		for (; it != end; ++it) {
			if (it->content == content) {
				father->responses.erase(it);
				return true;
			}
		}
	}

	return false;
}

void DiscussionTree::printPathToResponse(const string& content) const {
	auto path = _findPath(root, content);
	if (!path.empty()) {
		for (auto it = ++path.rbegin(); it != path.rend(); ++it) {
			cout << "=>" << (*it)->content;
		}

		cout << endl;
	}
}

bool DiscussionTree::printFromResponse(const string& content) const {
	auto node = _find(content);
	if (node) {
		_printNode(*node);
	}
	
	return node;
}

void DiscussionTree::printToFromResponse(const string& content) const {
	auto path = _findPath(root, content);
	if (!path.empty()) {
		size_t indentations = 0;
		auto end = --path.end();

		for (auto it = path.begin(); it != end; ++it) {
			for (size_t i = 0; i < indentations; i++) {
				cout << INDENTATION;
			}

			cout << (*it)->content << endl;
			indentations++;
		}

		auto node = *path.rbegin();
		_printNode(*node, cout, indentations);
	}
}

DiscussionTree::Node* DiscussionTree::_findFather(Node* father, const string& content) const {
	if (father) {
		for (auto& node : father->responses) {
			if (node.content == content) {
				return father;
			}
			else {
				auto result = _findFather(&node, content);

				if (result) {
					return result;
				}
			}
		}
	}

	return nullptr;
}

list<DiscussionTree::Node*> DiscussionTree::_findPath(Node* father, const string& content) const {
	list<Node*> lst;
	if (father) {
		if (father->content == content) {
			lst.push_back(father);
		}
		else {
			for (auto& child : father->responses) {
				auto childLst = _findPath(&child, content);
				if (!childLst.empty()) {
					lst.push_back(father);
					lst.splice(lst.end(), childLst);
					break;
				}
			}
		}
	}
	return lst;
}

void DiscussionTree::_printNode(const Node& node, ostream& os, size_t indentations) const {
	for (size_t i = 0; i < indentations; i++) {
		os << INDENTATION;
	}

	os << node.content << endl;

	for (const auto& child : node.responses) {
		_printNode(child, os, indentations + 1);
	}
}

ostream& operator<<(ostream& os, const DiscussionTree& dt) {
	if (dt.root) {
		dt._printNode(*dt.root, os);
	}
	return os;
}
