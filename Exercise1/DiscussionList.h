#pragma once
#include <list>
#include <string>
#include "DiscussionTree.h"

using namespace std;

class DiscussionList {
public:
	DiscussionList() = default;
	~DiscussionList() = default;

	void newDiscussion(const string& content);
	void deleteDiscussion(DiscussionTree::Node* root);
private:
	list<DiscussionTree> discussions;
};

