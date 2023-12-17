
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

static const int None = -1;
static const int Up = 0;
static const int Down = 1;
static const int Left = 2;
static const int Right = 3;

struct Point {
    int x;
    int y;
};

struct PointDirection {
    Point point;
    int Direction;
    int count;
};

std::map<Point, std::list<PointDirection>> toVisit;

int solve(std::vector<std::vector<int>> maze) {
    PointDirection start = { { 0, 0 }, None, 0 };

    toVisit.insert({ { start.point.x, start.point.y }, { start } });
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::vector<std::vector<int>> maze;
        std::string line;
        while (getline(newfile, line)) {
            std::vector<int> row;
            for (int i = 0; i < line.size(); i++) {
                row.push_back(line[i] - '0');
            }
            maze.push_back(row);
        }

        int least = solve(maze);
        std::cout << least << std::endl;
        newfile.close();
    }

    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        newfile.close();
    }

    return 0;
}

int main() {
    first();
    second();
}


