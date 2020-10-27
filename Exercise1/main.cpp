// Names: Aviel Berkovich (211981105), Meir Klemfner(211954185)
// Data Structures 2
// Exercise 1
// The main program has no comments beacuse it was copied from the moodle

#include <iostream>
#include <list>
#include <string>
#include "DiscussionList.h"

using namespace std;

int main() {
	DiscussionList dl;
	string title, father, val, son;
	char ch;

	cout << "DISCUSSION TREE\n";
	cout << "Choose one of the following:" << endl;
	cout << "n: New discussion tree" << endl;
	cout << "s: Add a new response" << endl;
	cout << "d: Delete a sub-discussion" << endl;
	cout << "p: Print all discussion trees" << endl;
	cout << "r: Print a sub-tree" << endl;
	cout << "w: Search a string in all discussion trees" << endl;
	cout << "e: exit:" << endl;

	do
	{
		cin >> ch;
		ch = tolower(ch);

		switch (ch)
		{
		case 'n':
			cout << "enter the discussion title (with no space) ";
			cin >> val;
			dl.addDiscussion(val);
			break;
		case 's':
			cout << "enter the discussion title (with no space) ";
			cin >> title;
			cout << "enter the last message (with no space) ";
			cin >> father;
			cout << "enter the new respond ";
			cin >> son;
			if (dl.addResponse(title, father, son))
				cout << "success\n";
			else cout << "ERROR\n";
			break;
		case 'd':
			cout << "enter the discussion title (with no space) ";
			cin >> title;
			cout << "enter string of subtree to delete (with no space) ";
			cin >> val;
			if (dl.deleteResponse(title, val))
				cout << "success\n";
			else cout << "ERROR\n";
			break;
		case 'p':
			cout << dl;
			break;
		case 'r':
			cout << "enter the discussion title (with no space) ";
			cin >> title;
			cout << "enter the last message (with no space) ";
			cin >> val;
			dl.printResponseTree(title, val);
			cout << endl;
			break;
		case 'w':
			cout << "enter a string (with no space) ";
			cin >> val;
			if (dl.printResponsesAndPathes(val))
				 cout << endl;
			else cout << "ERROR" << endl;
			break;
		case 'e':
			cout << "bye ";
			break;
		default:
			cout << "ERROR\n";
			break;
		}
	} while (ch != 'e');
}
