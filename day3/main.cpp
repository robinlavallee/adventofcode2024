
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
        /* Format is
            467..114..
            ...*......
            ..35..633.
            ......#...
            617*......
            .....+.58.
            ..592.....
            ......755.
            ...$.*....
            .664.598..        
        */

        std::string line;
        std::vector<std::string> charmap;

        while (getline(newfile, line)) {
            charmap.push_back(line);
        }

        // start parsing line by line for a sequence of digits, when you have one, store it a map
        struct number {
            int xStart;
            int xEnd;
            int value;
        };

        std::vector<std::vector<number>> numbers;

        for (int y = 0; y < charmap.size(); y++) {
            std::string row = charmap[y];
            std::vector<number> rowNumbers;
            int x = 0;
            while (x < row.length()) {
                if (row[x] >= '0' && row[x] <= '9') {
                    number n;
                    std::string numberString = "";
                    n.xStart = x;
                    numberString = row[x];
                    x++;
                    while (x < row.length() && row[x] >= '0' && row[x] <= '9') {
                        numberString += row[x];
                        x++;
                    }
                    n.xEnd = x - 1;
                    n.value = std::stoi(numberString);
                    rowNumbers.push_back(n);
                }
                x++;
            }
            numbers.push_back(rowNumbers);
        }

        std::vector<int> parts;

        // loop through the numbers
        for (int y = 0; y < numbers.size(); y++) {
            std::vector<number> rowNumbers = numbers[y];
            for (int x = 0; x < rowNumbers.size(); x++) {
                number n = rowNumbers[x];

                // now check if there is a symbol near the number itself
                for (int i = n.xStart; i <= n.xEnd; i++) {
                    std::vector<std::pair<int, int>> directions = {
                        {-1, -1},
                        {-1, 0},
                        {-1, 1},
                        {0, -1},
                        {0, 1},
                        {1, -1},
                        {1, 0},
                        {1, 1}
                    };

                    bool foundSymbol = false;

                    for (auto& direction : directions) {
                        int checkX = i + direction.first;
                        int checkY = y + direction.second;

                        if (checkX >= 0 && checkX < charmap[y].length() && checkY >= 0 && checkY < charmap.size()) {
                            if (charmap[checkY][checkX] != '.' && (charmap[checkY][checkX] < '0' || charmap[checkY][checkX] > '9')) {
                                std::cout << "Number " << n.value << " at " << n.xStart << ", " << n.xEnd << " has a symbol at " << x << ", " << y << std::endl;
                                parts.push_back(n.value);
                                foundSymbol = true;
                                break;
                            }
                        }
                    }

                    if (foundSymbol) {
                        break;
                    }
                }

                //std::cout << "Number " << n.value << " at " << n.xStart << ", " << n.xEnd << std::endl;
            }
        }

        int sum = 0;
        for (auto& part : parts) {
            sum += part;
        }

        std::cout << "Sum: " << sum << std::endl;
    }

    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        /* Format is
            467..114..
            ...*......
            ..35..633.
            ......#...
            617*......
            .....+.58.
            ..592.....
            ......755.
            ...$.*....
            .664.598..
        */

        std::string line;
        std::vector<std::string> charmap;

        while (getline(newfile, line)) {
            charmap.push_back(line);
        }

        // start parsing line by line for a sequence of digits, when you have one, store it a map
        struct number {
            int xStart;
            int xEnd;
            int value;
        };

        std::vector<std::vector<number>> numbers;

        for (int y = 0; y < charmap.size(); y++) {
            std::string row = charmap[y];
            std::vector<number> rowNumbers;
            int x = 0;
            while (x < row.length()) {
                if (row[x] >= '0' && row[x] <= '9') {
                    number n;
                    std::string numberString = "";
                    n.xStart = x;
                    numberString = row[x];
                    x++;
                    while (x < row.length() && row[x] >= '0' && row[x] <= '9') {
                        numberString += row[x];
                        x++;
                    }
                    n.xEnd = x - 1;
                    n.value = std::stoi(numberString);
                    rowNumbers.push_back(n);
                }
                x++;
            }
            numbers.push_back(rowNumbers);
        }

        // find all the 'gears' that are connected to only TWO numbers
        int sum = 0;
        std::vector<std::pair<int, int>> gears;
        for (int y = 0; y < charmap.size(); y++) {
            for (int x = 0; x < charmap[y].size(); ++x) {
                if (charmap[y][x] == '*') {
                    // it may be a gear if it is connected to only two numbers
                    // one number is wrong, more than 2 numbers is wrong
                    // the same number twice is fine
                    std::set<int> connectedNumbersSet;

                    std::vector<std::pair<int, int>> directions = {
                        {-1, -1},
                        {-1, 0},
                        {-1, 1},
                        {0, -1},
                        {0, 1},
                        {1, -1},
                        {1, 0},
                        {1, 1}
                    };

                    for (auto& direction : directions) {
                        int checkX = x + direction.first;
                        int checkY = y + direction.second;

                        // now loop through all the numbers and see if it is connected to one
                        const auto& rowNumber = numbers[checkY];
                        for (auto& number : rowNumber) {
                            if (checkX >= number.xStart && checkX <= number.xEnd) {
                                connectedNumbersSet.insert(number.value);
                                break;
                            }
                        }
                    }

                    if (connectedNumbersSet.size() == 2) {
                        // multiply the two numbers
                        int product = 1;
                        for (auto& number : connectedNumbersSet) {
                            product *= number;
                        }
                        sum += product;
                    }
                }
            }
        }        

        std::cout << "Sum: " << sum << std::endl;
    }

    return 0;
}

int main() {
    first();
    second();
}


