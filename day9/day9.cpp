
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;

        int sumExtrapoled = 0;
        while (getline(newfile, line)) {
            line += " ";
            std::vector<int> numbers;
            int space = line.find(" ");
            while (space != std::string::npos) {
                std::string number = line.substr(0, space);
                numbers.push_back(std::stoi(number));
                line = line.substr(space + 1);
                space = line.find(" ");
            }

            std::vector<std::vector<int>> allNumbers;
            allNumbers.push_back(numbers);

            while (true) {
                std::vector<int>& lastNumbers = allNumbers[allNumbers.size() - 1];
                bool allZeros = true;
                std::vector<int> diffs;
                for  (size_t i = 0; i < lastNumbers.size()-1; ++i) {
                    int diff = lastNumbers[i+1] - lastNumbers[i];
                    if (diff != 0) {
                        allZeros = false;
                    }
                    diffs.push_back(diff);
                }

                allNumbers.push_back(diffs);

                if (allZeros) {
                    break;
                }
            }

            allNumbers[allNumbers.size() - 1].push_back(0);

            for (int j = allNumbers.size() - 2; j >= 0; --j) {
                auto& currentNumbers = allNumbers[j];
                int extrapolated = allNumbers[j + 1][allNumbers[j + 1].size() - 1];
                currentNumbers.push_back(currentNumbers[currentNumbers.size() - 1] + extrapolated);
            }

            int extrapolated = allNumbers[0][allNumbers[0].size() - 1];
            sumExtrapoled += extrapolated;
        }

        std::cout << sumExtrapoled << std::endl;
    }

    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;

        int sumExtrapoled = 0;
        while (getline(newfile, line)) {
            line += " ";
            std::vector<int> numbers;
            int space = line.find(" ");
            while (space != std::string::npos) {
                std::string number = line.substr(0, space);
                numbers.push_back(std::stoi(number));
                line = line.substr(space + 1);
                space = line.find(" ");
            }

            std::vector<std::vector<int>> allNumbers;
            allNumbers.push_back(numbers);

            while (true) {
                std::vector<int>& lastNumbers = allNumbers[allNumbers.size() - 1];
                bool allZeros = true;
                std::vector<int> diffs;
                for (size_t i = 0; i < lastNumbers.size() - 1; ++i) {
                    int diff = lastNumbers[i + 1] - lastNumbers[i];
                    if (diff != 0) {
                        allZeros = false;
                    }
                    diffs.push_back(diff);
                }

                allNumbers.push_back(diffs);

                if (allZeros) {
                    break;
                }
            }

            allNumbers[allNumbers.size() - 1].insert(allNumbers[allNumbers.size() - 1].begin(), 0);

            for (int j = allNumbers.size() - 2; j >= 0; --j) {
                auto& currentNumbers = allNumbers[j];
                int extrapolated = allNumbers[j + 1][0];
                currentNumbers.insert(currentNumbers.begin(), currentNumbers[0] - extrapolated);
            }

            int extrapolated = allNumbers[0][0];
            std::cout << extrapolated << std::endl;
            sumExtrapoled += extrapolated;
        }

        std::cout << sumExtrapoled << std::endl;
    }

    return 0;
}

int main() {
    first();
    second();
}


