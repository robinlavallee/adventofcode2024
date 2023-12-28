
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

    bool operator<(const Point& other) const {
        if (y < other.y) {
            return true;
        } else if (y == other.y) {
            return x < other.x;
        } else {
            return false;
        }
    }
};

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::vector<std::string> grid;
        std::vector<std::string> solutionGrid;
        std::string line;
        std::set<Point> visitedOdd;
        std::set<Point> visitedEven;
        std::set<Point> toVisit;

        while (getline(newfile, line)) {
            grid.push_back(line);
            auto index = line.find('S');
            if (index != std::string::npos) {
                toVisit.insert({ (int)index, (int) grid.size() - 1 });
            }
        }

        solutionGrid = grid;

        // this is an even/odd problem. Let's start at the beginning and spread out, it's possible some of the tiles won't be reachable.
        int steps = 0;
        const int maxSteps = 64;
        while (steps <= maxSteps) {
            std::set<Point> nextToVisit;

            for (auto& point : toVisit) {
                if (point.x < 0 || point.y < 0 || point.x >= grid[0].length() || point.y >= grid.size()) {
                    continue;
                }

                if (grid[point.y][point.x] == '#') {
                    continue;
                }

                if (visitedEven.find(point) != visitedEven.end() || visitedOdd.find(point) != visitedOdd.end()) {
                    continue;
                }

                if (steps % 2 == 0) {
                    visitedEven.insert(point);
                    solutionGrid[point.y][point.x] = 'O';
                } else {
                    visitedOdd.insert(point);
                }

                nextToVisit.insert({ point.x - 1, point.y });
                nextToVisit.insert({ point.x + 1, point.y });
                nextToVisit.insert({ point.x, point.y - 1 });
                nextToVisit.insert({ point.x, point.y + 1 });
            }
            steps++;
            toVisit = nextToVisit;
        }

        // print solutionGrid
        for (auto& line : solutionGrid) {
            std::cout << line << std::endl;
        }
        std::cout << visitedEven.size() << std::endl;

        newfile.close();
    }

    return 0;
}


int second() {
 std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::vector<std::string> grid;
        std::vector<std::string> solutionGrid;
        std::string line;
        int unvisitable = 0;
        std::set<Point> visitedOdd;
        std::set<Point> visitedEven;
        std::set<Point> toVisit;

        while (getline(newfile, line)) {
            grid.push_back(line);
            auto index = line.find('S');
            if (index != std::string::npos) {
                toVisit.insert({ (int)index, (int) grid.size() - 1 });
            }

            for (auto& c : line) {
                if (c == '#') {
                    unvisitable++;
                }
            }
        }

        solutionGrid = grid;

        // this is an even/odd problem. Let's start at the beginning and spread out, it's possible some of the tiles won't be reachable.
        int steps = 0;
        const int maxSteps = 26501365;
        while (steps <= maxSteps) {
            std::set<Point> nextToVisit;

            if (visitedOdd.size() + unvisitable == grid.size() * grid[0].length()) {
                break;
            }

            for (auto& point : toVisit) {

                if (grid[point.y][point.x] == '#') {
                    continue;
                }

                if (steps % 2 == 0 && visitedEven.find(point) != visitedEven.end()) {
                    continue;
                }

                if (steps % 2 == 1 && visitedOdd.find(point) != visitedOdd.end()) {
                    continue;
                }

                if (steps % 2 == 0) {
                    visitedEven.insert(point);
                } else {
                    visitedOdd.insert(point);
                    solutionGrid[point.y][point.x] = 'O';
                }

                if (point.x == 0) {
                    nextToVisit.insert({ (int)grid[0].length() - 1, point.y });
                } else {
                    nextToVisit.insert({ point.x - 1, point.y });
                }

                if (point.x == grid[0].length() - 1) {
                    nextToVisit.insert({ 0, point.y });
                } else {
                    nextToVisit.insert({ point.x + 1, point.y });
                }
                
                if (point.y == 0) {
                    nextToVisit.insert({ point.x, (int)grid.size() - 1 });
                } else {
                    nextToVisit.insert({ point.x, point.y - 1 });
                }
                
                if (point.y == grid.size() - 1) {
                    nextToVisit.insert({ point.x, 0 });
                } else {
                    nextToVisit.insert({ point.x, point.y + 1 });
                }
            }
            steps++;
            toVisit = nextToVisit;
        }

        // print solutionGrid
        for (auto& line : solutionGrid) {
            std::cout << line << std::endl;
        }
        std::cout << visitedOdd.size() << std::endl;

        newfile.close();
    }

    return 0;
}

int main() {
    first();
    second();
}


