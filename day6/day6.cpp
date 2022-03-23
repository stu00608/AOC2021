#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void showFishList(std::vector<uint64_t>& fishList) {
    for(auto& item: fishList) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// TODO: Clean the code.
int main(void) {
    std::ifstream inputFile("input");

    std::string inputLine;
    getline(inputFile, inputLine);
    std::istringstream ss(inputLine);
    std::string element;
    std::vector<uint64_t> fishList(9);

    // 0 1 2 3 4 5 6 7 8
    //   1 1 2 1 
    while (getline(ss, element, ',')) {
        fishList[std::stoi(element)]++;
    }

    int days=256;
    while (days--)
    {
        uint64_t deadFish = fishList[0];
        fishList[0] = fishList[1];
        fishList[1] = fishList[2];
        fishList[2] = fishList[3];
        fishList[3] = fishList[4];
        fishList[4] = fishList[5];
        fishList[5] = fishList[6];
        fishList[6] = fishList[7] + deadFish;
        fishList[7] = fishList[8];
        fishList[8] = deadFish;
    }
    
    showFishList(fishList);

    int64_t ans=0;
    for(auto& fish : fishList) {
        ans+=fish;
    }

    std::cout << ans << std::endl;

    return 0;
}