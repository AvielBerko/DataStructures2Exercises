#include <queue>
#include <map>
#include "huffman.h"

// used by the priority queue to order the queue by the frequency of the nodes.
class CompareNode {
public:
    bool operator()(HuffmanTree::HuffmanNode* const& n1, HuffmanTree::HuffmanNode* const& n2) {
        return n1->frequency > n2->frequency;
    }
};

HuffmanTree::HuffmanTree(const std::string& text) {
    std::map<char, HuffmanNode*> nodes;

    // creates the first nodes of the queue, their letters and frequency
    std::string::const_iterator it = text.begin();
    for (; it != text.end(); ++it) {
        HuffmanNode* node = nodes[*it];
        if (node) {
            node->frequency++;
        }
        else {
            nodes[*it] = new HuffmanNode(*it);
        }
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode> pq;

    // pushes all the nodes from the map to the priority queue to order them by frequency
    std::map<char, HuffmanNode*>::iterator it_nodes = nodes.begin();
    for (; it_nodes != nodes.end(); ++it_nodes) {
        pq.push(it_nodes->second);
    }

    // builds the tree by the huffman algorithm
    while (pq.size() > 1) {
        HuffmanNode* first = pq.top();
        pq.pop();
        HuffmanNode* second = pq.top();
        pq.pop();

        size_t comb_freq = first->frequency + second->frequency;
        HuffmanNode* father = new HuffmanNode(0, comb_freq, first, second);
        pq.push(father);
    }

    root = pq.top();
}

HuffmanTree::HuffmanTree(const std::string& tree_str, const std::string& chars) {
    std::string::const_iterator tree_str_it = tree_str.begin();
    std::string::const_iterator chars_it = chars.begin();
    parse(tree_str_it, chars_it, root);
}

HuffmanTree::~HuffmanTree() {
    delete root;
}

std::vector<char> HuffmanTree::get_chars() const {
    std::vector<char> chars;
    get_chars(chars, root);
    return chars;
}

std::map<char, std::string> HuffmanTree::get_chars_to_code() const {
    std::map<char, std::string> mp;
    std::string _;
    encode_chars(mp, _, root);

    return mp;
}

std::map<std::string, char> HuffmanTree::get_code_to_chars() const {
    std::map<char, std::string> mp = get_chars_to_code();
    std::map<std::string, char> result;

    // reverses the map's direction
    std::map<char, std::string>::iterator it = mp.begin();
    for (; it != mp.end(); ++it) {
        result.insert(std::make_pair(it->second, it->first));
    }

    return result;
}

std::string HuffmanTree::to_string() const {
    std::string str;
    to_string(str, root);

    return str;
}

void HuffmanTree::encode_chars(std::map<char, std::string>& mp, std::string& code, HuffmanNode* current) const {
    if (!current) return;

    // if it is a leaf inserts the letter and the encoded value
    if (!current->left && !current->right) {
        mp.insert(std::make_pair(current->ch, code));
        return;
    }

    // adds 0 to the encoded value for the left node
    code += '0';
    encode_chars(mp, code, current->left);
    code.erase(code.size() - 1, 1);

    // adds 1 to the encoded value for the right node
    code += '1';
    encode_chars(mp, code, current->right);
    code.erase(code.size() - 1, 1);
}

void HuffmanTree::get_chars(std::vector<char>& chars, HuffmanNode* current) const {
    if (!current) return;

    // if it is a leaf inserts the letter
    if (!current->left && !current->right) {
        chars.push_back(current->ch);
    }

    get_chars(chars, current->left);
    get_chars(chars, current->right);
}

void HuffmanTree::to_string(std::string& str, HuffmanNode* current) const {
    if (!current) return;

    // inserts 1 if it is a leaf else inserts 0
    str += '0' + !current->left;

    to_string(str, current->left);
    to_string(str, current->right);
}

void HuffmanTree::parse(std::string::const_iterator& tree_str, std::string::const_iterator& chars, HuffmanNode*& current) {
    current = new HuffmanNode;
    char ch = *tree_str;
    ++tree_str;

    // if it is a leaf sets the letter
    if (ch == '1') {
        current->ch = *chars;
        ++chars;
        return;
    }

    parse(tree_str, chars, current->left);
    parse(tree_str, chars, current->right);
}
