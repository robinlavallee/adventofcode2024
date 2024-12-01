
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <set>

int first() {
    std::fstream newfile;
    newfile.open("day1_input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;

        std::list<int> list1;
        std::list<int> list2;

        while (getline(newfile, line)) {
            // read two numbers as string from the line
            long num1 = std::stoi(line.substr(0, line.find(" ")));
            long num2 = std::stoi(line.substr(line.find(" ") + 1));

            list1.push_back(num1);
            list2.push_back(num2);
        }

        // sort the lists
        list1.sort();
        list2.sort();

        // compare each value and sum them up
        long sum = 0;
        auto it1 = list1.begin();
        auto it2 = list2.begin();
        while (it1 != list1.end() && it2 != list2.end()) {
            sum += abs(*it1 - *it2);
            it1++;
            it2++;
        }

        std::cout << "Sum of the differences: " << sum << std::endl;

        newfile.close();
    }

    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("day1_input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;

        std::list<int> list;
        std::map<int, int> countMap;

        while (getline(newfile, line)) {
            // read two numbers as string from the line
            long num1 = std::stoi(line.substr(0, line.find(" ")));
            long num2 = std::stoi(line.substr(line.find(" ") + 1));

            list.push_back(num1);
            auto foundIt = countMap.find(num2);
            if (foundIt == countMap.end()) {
                countMap[num2] = 1;
            }
            else {
                foundIt->second++;
            }
        }

        // compare each value and sum them up
        long long sum = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            auto foundIt = countMap.find(*it);
            if (foundIt != countMap.end()) {
                sum += *it * foundIt->second;
            }
        }

        std::cout << "Similary Score: " << sum << std::endl;

        newfile.close();
    }

    return 0;
}

int main() {
    first();
    second();
}


