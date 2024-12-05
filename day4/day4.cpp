
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

void replace(std::string& str,
    const std::string& oldStr,
    const std::string& newStr)
{
    std::string::size_type pos = 0u;
    while ((pos = str.find(oldStr, pos)) != std::string::npos) {
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(newfile, line)) {
            lines.push_back(line);
        }

        int numXmas = 0;
        
        for (int i = 0; i < lines.size(); i++) {
            for (int j = 0; j < lines[i].size(); j++) {

                // check up
                if (i >= 3 && lines[i][j] == 'X' && lines[i - 1][j] == 'M' && lines[i - 2][j] == 'A' && lines[i - 3][j] == 'S') {
                    numXmas++;
                }

                // check down
                if (i <= lines.size() - 4 && lines[i][j] == 'X' && lines[i + 1][j] == 'M' && lines[i + 2][j] == 'A' && lines[i + 3][j] == 'S') {
                    numXmas++;
                }

                // check left
                if (j >= 3 && lines[i][j] == 'X' && lines[i][j - 1] == 'M' && lines[i][j - 2] == 'A' && lines[i][j - 3] == 'S') {
                    numXmas++;
                }

                // check right
                if (j <= lines[i].size() - 4 && lines[i][j] == 'X' && lines[i][j + 1] == 'M' && lines[i][j + 2] == 'A' && lines[i][j + 3] == 'S') {
                    numXmas++;
                }

                // check up left
                if (i >= 3 && j >= 3 && lines[i][j] == 'X' && lines[i - 1][j - 1] == 'M' && lines[i - 2][j - 2] == 'A' && lines[i - 3][j - 3] == 'S') {
                    numXmas++;
                }

                // check up right
                if (i >= 3 && j <= lines[i].size() - 4 && lines[i][j] == 'X' && lines[i - 1][j + 1] == 'M' && lines[i - 2][j + 2] == 'A' && lines[i - 3][j + 3] == 'S') {
                    numXmas++;
                }

                // check down left
                if (i <= lines.size() - 4 && j >= 3 && lines[i][j] == 'X' && lines[i + 1][j - 1] == 'M' && lines[i + 2][j - 2] == 'A' && lines[i + 3][j - 3] == 'S') {
                    numXmas++;
                }

                // check down right
                if (i <= lines.size() - 4 && j <= lines[i].size() - 4 && lines[i][j] == 'X' && lines[i + 1][j + 1] == 'M' && lines[i + 2][j + 2] == 'A' && lines[i + 3][j + 3] == 'S') {
                    numXmas++;
                }
            }
        }

        std::cout << "Num Xmas: " << numXmas << std::endl;


    }   
    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(newfile, line)) {
            lines.push_back(line);
        }

        std::vector<std::map<std::pair<int, int>, char>> pattern = 
        {
            {
                {{0, 0}, 'M'},
                {{0, 2}, 'S'},
                {{1, 1}, 'A'},
                {{2, 0}, 'M'},
                {{2, 2}, 'S'}
            },
            {
                {{0, 0}, 'S'},
                {{0, 2}, 'S'},
                {{1, 1}, 'A'},
                {{2, 0}, 'M'},
                {{2, 2}, 'M'}
            },
            {
                {{0, 0}, 'S'},
                {{0, 2}, 'M'},
                {{1, 1}, 'A'},
                {{2, 0}, 'S'},
                {{2, 2}, 'M'}
            },
            {
                {{0, 0}, 'M'},
                {{0, 2}, 'M'},
                {{1, 1}, 'A'},
                {{2, 0}, 'S'},
                {{2, 2}, 'S'}
            }
        };

        int numPatternsFound = 0;
        for (int i = 0; i < lines.size() - 2; i++) {
            for (int j = 0; j < lines[i].size() - 2; j++) {
                for (int k = 0; k < pattern.size(); k++) {
                    bool valid = true;
                    for (auto it = pattern[k].begin(); it != pattern[k].end(); it++) {
                        if (lines[i + it->first.first][j + it->first.second] != it->second) {
                            valid = false;
                            break;
                        }
                    }

                    if (valid) {
                        std::cout << "Pattern Found at coordinates: (" << i << ", " << j << ")" << std::endl;
                        numPatternsFound++;
                    }
                }
            }
        }

        std::cout << "Num Patterns Found: " << numPatternsFound << std::endl;        
    }

    return 0;
}

int main() {
    first();
    second();
}


