#include "DiscussionTree.h"

#define INDENTATION "   "

DiscussionTree::~DiscussionTree() {
	delete root;
}

void DiscussionTree::setRoot(const string& content) {
	delete root;

	root = new Node(content);
}

DiscussionTree::Node* DiscussionTree::find(const string& content) const {
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

void DiscussionTree::insert(const string& father, const string& content) {
	auto fatherNode = find(father);
	if (fatherNode) {
		fatherNode->responses.push_back(Node(content));
	}
}

void DiscussionTree::deleteResponse(const string& content) {
	if (root->content == content) delete root;
	else {
		auto father = _findFather(root, content);
		if (father) {
			auto begin = father->responses.begin();
			auto end = father->responses.end();
			std::remove_if(begin, end, [&content](const Node& node) { return node.content == content; });
		}
	}
}

void DiscussionTree::printToResponse(const string& content) const {
	auto lst = _findPath(root, content);
	size_t indentations = 0;
	for (auto node : lst) {
		for (size_t i = 0; i < indentations; i++) {
			cout << INDENTATION;
		}

		cout << node->content << endl;
		indentations++;
	}
}

void DiscussionTree::printFromResponse(const string& content) const {
	auto node = find(content);
	if (node) {
		_printNode(*node);
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
