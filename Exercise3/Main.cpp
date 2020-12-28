// Names: Aviel Berkovich (211981105), Meir Klemfner(211954185)
// Data Structures 2
// Exercise 3
// The main program has no comments beacuse it was copied from the moodle
#include<iostream>
#include <list>
#include <vector>
#include <string>
#include "Trie.h"

void fill(const Trie& trie, std::vector<std::string>& strings, std::vector<size_t>& indecies, const std::string& str, size_t index = 0);
std::string buildString(const std::string& str, const std::vector<size_t>& indecies);

std::vector <std::string> findSpaces(const std::string& str, const std::vector<std::string>& words) {
    Trie trie;
    for (const auto& word : words) {
        trie.insert(word);
    }

    std::vector<std::string> result;
    std::vector<size_t> indecies;
    fill(trie, result, indecies, str);
    return result;
}

void fill(const Trie& trie, std::vector<std::string>& strings, std::vector<size_t>& indecies, const std::string& str, size_t index) {
    std::string word;

    for (size_t i = index; i < str.size(); i++) {
        word += str[i];
        if (!trie.search(word)) continue;

        if (i + 1 == str.size()) {
            strings.push_back(buildString(str, indecies));
            break;
        }

        size_t end = indecies.size();
        indecies.push_back(i + 1);
        fill(trie, strings, indecies, str, i + 1);

        for (size_t j = end; j < indecies.size(); j++) {
            indecies.pop_back();
        }
    }
}

std::string buildString(const std::string& str, const std::vector<size_t>& indecies) {
    std::string builder;

    size_t lastIndex = 0;
    for (size_t index : indecies) {
        builder += std::string(str.begin() + lastIndex, str.begin() + index) + ' ';
        lastIndex = index;
    }
    builder += std::string(str.begin() + lastIndex, str.end());

    return builder;
}

int main() {
    auto result = findSpaces("breakoutside", { "breakout", "out", "outside", "break", "side" });
    for (const auto& str : result) {
        std::cout << str << std::endl;
    }
    return 0;

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
