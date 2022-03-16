#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

const int TABLE_SIZE = 5;
const bool DEBUG = false;
const bool DEBUG_INPUT = false;

class BingoElement
{
public:
    int value;
    bool is_set;

    BingoElement(int value)
    {
        this->value = value;
        this->is_set = false;
    }
};

class BingoTable
{
public:
    std::vector<std::vector<BingoElement>> table;
    bool is_winned = false;
    int guess = -1;
};

bool isArrayContainBool(std::vector<bool> &vec, bool target)
{
    return std::find(vec.begin(), vec.end(), target) != vec.end();
}

BingoTable getBingoTable(std::ifstream &file)
{
    /*
        Usage:
            Read a 2D integer from a file point to the beginning of the number.

        * Accept extra space for 1 digit number.
        * Load the extra space after the table.

        Example:
        v
         3 55 15 54 81
        56 77 20 99 25
        90 57 67  0 97
        28 45 69 84 14
        91 94 39 36 85
        (extra space)
    */
    std::string incomingLine;
    BingoTable table;

    for (int col = 0; col < TABLE_SIZE; col++)
    {
        char singleChar;
        char *numberCharArrayPtr = new char[3];
        std::vector<BingoElement> row;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            int c = 0;
            while (c < 3)
            {
                /* code */
                file.get(singleChar);
                numberCharArrayPtr[c] = singleChar;
                c++;
            }
            if (numberCharArrayPtr[2] == '1')
            {
                // Detect EOF of file.
                numberCharArrayPtr[2] = ' ';
            }
            std::string number(numberCharArrayPtr);

            BingoElement element(std::stoi(number));
            row.push_back(element);
        }
        table.table.push_back(row);
    }

    char spaceChar;
    file.get(spaceChar);

    if (DEBUG_INPUT)
    {
        for (int i = 0; i < table.table.size(); i++)
        {
            for (int j = 0; j < table.table[0].size(); j++)
            {
                std::cout << table.table[i][j].value << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl
                  << std::endl;
    }

    return table;
}

std::vector<int> getGuessList(std::ifstream &file)
{
    /*
        Usage:
            Get first line of input split by ,

        * Load the extra space after the table.

        Example:
        v
        87,7,82,21,47,88,12,71,24,35,10,90,4,97,30,55,36,74,19,50,23,46,13,44,69,27,2,0,37,33,99,49,77,15,89,98,31,51,22,96,73,94,95,18,52,78,32,83,85,54,75,84,59,25,76,45,20,48,9,28,39,70,63,56,5,68,61,26,58,92,67,53,43,62,17,81,80,66,91,93,41,64,14,8,57,38,34,16,42,11,86,72,40,65,79,6,3,29,60,1
        (extra space)
    */
    std::string incomingLine;
    std::vector<int> guessArray;
    while (getline(file, incomingLine))
    {
        if (incomingLine.empty())
        {
            break;
        }
        std::istringstream ss(incomingLine);
        std::string substr;
        while (getline(ss, substr, ','))
        {
            guessArray.push_back(std::stoi(substr));
        }
        if (DEBUG_INPUT)
        {
            for (int i = 0; i < guessArray.size(); i++)
            {
                std::cout << guessArray[i] << " ";
            }
            std::cout << std::endl
                      << std::endl;
        }
    }

    return guessArray;
}

void setBingoInTable(BingoTable &table, int target)
{
    /*
        Usage:
            Input a table and target number, if the element match the target,
            set the is_set member in the BingoElement object.
    */
    for (int i = 0; i < table.table.size(); i++)
    {
        for (int j = 0; j < table.table[0].size(); j++)
        {
            if (table.table[i][j].value == target)
            {
                table.table[i][j].is_set = true;
            }
        }
    }
}

void appliedBingo(std::vector<BingoTable> &tableList, int target)
{
    /*
        Usage:
            A loop function for running setBingoInTable for a table list with a target number.
    */

    for (int i = 0; i < tableList.size(); i++)
    {
        if (!tableList[i].is_winned)
        {
            setBingoInTable(tableList[i], target);
        }
    }
}

bool checkBingoInTable(BingoTable &table)
{
    /*
        Usage:
            Check if there is a bingo happened in a table
    */

    std::vector<bool> rowCheckList;
    std::vector<bool> colCheckList;
    for (int i = 0; i < table.table.size(); i++)
    {
        // Multiply the row.
        bool rowElement = true;
        for (int j = 0; j < table.table[0].size(); j++)
        {
            rowElement *= table.table[i][j].is_set;
        }
        rowCheckList.push_back(rowElement);

        // Multiply the column.
        bool colElement = true;
        for (int j = 0; j < table.table[0].size(); j++)
        {
            colElement *= table.table[j][i].is_set;
        }
        colCheckList.push_back(colElement);
    }

    if (DEBUG)
    {
        for (int j = 0; j < TABLE_SIZE; j++)
        {
            std::cout << colCheckList[j] << " ";
        }
        std::cout << std::endl
                  << std::endl;

        for (int j = 0; j < TABLE_SIZE; j++)
        {
            std::cout << rowCheckList[j] << std::endl;
        }
        std::cout << std::endl
                  << std::endl;
    }

    return isArrayContainBool(colCheckList, true) || isArrayContainBool(rowCheckList, true);
}

void findBingoTable(std::vector<BingoTable> &tableList, std::vector<int> &order, int guess)
{
    /*
        Usage:
            Give a list of table, if the table has bingo happened, it will set the is_winned and prevent the check.
            Also save the guess number and the index of the table.
    */
    for (int i = 0; i < tableList.size(); i++)
    {
        // Q: What if there is 2 more table winned in the same round, how to decide the order?
        if (!tableList[i].is_winned && checkBingoInTable(tableList[i]))
        {
            order.push_back(i);
            tableList[i].is_winned = true;
            tableList[i].guess = guess;
        }
    }
}

int calculateUnmarkValue(BingoTable &table)
{
    /*
        Usage:
            Follow the equation from the problem description.
            Return the final score.
    */
    int result = 0;
    for (int i = 0; i < table.table.size(); i++)
    {
        for (int j = 0; j < table.table[0].size(); j++)
        {
            if (!table.table[i][j].is_set)
            {
                result += table.table[i][j].value;
            }
        }
    }

    return result;
}

void showTableinformation(BingoTable &table)
{
    /*
        Usage:
            Print the value and mark in a single table.
    */
    for (int r = 0; r < 2; r++)
    {
        for (int i = 0; i < table.table.size(); i++)
        {
            for (int j = 0; j < table.table[0].size(); j++)
            {
                if (r == 0)
                {
                    std::cout << table.table[i][j].value << " ";
                }
                else
                {
                    std::cout << table.table[i][j].is_set << " ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl
                  << std::endl;
    }
}

int main()
{
    // ifstream object for reading file.
    std::ifstream inputFile("input");
    std::vector<int> guessArray;
    std::vector<BingoTable> tableList;
    std::vector<int> winnedOrder;
    std::vector<bool> winnedTable;
    int part1_answer = -1;
    int part2_answer = -1;

    // Read guess list and every table.
    guessArray = getGuessList(inputFile);

    while (!inputFile.eof())
    {
        tableList.push_back(getBingoTable(inputFile));
    }

    // Main program
    for (int i = 0; i < guessArray.size(); i++)
    {
        appliedBingo(tableList, guessArray[i]);
        if (i < TABLE_SIZE - 1)
        {
            // The first 4 numbers will not trigger bingo.
            continue;
        }
        findBingoTable(tableList, winnedOrder, i);
    }

    // Calculate the final score of the first bingo and the last bingo.
    part1_answer = calculateUnmarkValue(tableList[winnedOrder[0]]) * guessArray[tableList[winnedOrder[0]].guess];
    part2_answer = calculateUnmarkValue(tableList[winnedOrder[winnedOrder.size() - 1]]) * guessArray[tableList[winnedOrder[winnedOrder.size() - 1]].guess];

    std::printf("Part1 Answer : %d\n\n", part1_answer);
    std::printf("Part2 Answer : %d\n\n", part2_answer);

    return 0;
}