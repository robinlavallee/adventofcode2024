
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

    bool operator<(const Point& other) const {
        if (x < other.x) {
            return true;
        } else if (x > other.x) {
            return false;
        } else if (y < other.y) {
            return true;
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
        } else {
            return false;
        }
    }
};

struct CountCost {
    int count = 0;
    int cost = 0;

    bool operator<(const CountCost& other) const {
        if (count < other.count) {
            return true;
        } else if (count > other.count) {
            return false;
        } else if (cost < other.cost) {
            return true;
        } else {
            return false;
        }
    }

    bool operator>(const CountCost& other) const {
        if (count > other.count) {
            return true;
        } else if (count < other.count) {
            return false;
        } else if (cost > other.cost) {
            return true;
        } else {
            return false;
        }
    }
};

struct DirectionCount {
    int direction = None;
    int count = 0;

    bool operator<(const DirectionCount& other) const {
        if (direction < other.direction) {
            return true;
        } else if (direction > other.direction) {
            return false;
        } else if (count < other.count) {
            return true;
        } else {
            return false;
        }
    }

    bool operator>(const DirectionCount& other) const {
        if (direction > other.direction) {
            return true;
        } else if (direction < other.direction) {
            return false;
        } else if (count > other.count) {
            return true;
        } else {
            return false;
        }
    }
};

struct PointDirection {
    Point point;
    DirectionCount dirCount;
    int cost = 0;

    bool operator<(const PointDirection& other) const {
        if (point < other.point) {
            return true;
        } else if (point > other.point) {
            return false;
        } else if (dirCount < other.dirCount) {
            return true;
        } else if (dirCount > other.dirCount) {
            return false;
        } else if (cost < other.cost) {
            return true;
        } else {
            return false;
        }
    }
};


int solve(std::vector<std::vector<int>> maze) {
    std::vector<std::vector<std::map<int, CountCost>>> visited;
    std::map<Point, std::map<DirectionCount, int>> toProcess;

    visited.resize(maze.size());
    for (int i = 0; i < maze.size(); i++) {
        visited[i].resize(maze[i].size());
    }

    PointDirection start = { { 0, 0 }, None, 0 };
    toProcess[start.point][start.dirCount] = 0;
    visited[start.point.y][start.point.x][None] = { 0, 0 };

    while (!toProcess.empty()) {
        auto pointCandidate = toProcess.begin();
        
        // count total visited so far for stats
        // display everything in visited with the lowest cost rows by rows
        for (auto& row : visited) {
            for (auto& entry : row) {
                int lowest = INT_MAX;
                for (auto& elem : entry) {
                    if (elem.second.cost < lowest) {
                        lowest = elem.second.cost;
                    }
                }

                if (lowest == INT_MAX) {
                    std::cout << "     ";
                    continue;
                } else {
                    // align to 4 characters
                    std::string lowestStr = std::to_string(lowest);
                    while (lowestStr.size() < 4) {
                        lowestStr = " " + lowestStr;
                    }
                    std::cout << lowestStr;
                }
            }
            std::cout << std::endl;
        }

        std::cout << "============================" << std::endl;

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

                auto& visitedEntry = visited[nextDirectionCount.point.y][nextDirectionCount.point.x];

                auto visitedIt = visitedEntry.find(nextDirectionCount.dirCount.direction);
                if (visitedIt == visitedEntry.end()) {
                    visitedEntry[nextDirectionCount.dirCount.direction] = { nextDirectionCount.dirCount.count, nextDirectionCount.cost };
                    toProcess[nextDirectionCount.point][nextDirectionCount.dirCount] = nextDirectionCount.cost;
                } else {
                    bool ignore=false;
                    for (auto it = visitedEntry.begin(); it != visitedEntry.end();) {
                        auto& visitedElem = *it;

                        // Replace worse entries (new entry is better on cost and direction count)
                        if (visitedElem.second.count > nextDirectionCount.dirCount.count && visitedElem.second.cost > nextDirectionCount.cost) {
                            // Remove from toProcess as well
                            auto toProcessIt = toProcess[nextDirectionCount.point].find( { visitedElem.first, visitedElem.second.count } );
                            if (toProcessIt != toProcess[nextDirectionCount.point].end()) {
                                toProcess[nextDirectionCount.point].erase(toProcessIt);
                            }
                            it = visitedEntry.erase(it);
                            continue;
                        }

                        // Replace worse entries (new entry is better on cost, and same on direction count)
                        if (visitedElem.second.count == nextDirectionCount.dirCount.count && visitedElem.second.cost > nextDirectionCount.cost) {
                            auto toProcessIt = toProcess[nextDirectionCount.point].find( { visitedElem.first, visitedElem.second.count } );
                            if (toProcessIt != toProcess[nextDirectionCount.point].end()) {
                                toProcess[nextDirectionCount.point].erase(toProcessIt);
                            }
                            it = visitedEntry.erase(it);
                            continue;
                        }

                        // Replace worse entries (new entry is same on cost, and better on direction count)
                        if (visitedElem.second.count > nextDirectionCount.dirCount.count && visitedElem.second.cost == nextDirectionCount.cost) {
                            auto toProcessIt = toProcess[nextDirectionCount.point].find( { visitedElem.first, visitedElem.second.count } );
                            if (toProcessIt != toProcess[nextDirectionCount.point].end()) {
                                toProcess[nextDirectionCount.point].erase(toProcessIt);
                            }
                            it = visitedEntry.erase(it);
                            continue;
                        }

                        // do nothing if the entry is the same (ignore it)
                        if (visitedElem.second.count == nextDirectionCount.dirCount.count && visitedElem.second.cost == nextDirectionCount.cost) {
                            ignore = true;
                            ++it;
                            continue;
                        }

                        // do nothing if the entry has same cost but higher count
                        if (visitedElem.second.cost == nextDirectionCount.cost && visitedElem.second.count < nextDirectionCount.dirCount.count) {
                            ignore = true;
                            ++it;
                            continue;
                        }

                        // do nothing if the entry has higher cost but same count
                        if (visitedElem.second.cost < nextDirectionCount.cost && visitedElem.second.count == nextDirectionCount.dirCount.count) {
                            ignore = true;
                            ++it;
                            continue;
                        }

                        // do nothing if the entry has higher cost and higher count
                        if (visitedElem.second.cost < nextDirectionCount.cost && visitedElem.second.count < nextDirectionCount.dirCount.count) {
                            ignore = true;
                            ++it;
                            continue;
                        }
                        ++it;
                    }

                    if (!ignore) {
                        visitedEntry[nextDirectionCount.dirCount.direction] = { nextDirectionCount.dirCount.count, nextDirectionCount.cost };
                        toProcess[nextDirectionCount.point][nextDirectionCount.dirCount] = nextDirectionCount.cost;
                    }
                }
            }
        }

        toProcess.erase(pointCandidate);
    }

    // get the best cost from bottom right position
    int bestCost = INT_MAX;
    for (auto& entry : visited[maze.size() - 1][maze[0].size() - 1]) {
        if (entry.second.cost < bestCost) {
            bestCost = entry.second.cost;
        }
    }

    return bestCost;
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


