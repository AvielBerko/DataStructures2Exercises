// Names: Aviel Berkovich (211981105), Meir Klemfner(211954185)
// Data Structures 2
// Exercise 1

#include <iostream>
#include <list>
#include <string>
#include "DiscussionList.h"

using namespace std;

//int main() {
//	DiscussionTree dt;
//	dt.setRoot("test");
//	dt.addResponse("test", "test 2");
//	dt.addResponse("test 2", "test 3");
//	dt.addResponse("test 2", "test 5");
//	dt.addResponse("test 3", "test 4");
//	dt.addResponse("test", "test 0");
//	dt.addResponse("test 0", "test -1");
//	//dt.printToResponse("test 4");
//	//dt.printFromResponse("test 1");
//	dt.printResponse("test 2");
//	//cout << dt;
//}

int main() {
	DiscussionList dl;
	string title, father, val, son;
	char ch;

	cout << "\nDISCUSSION TREE\n";
	cout << "Choose one of the following (Upper case letters allowed):" << endl;
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
			dl.printFromResponse(title, val);
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
