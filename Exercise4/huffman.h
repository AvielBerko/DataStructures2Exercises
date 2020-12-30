#pragma once
#include <string>
#include <map>

class HuffmanTree {
public:
    // ctor to create the tree by the text to encode
    HuffmanTree(const std::string& text);
    // ctor to create the tree by the tree's structure and letters 
    HuffmanTree(const std::string& tree_str, const std::string& chars);
    ~HuffmanTree();

    // finds the letters in the tree and returns them by the tree's order
    std::vector<char> get_chars() const;
    // encods the letters and returns a map from letter to its encoded value
    std::map<char, std::string> get_chars_to_code() const;
    // encods the letters and returns a map from the encoded value to the letter
    std::map<std::string, char> get_code_to_chars() const;
    // returns the tree's structure
    std::string to_string() const;

private:
    struct HuffmanNode {
        char ch;
        size_t frequency;
        HuffmanNode* left, * right;

        HuffmanNode(char ch = 0, size_t frequency = 1, HuffmanNode* left = 0, HuffmanNode* right = 0)
            : frequency(frequency), left(left), right(right), ch(ch) { }

        ~HuffmanNode() {
            delete left;
            delete right;
        }
    } * root = 0;

    friend class CompareNode;

    // recoursive function that encodes the letters and fills the map from letter to its encoded value
    // the code string reference is used to build the encoded value and doesn't output anything
    void encode_chars(std::map<char, std::string>& mp, std::string& code, HuffmanNode* current) const;
    // recoursive function that finds the letters and fills the chars vector by the tree's order
    void get_chars(std::vector<char>& chars, HuffmanNode* current) const;
    // recoursive function that builds the tree's structure inside the str
    void to_string(std::string& str, HuffmanNode* current) const;
    // recoursive fnction that builds the tree by the given tree's structure and letters
    void parse(std::string::const_iterator& tree_str, std::string::const_iterator& chars, HuffmanNode*& current);
};
