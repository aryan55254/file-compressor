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
void delete_tree(HuffmanNode *node)
{
    if (node == nullptr)
        return;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
};
void compress_file(const std::string &input_filename, const std::string &output_filename)
{
    std::ifstream inputFile(input_filename);
    if (!inputFile.is_open())
    {
        std::cerr << "error in opening the file " << std::endl;
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
    std::ofstream output_file(output_filename, std::ios::binary);
    int unique_chars = file_content_by_character.size();
    output_file.write(reinterpret_cast<const char *>(&unique_chars), sizeof(unique_chars));
    for (const auto &pair : file_content_by_character)
    {
        output_file.write(&pair.first, sizeof(pair.first));
        output_file.write(reinterpret_cast<const char *>(&pair.second), sizeof(pair.second));
    }

    std::ifstream input_file(input_filename);
    char buffer = 0;
    int bits_in_buffer = 0;
    char c;

    while (input_file.get(c))
    {
        std::string code = huffman_codes.at(c);
        for (char bit : code)
        {
            buffer <<= 1;
            if (bit == '1')
            {
                buffer |= 1;
            }
            bits_in_buffer++;

            if (bits_in_buffer == 8)
            {
                output_file.put(buffer);
                buffer = 0;
                bits_in_buffer = 0;
            }
        }
    }

    if (bits_in_buffer > 0)
    {
        buffer <<= (8 - bits_in_buffer);
        output_file.put(buffer);
    };
    input_file.close();
    output_file.close();
    delete_tree(root);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    };
    std::string input_filename = argv[1];
    std::string output_filename = argv[2];

    compress_file(input_filename, output_filename);

    std::ifstream in_file(input_filename, std::ios::binary);
    in_file.seekg(0, std::ios::end);
    long long input_size = in_file.tellg();
    std::ifstream out_file(output_filename, std::ios::binary);
    out_file.seekg(0, std::ios::end);
    long long output_size = out_file.tellg();

    std::cout << "Successfully compressed file." << std::endl;
    std::cout << "Original file size: " << input_size << " bytes" << std::endl;
    std::cout << "Compressed file size: " << output_size << " bytes" << std::endl;

    return 0;
}