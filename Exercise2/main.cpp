// Names: Aviel Berkovich (211981105), Meir Klemfner(211954185)
// Data Structures 2
// Exercise 2
// The main program has no comments beacuse it was copied from the moodle

#include <iostream>
#include "HSubject.h"
#pragma warning(disable: 4996)
using namespace std;

int main()
{
	char ch;
	int n;
	HSubject hs(1000);
	string subject, title;

	cout << "Hash Table\n";
	cout << "\nChoose one of the following" << endl;
	cout << "n: New hash table" << endl;
	cout << "a: Add a subject and a title" << endl;
	cout << "d: Del a subject " << endl;
	cout << "t: print all titles of the subject " << endl;
	cout << "s: print N first appearances of a subect " << endl;
	cout << "p: print all non-empty entries " << endl;
	cout << "e: Exit" << endl;
	do
	{
		cin >> ch;
		switch (ch)
		{

		case 'n':hs.initTable(); break;
		case 'a':cout << "Enter a subject and a title\n";
			cin >> subject >> title;
			hs.addSubjectAndTitle(subject, title);
			break;
		case 'd':cout << "Enter a subject to remove\n";
			cin >> subject;
			hs.remove(subject); break;
		case 't':cout << "enter subject to print\n";
			cin >> subject;
			hs.printSubject(subject); break;
		case 's':cout << "enter a subject and N\n"; cin >> subject >> n;
			hs.printFirstN(subject, n); break;
		case 'e':cout << "bye\n"; break;
		case 'p':cout << hs; break;
		default: cout << "ERROR\n";  break;
		}
	} while (ch != 'e');
	return 0;
}

