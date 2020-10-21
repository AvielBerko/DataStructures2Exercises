#pragma once
#include <list>
#include <string>
#include "DiscussionTree.h"

using namespace std;

class DiscussionList {
public:
	//DiscussionList() = default;																// defualt ctor (3.1)
	//~DiscussionList() = default;																// dtor (3.2)


	void addDiscussion(const string& content);													// adds a new discussion tree (3.3)
	void deleteDiscussion(DiscussionTree::Node* root);											// deletes a discussion tree (3.4)
	bool printResponsesAndPathes(const string& content) const;									// prints all Responses and pathes of a node (3.5)
	void printResponseTree(const string& discussion, const string& content) const;				// prints the response subtree (3.?)
	bool addResponse(const string& discussion, const string& response, const string& content);	// adds a response to an existing discussion (3.6)
	bool deleteResponse(const string& discussion, const string& content);						// deletes a response from an existing discussion (3.7)
	void printDiscussion(const string& discussion) const;										// prints a hole discussion tree (3.8)
	void printResponse(const string& discussion, const string& content) const;					// prints the path and subtree of a given response (3.9)

	friend ostream& operator<<(ostream& os, const DiscussionList& dl);							// operator << to print all discussion trees list

private:
	list<DiscussionTree> discussions;
};

