#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

const bool DEBUG = false;

typedef std::pair<int, int> Point;
typedef std::pair<Point, Point> Line;
typedef std::vector<std::vector<int>> Table;

void showLine(Line line)
{
    std::printf("p1 = (%d, %d), p2 = (%d, %d)\n", line.first.first, line.first.second, line.second.first, line.second.second);
}

void showPoint(Point pt)
{
    std::printf("(%d, %d))\n", pt.first, pt.second);
}

void showTable(Table &table)
{
    for (size_t i = 0; i < table.size(); i++)
    {
        for (size_t j = 0; j < table[i].size(); j++)
        {
            std::cout << table[i][j];
        }

        std::cout << std::endl;
    }
}

void dumpTable(Table &table, std::string filename)
{
    std::ofstream outFile;
    outFile.open(filename);
    for (size_t i = 0; i < table.size(); i++)
    {
        for (size_t j = 0; j < table[i].size(); j++)
        {
            outFile << table[i][j] << " ";
        }
        outFile << std::endl;
    }
    outFile.close();
}

std::vector<Line> getInputData(std::ifstream &file)
{
    std::string inputLine;
    std::string substring = " -> ";
    std::vector<Line> result;
 
    
    while(getline(file, inputLine))
    {
        inputLine.replace(inputLine.find(substring), substring.length(), ",");

        std::istringstream ss(inputLine);
        std::string pointStr;
        std::vector<int> pointSet;
        while(getline(ss, pointStr, ','))
        {
            pointSet.push_back(std::stoi(pointStr));
        }

        // Save the point to a line object.
        Line line;
        line.first.first = pointSet[0];
        line.first.second = pointSet[1];
        line.second.first = pointSet[2];
        line.second.second = pointSet[3];
        result.push_back(line);
    }

    if(DEBUG)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
           showLine(result[i]); 
        }
    }

    return result;
}

int getMaxSizeX(std::vector<Line> lineList)
{
    int max = 0;
    for (size_t i = 0; i < lineList.size(); i++)
    {
        max = std::max(max, lineList[i].first.first);
        max = std::max(max, lineList[i].second.first);
    }
    return max;
}

int getMaxSizeY(std::vector<Line> lineList)
{
    int max = 0;
    for (size_t i = 0; i < lineList.size(); i++)
    {
        max = std::max(max, lineList[i].first.second);
        max = std::max(max, lineList[i].second.second);
    }
    return max;
}

int8_t directionOfLine(Line line) {
    // 1:vertical, -1:horizontal, 0:cross

    if(line.second.first-line.first.first == 0)
    {
        return 1;
    }
    else if(line.second.second-line.first.second == 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }

}

std::vector<Point> extractPointFromLine(Line line)
{
    // 0,9 -> 5,9
    // 8,0 -> 0,8
    // Only consider x1==x2 or y1==y2
    std::vector<Point> result;

    if(directionOfLine(line)>0)
    {
        if(line.first.second > line.second.second)
        {
            std::swap(line.first.second, line.second.second);
        }

        for (size_t i =line.first.second; i <= line.second.second; i++)
        {
            Point pt(line.first.first, i);
            result.push_back(pt);
        }
    }
    else if(directionOfLine(line)<0)
    {
        if(line.first.first > line.second.first)
        {
            std::swap(line.first.first, line.second.first);
        }

        for (size_t i =line.first.first; i <= line.second.first; i++)
        {
            Point pt(i, line.first.second);
            result.push_back(pt);
        }
    }
    // else
    // {
        // std::cout << "Cross line" << std::endl;
    // }

    if(DEBUG)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            showPoint(result[i]);
        }
    }

    return result;
}

void setPointInTable(Table &table, Point point)
{
    table[point.second][point.first] += 1;
}

void applyLineInTable(Table &table, Line line)
{
    std::vector<Point> path = extractPointFromLine(line);
    if (path.empty())
    {
        return;
    }
    
    for (size_t i = 0; i < path.size(); i++)
    {
        setPointInTable(table, path[i]);
    }
}



int main()
{
    std::ifstream inputFile("input");
    std::vector<Line> lineList = getInputData(inputFile);

    int height = getMaxSizeY(lineList)+1;
    int width = getMaxSizeX(lineList)+1;

    std::vector<std::vector<int>> table(width, std::vector<int>(height));

    for (size_t i = 0; i < lineList.size(); i++)
    {
        applyLineInTable(table, lineList[i]);
    }

    int ans = 0;
    for (size_t i = 0; i < table.size(); i++)
    {
        for (size_t j = 0; j < table[i].size(); j++)
        {
            if (table[i][j] >= 2)
            {
                ans += 1;
            }
        }
    }

    printf("\n\n%d\n", ans);
    
    return 0;
}