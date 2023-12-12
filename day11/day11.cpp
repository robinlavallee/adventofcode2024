
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

        std::set<int> activeColumns;
        std::set<int> activeRows;

        struct Point {
            int x;
            int y;
            bool operator<(const Point& other) const {
                if (x < other.x) {
                    return true;
                }
                if (x > other.x) {
                    return false;
                }
                return y < other.y;
            }
        };

        std::set<Point> activePoints;

        int row = -1;
        while (getline(newfile, line)) {
            row++;
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == '#') {
                    activeColumns.insert(i);
                    activeRows.insert(row);
                    activePoints.insert({ i, row });
                }
            }
        }

        std::cout << "Total actives: " << activePoints.size() << std::endl;

        // loop on all pairs and find the distance
        unsigned long long sumDistances = 0;
        for (auto& point : activePoints) {
            for (auto& secondpoint : activePoints) {
                if (point.x == secondpoint.x && point.y == secondpoint.y) {
                    continue;
                }

                int stepX = -1;
                if (secondpoint.x > point.x) {
                    stepX = 1;
                }

                int stepY = -1;
                if (secondpoint.y > point.y) {
                    stepY = 1;
                }

                Point current = point;
                unsigned long long distance = 0;
                while (current.x != secondpoint.x) {
                    current.x += stepX;
                    distance++;
                    if (activeColumns.find(current.x) == activeColumns.end()) {
                        distance++;
                    }
                }

                while (current.y != secondpoint.y) {
                    current.y += stepY;
                    distance++;
                    if (activeRows.find(current.y) == activeRows.end()) {
                        distance++;
                    }
                }

                sumDistances += distance;
            }
        }

        std::cout << sumDistances / 2 << std::endl;
    }

    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;

        std::set<int> activeColumns;
        std::set<int> activeRows;

        struct Point {
            int x;
            int y;
            bool operator<(const Point& other) const {
                if (x < other.x) {
                    return true;
                }
                if (x > other.x) {
                    return false;
                }
                return y < other.y;
            }
        };

        std::set<Point> activePoints;

        int row = -1;
        while (getline(newfile, line)) {
            row++;
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == '#') {
                    activeColumns.insert(i);
                    activeRows.insert(row);
                    activePoints.insert({ i, row });
                }
            }
        }

        std::cout << "Total actives: " << activePoints.size() << std::endl;

        // loop on all pairs and find the distance
        unsigned long long sumDistances = 0;
        for (auto& point : activePoints) {
            for (auto& secondpoint : activePoints) {
                if (point.x == secondpoint.x && point.y == secondpoint.y) {
                    continue;
                }

                int stepX = -1;
                if (secondpoint.x > point.x) {
                    stepX = 1;
                }

                int stepY = -1;
                if (secondpoint.y > point.y) {
                    stepY = 1;
                }

                Point current = point;
                unsigned long long distance = 0;
                while (current.x != secondpoint.x) {
                    current.x += stepX;
                    distance++;
                    if (activeColumns.find(current.x) == activeColumns.end()) {
                        distance += 999999;
                    }
                }

                while (current.y != secondpoint.y) {
                    current.y += stepY;
                    distance++;
                    if (activeRows.find(current.y) == activeRows.end()) {
                        distance += 999999;
                    }
                }

                sumDistances += distance;
            }
        }

        std::cout << sumDistances / 2 << std::endl;
    }
       

    return 0;
}

int main() {
    first();
    second();
}


