#include "DiscussionList.h"

void DiscussionList::addDiscussion(const string& content) {
	DiscussionTree dt;
	dt.setRoot(content);
	discussions.push_back(dt);
}

void DiscussionList::deleteDiscussion(DiscussionTree::Node* root) {
	for (auto it = discussions.begin(); it != discussions.end(); ++it) {
		if (it->getRoot() == root) {
			discussions.erase(it);
			break;
		}
	}
}

bool DiscussionList::printResponsesAndPathes(const string& content) const {
	bool found = false;
	for (const auto& dt : discussions) {
		if (dt.printFromResponse(content)) {
			dt.printPathToResponse(content);
			found = true;
		}
	}

	return found;
}

void DiscussionList::printFromResponse(const string& discussion, const string& content) const {
	for (const auto& dt : discussions) {
		if (dt.getRoot()->content == discussion) {
			dt.printFromResponse(content);
			break;
		}
	}
}

bool DiscussionList::addResponse(const string& discussion, const string& response, const string& content) {
	for (auto& dt : discussions) {
		if (dt.getRoot()->content == discussion) {
			return dt.addResponse(response, content);
		}
	}

	return false;
}

bool DiscussionList::deleteResponse(const string& discussion, const string& content) {
	for (auto& dt : discussions) {
		if (dt.getRoot()->content == discussion) {
			return dt.deleteResponse(content);
		}
	}

	return false;
}

void DiscussionList::printDiscussion(const string& discussion) const {
	for (auto& dt : discussions) {
		if (dt.getRoot()->content == discussion) {
			cout << dt;
			break;
		}
	}
}

void DiscussionList::printResponse(const string& discussion, const string& content) const {
	for (const auto& dt : discussions) {
		if (dt.getRoot()->content == discussion) {
			dt.printToFromResponse(content);
			break;
		}
	}
}

ostream& operator<<(ostream& os, const DiscussionList& dl) {
	size_t counter = 1;
	for (const auto& dt : dl.discussions) {
		os << "Tree #" << counter++ << '\n';
		os << dt;
	}

	return os;
}
