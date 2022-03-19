#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class Fish {
   public:
    uint8_t value;
    uint8_t offset;

    Fish(uint8_t a, uint8_t b) {
        this->value = a;
        this->offset = b;
    }
};

std::vector<Fish> fishList;
int days = 256;
int fishCount = 0;

void fishAlgorithm(Fish fish) {
    int pos = days - fish.offset;
    if (pos > fish.value) {
        int child = (pos - fish.value) / 7 + 1;
        for (size_t i = 0; i < child; i++) {
            int newOffset = fish.offset + 7 * i + fish.value + 1;
            if (newOffset > days) {
                continue;
            }
            // std::cout << newOffset << " ";
            Fish newFish(8, newOffset);
            fishList.push_back(newFish);
        }
        // std::cout << std::endl;
    }
    fishList.erase(fishList.begin());
    fishCount++;
}

int main(void) {
    std::ifstream inputFile("input");

    std::string inputLine;
    getline(inputFile, inputLine);
    std::istringstream ss(inputLine);
    std::string element;
    while (getline(ss, element, ',')) {
        Fish fish(std::stoi(element), 0);
        fishList.push_back(fish);
    }


    while(!fishList.empty()) {
        fishAlgorithm(fishList[0]);        
        std::cout << fishCount << std::endl;
    }

    std::vector<Fish> copy(fishList);

    std::cout << fishCount << std::endl;

    return 0;
}