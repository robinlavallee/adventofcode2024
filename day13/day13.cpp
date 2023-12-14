
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

int findMirror(std::vector<std::string>& pattern, int avoid=-1) {
    // check if vertical or horizontal
    int numCols = pattern[0].size();
    int numRows = pattern.size();

    // try vertical reflection
    for (int i = 0; i < numCols - 1; i++) {
        int left = i;
        int right = i+1;

        bool valid = true;
        while (left >= 0 && right < numCols) {
            for (int j = 0; j < numRows; j++) {

                if (pattern[j][left] != pattern[j][right]) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                break;
            }

            left--;
            right++;
        }

        if (valid && (avoid == -1 || i + 1 != avoid)) {
            return i + 1;
        }
    }

    // try horizontal reflection
    for (int i = 0; i < numRows - 1; i++) {
        int top = i;
        int bottom = i+1;

        bool valid = true;
        while (top >= 0 && bottom < numRows) {
            for (int j = 0; j < numCols; j++) {

                if (pattern[top][j] != pattern[bottom][j]) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                break;
            }

            top--;
            bottom++;
        }

        if (valid && (avoid == -1 || (i+1)*100 != avoid)) {
            return (i + 1)*100;
        }
    }

    return -1;
}

int findMirrorSmudge(std::vector<std::string>& pattern) {
    int avoid = findMirror(pattern);

    int numCols = pattern[0].size();
    int numRows = pattern.size();
    for (int j = 0; j < numCols; j++) {
        for (int i = 0; i < numRows; i++) {
            if (pattern[i][j] == '.') {
                pattern[i][j] = '#';
            } else if (pattern[i][j] == '#') {
                pattern[i][j] = '.';
            }

            int tryMirror = findMirror(pattern, avoid);
            if (tryMirror != -1) {
                return tryMirror;
            }

            if (pattern[i][j] == '.') {
                pattern[i][j] = '#';
            } else if (pattern[i][j] == '#') {
                pattern[i][j] = '.';
            }
        }
    }

    return -1;
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::vector<std::string> rows;

        std::string line;
        int total = 0;
        while (getline(newfile, line)) {
            if (line.empty()) {
                int vertical = findMirror(rows);
                std::cout << vertical << std::endl;
                total += vertical;
                rows.clear();
                continue;
            }
            rows.push_back(line);
        }

        int vertical = findMirror(rows);
        std::cout << vertical << std::endl;
        total += vertical;
        std::cout << total << std::endl;

        newfile.close();
    }




    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::vector<std::string> rows;

        std::string line;
        int total = 0;
        while (getline(newfile, line)) {
            if (line.empty()) {
                int vertical = findMirrorSmudge(rows);
                std::cout << vertical << std::endl;
                total += vertical;
                rows.clear();
                continue;
            }
            rows.push_back(line);
        }

        int vertical = findMirrorSmudge(rows);
        std::cout << vertical << std::endl;
        total += vertical;
        std::cout << total << std::endl;

        newfile.close();
    }

    return 0;
}

int main() {
    //first();
    second();
}


