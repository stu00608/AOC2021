#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

const int TABLE_SIZE = 5;

// std::vector<std::vector<int>> getBingoTable(std::ifstream &file)
// {
//     std::string incomingLine;
//     std::vector<std::vector<int>> table;
//     while(getline(file, incomingLine))
//     {
//         if(incomingLine.empty())
//         {
//             break;
//         }
//         std::istringstream ss(incomingLine);
//         std::string substr;
//         std::vector<int> row;
//         while(getline(ss, substr, ' '))
//         {
//             std::cout << substr << std::endl;
//             substr.erase(std::remove(substr.begin(), substr.end(), ' '), substr.end());
//             row.push_back(std::stoi(substr));
//         }
//         table.push_back(row);
//     }

//     for(int i=0;i<table.size();i++)
//     {
//         for(int j=0;j<table[0].size();j++)
//         {
//             std::cout << table[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }

//     return table;
// }

int main()
{
    // ifstream object for reading file.
    std::ifstream inputFile("input");
    
    // Get the guess list from first line.
    std::string incomingLine;
    while(getline(inputFile, incomingLine))
    {
        if(incomingLine.empty())
        {
            std::cout << "Meet space line." << std::endl;
            break;
        }
        std::istringstream ss(incomingLine);
        std::string substr;
        std::vector<int> guessArray;
        while(getline(ss, substr, ','))
        {
            guessArray.push_back(std::stoi(substr));
        }

        for(int i=0;i<guessArray.size();i++)
        {
            std::cout << guessArray[i] << " ";
        }
        std::cout << std::endl;
    }
    
    // TODO: Write a custom split function.
    // TODO: Write a getTable function.


    return 0;
}