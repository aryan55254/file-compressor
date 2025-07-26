#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main()
{
    std::ifstream myfile("index.txt");
    if (!myfile.is_open())
    {
        std::cerr << "error opening file or reading file" << std::endl;
        return 1;
    }
    char ch;
    std::string filecontents;
    while (myfile.get(ch))
    {
        filecontents += ch;
    }
    std::map<char, int> charfrequency;
    for (char c : filecontents)
    {
        charfrequency[c]++;
    }

    for (const auto &pair : charfrequency)
    {
        std::cout << "character : " << pair.first << " , frequency : " << pair.second << std::endl;
    }

    myfile.close();
    return 0;
}