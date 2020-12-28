// Names: Aviel Berkovich (211981105), Meir Klemfner(211954185)
// Data Structures 2
// Exercise 4
// The main program has no comments beacuse it was copied from the moodle

#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <map>
#include <cmath>

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

			//HuffmanTree tree(text);
			//std::cout << tree.get_n() << '\n';
			//std::vector<char> chars = tree.get_chars();
			//for (char ch : chars) {
			//	std::cout << ch;
			//}
			//std::cout << '\n' << tree.to_string() << '\n';
			//for (char ch : text) {
			//	std::cout << tree.get_code(ch);
			//}
			//std::cout << '\n';

			HuffmanTree tree(text);
			std::map<char, std::string> mp = tree.get_chars_code();
			std::cout << mp.size() << '\n';

			std::map<char, std::string>::iterator it = mp.begin();
			for (; it != mp.end(); ++it) {
				std::cout << it->first;
			}

			std::cout << '\n' << tree.to_string() << '\n';

			for (char ch : text) {
				std::cout << mp[ch];
			}
			std::cout << '\n';

			//Build Huffman tree given the data inside "word".
			//Then find the code of each letter.
			//Then print the output - number of leaves, order of letters, tree structure and the encoded text - according to the explanation in the exercise.

			break;
		}
		case 2: {
			size_t n;
			std::cout << "";
			std::cin >> n;

			std::string chars;
			std::cout << "";
			std::cin >> chars;

			std::string tree_str;
			std::cout << "";
			std::cin >> tree_str;

			std::string encoded;
			std::cout << "";
			std::cin >> encoded;

			//HuffmanTree tree(chars, tree_str);
			//std::cout << tree.decode(encoded) << '\n';

			//std::map<std::string, char> vec = tree.get_vec_reverse();
			//std::string builder;
			//for (char ch : encoded) {
			//	builder += ch;
			//	if (vec[builder]) {
			//		std::cout << vec[builder];
			//		builder = "";
			//	}
			//}
			//std::cout << '\n';

			//input the number of leaves, the  order of letters, tree structure and the encoded text.
			//build the Huffman Tree according to the tree strcture. put the letters in the leaves according to the given order. 
			//Given the Huffman Tree and the encoded text, find the original text, and print it. 
		}
		}
	} while (choice != 3);

	return 0;
}
