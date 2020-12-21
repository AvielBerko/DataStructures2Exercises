#include<iostream>
#include <list>
#include <string>
#include "Trie.h"

int main() {
	char ch;
	std::string wrd;
	Trie tr;
	int comp;

	std::cout << "TRIE PROGRAM\n\n";
	std::cout << "Choose one of the following\n";
	std::cout << "1: add a new item\n";
	std::cout << "2: delete an item\n";
	std::cout << "3: check if an item exists\n";
	std::cout << "4: complete the possible item name\n";
	std::cout << "5: exit\n";

	do
	{
		std::cin >> ch;

		switch (ch)
		{
		case '1':
			std::cout << "Enter a word to insert\n";
			std::cin >> wrd;
			tr.insert(wrd);
			break;
		case '2':
			std::cout << "Enter a word to del\n";
			std::cin >> wrd;
			if (!tr.remove(wrd)) std::cout << "ERROR\n";
			break;
		case '3':
			std::cout << "Enter a word to search\n";
			std::cin >> wrd;
			if (tr.search(wrd))
				std::cout << "exists\n";
			else
				std::cout << "does not exist\n";
			break;

		case '4':
			std::cout << "Enter a prefix to complete\n";
			std::cin >> wrd;

			if (!tr.printAutoComplete(wrd))
				std::cout << "No string exist with this prefix\n";
			break;
		case '5':std::cout << "bye\n"; break;
		default: std::cout << "ERROR\n";  break;
		}//switch
	} while (ch != '5');
	return 0;
}
