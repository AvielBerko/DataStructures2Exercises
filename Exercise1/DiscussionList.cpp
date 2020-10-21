// dt is used for "discussion tree"

#include "DiscussionList.h"

// adds a new discussion tree (3.3)
void DiscussionList::addDiscussion(const string& content) {
	DiscussionTree dt; // bulids an empty dt
	dt.setRoot(content); // sets the dt's root
	discussions.push_back(dt); // moves dt to discussions list

	//discussions.push_back(move(dt)); // moves dt to discussions list
}

// deletes a discussion tree (3.4)
void DiscussionList::deleteDiscussion(DiscussionTree::Node* root) {
	for (list<DiscussionTree>::iterator it = discussions.begin(); it != discussions.end(); ++it) {
		if (it->getRoot() == root) { // if the root was found
			discussions.erase(it); // erase the root
			break;
		}
	}
}

// prints all Responses and pathes of a node (3.5)
bool DiscussionList::printResponsesAndPathes(const string& content) const {
	bool found = false;
	for (list<DiscussionTree>::const_reverse_iterator it = discussions.rbegin(); it != discussions.rend(); ++it) { // foreach dt in discussions list
		if (it->printResponseTree(content)) { // if the subtree was printed
			it->printPathToResponse(content); // print the paths
			found = true;
		}
	}

	return found;
}

// prints the response subtree (3.?)
void DiscussionList::printResponseTree(const string& discussion, const string& content) const {
	for (list<DiscussionTree>::const_iterator it = discussions.cbegin(); it != discussions.cend(); ++it) { // foreach dt in discussions list
		if (it->getRoot()->content == discussion) { // if the dt was found
			it->printResponseTree(content); // print the subtree of content
			if (it->_findFather(it->root, content))
				cout << "=>" << it->_findFather(it->root, content)->content << endl;
			break;
		}
	}
}

// adds a response to an existing discussion (3.6)
bool DiscussionList::addResponse(const string& discussion, const string& response, const string& content) {
	for (list<DiscussionTree>::iterator it = discussions.begin(); it != discussions.end(); ++it) { // foreach dt in discussions list
		if (it->getRoot()->content == discussion) { // if the dt was found
			return it->addResponse(response, content); // adds the response
		}
	}

	return false;
}

// deletes a response from an existing discussion (3.7)
bool DiscussionList::deleteResponse(const string& discussion, const string& content) {
	for (list<DiscussionTree>::iterator it = discussions.begin(); it != discussions.end(); ++it) { // foreach dt in discussions list
		if (it->getRoot()->content == discussion) { // if the dt was found
			return it->deleteResponse(content); // deletes the response
		}
	}

	return false;
}

// prints a hole discussion tree (3.8)
void DiscussionList::printDiscussion(const string& discussion) const {
	for (list<DiscussionTree>::const_iterator it = discussions.cbegin(); it != discussions.cend(); ++it) { // foreach dt in discussions list
		if (it->getRoot()->content == discussion) { // if the dt was found
			cout << *it; // prints the dt
			break;
		}
	}
}

// prints the path and subtree of a given response (3.9)
void DiscussionList::printResponse(const string& discussion, const string& content) const {
	for (list<DiscussionTree>::const_iterator it = discussions.cbegin(); it != discussions.cend(); ++it) { // foreach dt in discussions list
		if (it->getRoot()->content == discussion) { // if the dt was found
			it->printToFromResponse(content); // print the path and subtree of the response
			break;
		}
	}
}

// operator << to print all discussion trees list
ostream& operator<<(ostream& os, const DiscussionList& dl) {
	size_t counter = 1;
	for (list<DiscussionTree>::const_reverse_iterator it = dl.discussions.rbegin(); it != dl.discussions.rend(); ++it) { // foreach dt in discussions list
		os << "Tree #" << counter++ << '\n';
		os << *it; // prints the dt
	}

	return os;
}