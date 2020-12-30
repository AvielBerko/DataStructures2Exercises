// Names: Aviel Berkovich (211981105), Meir Klemfner(211954185)
// Data Structures 2
// Exercise 4
// The main program has no comments beacuse it was copied from the moodle

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "huffman.h"

int main() {
	int choice;
	std::cout << "enter 1 to encode a text\n";
	std::cout << "enter 2 to decode a text\n";
	std::cout << "enter 3 to exit\n";

	do
	{
		std::cin >> choice;
		switch (choice) {
		case 1: {
			std::cout << "enter the original text\n";
			std::string text;
			std::cin >> text;

			HuffmanTree tree(text);
			std::vector<char> vec = tree.get_chars();

			std::cout << "the encoded string is: ";
			// prints n
			std::cout << vec.size() << '\n';

			// prints the letters by order
			std::vector<char>::iterator it = vec.begin();
			for (; it != vec.end(); ++it) {
				std::cout << *it;
			}

			// prints the tree's structure
			std::cout << '\n' << tree.to_string() << '\n';

			// prints the encoded text
			std::map<char, std::string> mp = tree.get_chars_to_code();
			std::string::iterator it_txt = text.begin();
			for (; it_txt != text.end(); ++it_txt) {
				std::cout << mp[*it_txt];
			}
			std::cout << '\n';

			break;
		}
		case 2: {
			size_t n;
			std::cout << "enter n ";
			std::cin >> n;

			std::string chars;
			std::cout << "enter the letters ";
			std::cin >> chars;

			std::string tree_str;
			std::cout << "enter the encoded structure ";
			std::cin >> tree_str;

			std::string encoded;
			std::cout << "enter the encoded text ";
			std::cin >> encoded;

			HuffmanTree tree(tree_str, chars);

			std::map<std::string, char> vec = tree.get_code_to_chars();
			std::string builder;

			std::cout << "The decoded string is: ";

			// iterates over the encoded text and tries to find 
			// the letters by adding the binary to the builder
			std::string::iterator it_txt = encoded.begin();
			for (; it_txt != encoded.end(); ++it_txt) {
				builder += *it_txt;
				if (vec[builder]) {
					std::cout << vec[builder];
					builder.clear();
				}
			}
			std::cout << '\n';

		}
		}
	} while (choice != 3);

	return 0;
}
