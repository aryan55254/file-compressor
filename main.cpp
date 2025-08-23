#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <queue>
#include <vector>

struct HuffmanNode
{
    char data;
    int frequency;
    HuffmanNode *left = nullptr;
    HuffmanNode *right = nullptr;
};

struct CompareNodes
{
    bool operator()(HuffmanNode *const &a, HuffmanNode *const &b)
    {
        return a->frequency > b->frequency;
    }
};

void generate_codes(HuffmanNode *node, std::string current_code, std::map<char, std::string> &codes_map)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->left == nullptr && node->right == nullptr)
    {
        codes_map[node->data] = current_code;
        return;
    }
    generate_codes(node->left, current_code + "0", codes_map);
    generate_codes(node->right, current_code + "1", codes_map);
};

int main()
{

    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "error in opening the file " << std::endl;
        return 1;
    };
    std::string file_content;
    std::string current_line;
    while (std::getline(inputFile, current_line))
    {
        file_content += current_line + "\n";
    }
    std::map<char, int> file_content_by_character;
    for (char c : file_content)
    {
        file_content_by_character[c]++;
    };
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, CompareNodes> pq;
    for (const auto &pair : file_content_by_character)
    {

        HuffmanNode *pnode = new HuffmanNode{pair.first, pair.second, nullptr, nullptr};
        pq.push(pnode);
    };
    while (pq.size() > 1)
    {
        HuffmanNode *left_child = pq.top();
        pq.pop();
        HuffmanNode *right_child = pq.top();
        pq.pop();

        HuffmanNode *parent = new HuffmanNode{'$', left_child->frequency + right_child->frequency, left_child, right_child};

        pq.push(parent);
    };
    HuffmanNode *root = pq.top();
    std::map<char, std::string> huffman_codes;
    generate_codes(root, "", huffman_codes);
    for (const auto &pair : huffman_codes)
    {
        std::cout << "character : " << pair.first << " huffman_code : " << pair.second << std::endl;
    }
    return 0;
}