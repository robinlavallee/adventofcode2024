
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

struct DirectionCount {
    int direction = None;
    int count = 0;
};

struct PointDirection {
     Point point;
     DirectionCount dirCount;
     int cost = 0;
};


int solve(std::vector<std::vector<int>> maze) {
    std::vector<std::vector<std::map<DirectionCount, int>>> visited;
    std::map<Point, std::map<DirectionCount, int>> toProcess;

    visited.resize(maze.size());
    for (int i = 0; i < maze.size(); i++) {
        visited[i].resize(maze[i].size());
    }

    PointDirection start = { { 0, 0 }, None, 0 };
    toProcess[start.point][start.dirCount] = 0;
    visited[start.point.y][start.point.x][start.dirCount] = 0;

    while (!toProcess.empty()) {
        auto pointCandidate = toProcess.begin();
        
        const Point& currentPoint = pointCandidate->first;
        for (auto it = pointCandidate->second.begin() ; it != pointCandidate->second.end(); ++it) {
            const DirectionCount& currentDirectionCount = it->first;
            const int& currentCost = it->second;

            int directions[4] = { Up, Down, Left, Right };
            for (int direction : directions) {
                PointDirection nextDirectionCount = { currentPoint, currentDirectionCount, currentCost };
                Point& nextPoint = nextDirectionCount.point;
                if (direction == Up) {
                    nextPoint.y--;
                } else if (direction == Down) {
                    nextPoint.y++;
                } else if (direction == Left) {
                    nextPoint.x--;
                } else if (direction == Right) {
                    nextPoint.x++;
                }

                if (nextPoint.x < 0 || nextPoint.x >= maze[0].size() || nextPoint.y < 0 || nextPoint.y >= maze.size()) {
                    continue;
                }

                if (currentDirectionCount.direction == direction) {
                    nextDirectionCount.dirCount.count++;
                } else {
                    nextDirectionCount.dirCount.direction = direction;
                    nextDirectionCount.dirCount.count = 1;
                }

                if (nextDirectionCount.dirCount.count > 3) {
                    continue;
                }

                nextDirectionCount.cost += maze[nextDirectionCount.point.y][nextDirectionCount.point.x];

                auto visitedIt = visited[nextDirectionCount.point.y][nextDirectionCount.point.x].find(nextDirectionCount.dirCount);
                if (visitedIt == visited[nextDirectionCount.point.y][nextDirectionCount.point.x].end()) {
                    visited[nextDirectionCount.point.y][nextDirectionCount.point.x][nextDirectionCount.dirCount] = nextDirectionCount.cost;
                    toProcess[nextDirectionCount.point][nextDirectionCount.dirCount] = nextDirectionCount.cost;
                } else {
                    // TODO
                }
            }
        }
    }

    return 0;
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


