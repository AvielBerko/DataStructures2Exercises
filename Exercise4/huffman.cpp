#include <queue>
#include <map>
#include "huffman.h"
class CompareNode {
public:
    bool operator()(HuffmanTree::HuffmanNode* const& n1, HuffmanTree::HuffmanNode* const& n2) {
        return n1->frequency > n2->frequency;
    }
};

HuffmanTree::HuffmanTree(const std::string& text) {
    std::map<char, HuffmanNode*> nodes;

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

    std::map<char, HuffmanNode*>::iterator it_nodes = nodes.begin();
    for (; it_nodes != nodes.end(); ++it_nodes) {
        pq.push(it_nodes->second);
    }

    while (pq.size() > 1) {
        HuffmanNode* first = pq.top();
        pq.pop();
        HuffmanNode* second = pq.top();
        pq.pop();

        HuffmanNode* father = new HuffmanNode(0, first, second);
        pq.push(father);
    }

    root = pq.top();
}

HuffmanTree::HuffmanTree(const std::string& chars, const std::string& tree_str) {
}

std::map<char, std::string> HuffmanTree::get_chars_code() const {
    std::map<char, std::string> mp;
    std::string code;
    fill_map(mp, code, root);

    return mp;
}

std::map<std::string, char> HuffmanTree::get_code_chars() const {
    return std::map<std::string, char>();
}

std::string HuffmanTree::to_string() const {
    return std::string();
}

void HuffmanTree::fill_map(std::map<char, std::string>& mp, std::string& code, HuffmanNode* current) const {
    if (!current) return;

    if (!current->left && !current->right) {
        mp.insert(std::make_pair(current->ch, code));
    }

    code += '0';
    fill_map(mp, code, current->left);
    code.pop_back();

    code += '1';
    fill_map(mp, code, current->right);
    code.pop_back();
}
