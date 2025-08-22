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

    return 0;
}