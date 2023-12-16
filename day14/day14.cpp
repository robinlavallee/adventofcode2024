
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

void moveNorth(std::vector<std::string>& rows) {
    bool stable = true;
    int numRows = rows.size();
    int numCols = rows[0].size();
    do {
        stable = true;
        for (int j = 0; j < numRows - 1; j++) {
            for (int i = 0; i < numCols; i++) {
                if (rows[j][i] == '.' && rows[j+1][i] == 'O') {
                    rows[j][i] = 'O';
                    rows[j+1][i] = '.';
                    stable = false;
                }
            }
        }
    } while (!stable);
}

void moveSouth(std::vector<std::string>& rows) {
    bool stable = true;
    int numRows = rows.size();
    int numCols = rows[0].size();
    do {
        stable = true;
        for (int j = numRows - 2; j >= 0; j--) {
            for (int i = 0; i < numCols; i++) {
                if (rows[j][i] == 'O' && rows[j+1][i] == '.') {
                    rows[j][i] = '.';
                    rows[j+1][i] = 'O';
                    stable = false;
                }
            }
        }
    } while (!stable);
}

void moveWest(std::vector<std::string>& rows) {
    bool stable = true;
    int numRows = rows.size();
    int numCols = rows[0].size();
    do {
        stable = true;
        for (int j = 0; j < numRows; j++) {
            for (int i = 0; i < numCols - 1; i++) {
                if (rows[j][i] == '.' && rows[j][i+1] == 'O') {
                    rows[j][i] = 'O';
                    rows[j][i+1] = '.';
                    stable = false;
                }
            }
        }
    } while (!stable);
}

void moveEast(std::vector<std::string>& rows) {
    bool stable = true;
    int numRows = rows.size();
    int numCols = rows[0].size();
    do {
        stable = true;
        for (int j = 0; j < numRows; j++) {
            for (int i = numCols - 2; i >= 0; i--) {
                if (rows[j][i] == 'O' && rows[j][i+1] == '.') {
                    rows[j][i] = '.';
                    rows[j][i+1] = 'O';
                    stable = false;
                }
            }
        }
    } while (!stable);
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::vector<std::string> rows;

        std::string line;
        while (getline(newfile, line)) {
            rows.push_back(line);
        }

        int numRows = rows.size();
        int numCols = rows[0].size();
        moveNorth(rows);

        // count load going from top to bottom
        int total = 0;
        for (int j = 0; j < numRows; j++) {
            int weight = numRows - j;
            for (int i = 0; i < numCols; i++) {
                if (rows[j][i] == 'O') {
                    total += weight;
                }
            }
        }

        // print the rows
        for (int j = 0; j < numRows; j++) {
            std::cout << rows[j] << std::endl;
        }

        std::cout << total << std::endl;


        newfile.close();
    }

    return 0;
}

unsigned long long computeHash(std::vector<std::string>& rows) {
    unsigned long long hash = 0;
    int numRows = rows.size();
    int numCols = rows[0].size();
    for (int j = 0; j < numRows; j++) {
        for (int i = 0; i < numCols; i++) {
            if (rows[j][i] == 'O') {
                hash += 1 << (j * numCols + i);
            }
        }
    }
    
    return hash;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::vector<std::string> rows;

        std::string line;
        while (getline(newfile, line)) {
            rows.push_back(line);
        }

        int numRows = rows.size();
        int numCols = rows[0].size();

        struct Cache {
            unsigned long long hash;
            unsigned long long iteration;
        };

        std::map<unsigned long long, Cache> cacheMap;

        unsigned long long numIterations = 1000000000;
        unsigned int cycleLength = -1;
        // maybe we can use some dynamic programming here to cache stuff and accelerate loops
        while (numIterations != 0) {
            moveNorth(rows);
            moveWest(rows);
            moveSouth(rows);
            moveEast(rows);
            numIterations--;

            unsigned long long hash = computeHash(rows);
            auto it = cacheMap.find(hash);
            if (it != cacheMap.end()) {
                cycleLength = it->second.iteration - numIterations;
                break;
            } else {
                Cache cache;
                cache.hash = hash;
                cache.iteration = numIterations;
                cacheMap[hash] = cache;
            }
        }

        if (cycleLength != -1 && numIterations != 0) {
            numIterations = numIterations % cycleLength;
        }

        while (numIterations != 0) {
            moveNorth(rows);
            moveWest(rows);
            moveSouth(rows);
            moveEast(rows);
            numIterations--;
        }

        

        // count load going from top to bottom
        int total = 0;
        for (int j = 0; j < numRows; j++) {
            int weight = numRows - j;
            for (int i = 0; i < numCols; i++) {
                if (rows[j][i] == 'O') {
                    total += weight;
                }
            }
        }

        // print the rows
        for (int j = 0; j < numRows; j++) {
            std::cout << rows[j] << std::endl;
        }

        std::cout << total << std::endl;

        newfile.close();
    }

    return 0;
}

int main() {
    first();
    second();
}


