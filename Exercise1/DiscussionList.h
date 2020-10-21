#pragma once
#include <list>
#include <string>
#include "DiscussionTree.h"

using namespace std;

class DiscussionList {
public:
	DiscussionList() = default;																	// 3.1
	~DiscussionList() = default;																// 3.2

	void addDiscussion(const string& content);													// 3.3
	void deleteDiscussion(DiscussionTree::Node* root);											// 3.4
	bool printResponsesAndPathes(const string& content) const;									// 3.5
	void printFromResponse(const string& discussion, const string& content) const;				// 3.?
	bool addResponse(const string& discussion, const string& response, const string& content);	// 3.6
	bool deleteResponse(const string& discussion, const string& content);						// 3.7
	void printDiscussion(const string& discussion) const;										// 3.8
	void printResponse(const string& discussion, const string& content) const;					// 3.9

	friend ostream& operator<<(ostream& os, const DiscussionList& dl);
private:
	list<DiscussionTree> discussions;
};

