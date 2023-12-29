
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

struct Point {
    int x;
    int y;
    int z;

    bool operator<(const Point& other) const {
        if (x < other.x) {
            return true;
        } else if (x > other.x) {
            return false;
        } else if (y < other.y) {
            return true;
        } else if (y > other.y) {
            return false;
        } else if (z < other.z) {
            return true;
        } else if (z > other.z) {
            return false;
        } else {
            return false;
        }
    }

    bool operator>(const Point& other) const {
        if (x > other.x) {
            return true;
        } else if (x < other.x) {
            return false;
        } else if (y > other.y) {
            return true;
        } else if (y < other.y) {
            return false;
        } else if (z > other.z) {
            return true;
        } else if (z < other.z) {
            return false;
        } else {
            return false;
        }
    }
};

struct Brick {
    Point p1;
    Point p2;

    Brick(Point p1, Point p2) : p1(p1), p2(p2) {}

    bool isVertical() const { return p1.z != p2.z; }
    bool isHorizontal() const { return !isVertical(); }

    bool operator<(const Brick& other) const {
        if (p1 < other.p1) {
            return true;
        } else if (p1 > other.p1) {
            return false;
        } else if (p2 < other.p2) {
            return true;
        } else if (p2 > other.p2) {
            return false;
        } else {
            return false;
        }
    }
}

void fall(std::vector<std::vector<std::vector<int>>>& grid, std::set<Brick>& bricks) {
    bool stable = true;
    int numZ = grid.size();
    int numY = grid[0].size();
    int numX = grid[0][0].size();
    do {
        for (auto it = bricks.begin(); it != bricks.end();) {
            Brick brick = *it;

            // check if it can go down
            if (brick.isHorizontal()) {

            }
        }

    } while (!stable);
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::vector<std::vector<std::vector<int>>> grid;

        int maxX = 0;
        int maxY = 0;
        int maxZ = 0;

        std::string line;
        while (getline(newfile, line)) {
            // line is of the format 3,9,130~5,9,130

            auto squigle = line.find('~');
            auto first = line.substr(0, squigle);
            auto second = line.substr(squigle + 1);

            // get x,y,z coordinates from first
            auto comma1 = first.find(',');
            auto comma2 = first.find(',', comma1 + 1);
            auto x = std::stoi(first.substr(0, comma1));
            auto y = std::stoi(first.substr(comma1 + 1, comma2 - comma1 - 1));
            auto z = std::stoi(first.substr(comma2 + 1));

            maxX = std::max(maxX, x);
            maxY = std::max(maxY, y);
            maxZ = std::max(maxZ, z);

            // get x,y,z coordinates from second
            auto comma3 = second.find(',');
            auto comma4 = second.find(',', comma3 + 1);
            auto x2 = std::stoi(second.substr(0, comma3));
            auto y2 = std::stoi(second.substr(comma3 + 1, comma4 - comma3 - 1));
            auto z2 = std::stoi(second.substr(comma4 + 1));

            maxX = std::max(maxX, x2);
            maxY = std::max(maxY, y2);
            maxZ = std::max(maxZ, z2);
        }

        newfile.clear();
        newfile.seekg(0, std::ios::beg);

        // now create the data structure required from those max values
        grid.resize(maxZ + 1);
        for (int i = 0; i < maxZ + 1; i++) {
            grid[i].resize(maxY + 1);
            for (int j = 0; j < maxY + 1; j++) {
                grid[i][j].resize(maxX + 1);
            }
        }

        std::set<Brick> bricks;

        while (getline(newfile, line)) {
            auto squigle = line.find('~');
            auto first = line.substr(0, squigle);
            auto second = line.substr(squigle + 1);

            // get x,y,z coordinates from first
            auto comma1 = first.find(',');
            auto comma2 = first.find(',', comma1 + 1);
            auto x = std::stoi(first.substr(0, comma1));
            auto y = std::stoi(first.substr(comma1 + 1, comma2 - comma1 - 1));
            auto z = std::stoi(first.substr(comma2 + 1));

            // get x,y,z coordinates from second
            auto comma3 = second.find(',');
            auto comma4 = second.find(',', comma3 + 1);
            auto x2 = std::stoi(second.substr(0, comma3));
            auto y2 = std::stoi(second.substr(comma3 + 1, comma4 - comma3 - 1));
            auto z2 = std::stoi(second.substr(comma4 + 1));

            bricks.insert(Brick(Point{x, y, z}, Point{x2, y2, z2}));
            for (int i = z; i <= z2; i++) {
                for (int j = y; j <= y2; j++) {
                    for (int k = x; k <= x2; k++) {
                        grid[i][j][k] = 1;
                    }
                }
            }
        }

        fall(grid, bricks);)
          
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