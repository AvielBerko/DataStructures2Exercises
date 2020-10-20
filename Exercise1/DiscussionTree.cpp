#include "DiscussionTree.h"

//using Node = DiscussionTree::Node;
//typedef DiscussionTree::Node Node;

DiscussionTree::DiscussionTree() : root(nullptr) { }

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
	for (auto node : father->responses) {
		if (node.content == content) {
			return &node;
		}
	}
}

void DiscussionTree::insert(const string& father, const string& content) {
	auto fatherNode = find(father);
	if (fatherNode) {
		fatherNode->responses.push_back(Node(content));
	}
}

void DiscussionTree::deleteSubTree(const string& content) {
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

void DiscussionTree::printToSubTree(const string& content) const {

}

void DiscussionTree::printFromSubTree(const string& content) const
{
}

DiscussionTree::Node* DiscussionTree::_findFather(Node* father, const string& content) const
{
	if (father) {
		for (auto node : father->responses) {
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

ostream& operator<<(ostream& os, const DiscussionTree& dt)
{
	// TODO: insert return statement here
}
