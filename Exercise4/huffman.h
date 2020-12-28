#pragma once
#include <string>
#include <map>

class HuffmanTree {
public:
    HuffmanTree(const std::string& text);
    HuffmanTree(const std::string& chars, const std::string& tree_str);

    std::map<char, std::string> get_chars_code() const;
    std::map<std::string, char> get_code_chars() const;
    std::string to_string() const;

private:
    struct HuffmanNode {
        char ch;
        size_t frequency;
        HuffmanNode* left, * right;

        HuffmanNode(char ch = 0, HuffmanNode* right = 0, HuffmanNode* left = 0)
            : frequency(1), left(left), right(right), ch(ch) { }
    } * root = 0;

    friend class CompareNode;

    void fill_map(std::map<char, std::string>& mp, std::string& code, HuffmanNode* current) const;
};
