
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
    int direction = None;
    int count = 0;
    int cost = 0;
};


int solve(std::vector<std::vector<int>> maze) {
    std::vector<std::vector<std::list<PointDirection>>> visited;
    std::map<Point, std::list<PointDirection>> toProcess;

    visited.resize(maze.size());
    for (int i = 0; i < maze.size(); i++) {
        visited[i].resize(maze[i].size());
    }

    PointDirection start = { { 0, 0 }, None, 0 };
    toProcess.insert({ { start.point.x, start.point.y }, { start } });
    visited[start.point.y][start.point.x].push_back(start);

    while (!toProcess.empty()) {
        auto candidate = *toProcess.begin()->second.begin();
        
        int directions[4] = { Up, Down, Left, Right };
        for (int direction : directions) {
            PointDirection nextPoint = candidate;
            if (direction == Up) {
                nextPoint.point.y--;
            } else if (direction == Down) {
                nextPoint.point.y++;
            } else if (direction == Left) {
                nextPoint.point.x--;
            } else if (direction == Right) {
                nextPoint.point.x++;
            }

            if (nextPoint.direction == direction) {
                nextPoint.count++;
            } else {
                nextPoint.direction = direction;
                nextPoint.count = 1;
            }

            nextPoint.cost += maze[nextPoint.point.y][nextPoint.point.x];

            if (nextPoint.point.x < 0 || nextPoint.point.x >= maze[0].size() || nextPoint.point.y < 0 || nextPoint.point.y >= maze.size()) {
                continue;
            }

            if (nextPoint.count > 3) {
                continue;
            }

            auto visitedDirectionIt = std::find_if(visited[nextPoint.point.y][nextPoint.point.x].begin(), visited[nextPoint.point.y][nextPoint.point.x].end(), [&nextPoint](const PointDirection& pd) {
                return pd.direction == nextPoint.direction;
            });

            // different direction, just add it
            if (visitedDirectionIt == visited[nextPoint.point.y][nextPoint.point.x].end()) {
                visited[nextPoint.point.y][nextPoint.point.x].push_back(nextPoint);
                toProcess[nextPoint.point].push_back(nextPoint);
            } else {
                // it depends on the cost and count
                // TODO

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


