
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;

        int numSafe = 0;
        while (getline(newfile, line)) {
            // convert string to integer list
            // 34 40 23 43 56
            std::vector<int> nums;
            size_t pos = 0;
            while (line.size() > 0) {
                auto pos = line.find(" ");
                if (pos == std::string::npos) {
                    pos = line.size();
                }

                nums.push_back(std::stoi(line.substr(0, pos)));
                line.erase(0, pos + 1);
            }

            // check the distance between each number, make sure it's 1-3
            bool isIncrease = nums[1] - nums[0] > 0;

            bool isSafe = true;
            for (int i = 0; i < nums.size() - 1; ++i) {
                if (isIncrease) {
                    if (nums[i + 1] - nums[i] > 3 || nums[i + 1] - nums[i] < 1) {
                        isSafe = false;
                        break;
                    }
                } else {
                    if (nums[i] - nums[i + 1] > 3 || nums[i] - nums[i + 1] < 1) {
                        isSafe = false;
                        break;
                    } 
                }
            }

            if (isSafe) {
                numSafe++;
            }
        }

        std::cout << "Number of safe numbers: " << numSafe << std::endl;
    }
    
    return 0;
}

bool isSafe(const std::vector<int>& nums) {
    // check the distance between each number, make sure it's 1-3
    bool isIncrease = nums[1] - nums[0] > 0;

    bool isSafe = true;
    for (int i = 0; i < nums.size() - 1; ++i) {
        if (isIncrease) {
            if (nums[i + 1] - nums[i] > 3 || nums[i + 1] - nums[i] < 1) {
                isSafe = false;
                break;
            }
        } else {
            if (nums[i] - nums[i + 1] > 3 || nums[i] - nums[i + 1] < 1) {
                isSafe = false;
                break;
            } 
        }
    }

    return isSafe;
}

int second() {
std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;

        int numSafe = 0;
        while (getline(newfile, line)) {
            // convert string to integer list
            // 34 40 23 43 56
            std::vector<int> nums;
            size_t pos = 0;
            while (line.size() > 0) {
                auto pos = line.find(" ");
                if (pos == std::string::npos) {
                    pos = line.size();
                }

                nums.push_back(std::stoi(line.substr(0, pos)));
                line.erase(0, pos + 1);
            }

            for (int i = nums.size(); i >= 0; i--) {
                if (i == nums.size()) {
                    if (isSafe(nums)) {
                        numSafe++;
                        break;
                    }
                } else {
                    auto newNums = nums;
                    newNums.erase(newNums.begin() + i);
                    if (isSafe(newNums)) {
                        numSafe++;
                        break;
                    }
                }
            }
        }

        std::cout << "Number of safe numbers: " << numSafe << std::endl;
    }
    return 0;
}

int main() {
    first();
    second();
}


