
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


int solve(std::vector<std::vector<int>> maze, int minMovement=0, int maxMovement=3) {
    std::vector<std::vector<std::map<int, std::list<CountCost>>>> visited;
    std::map<Point, std::map<DirectionCount, int>> toProcess;

    std::map<PointDirection, PointDirection> previousPoint;

    visited.resize(maze.size());
    for (int i = 0; i < maze.size(); i++) {
        visited[i].resize(maze[i].size());
    }

    PointDirection start = { { 0, 0 }, None, 0 };
    toProcess[start.point][start.dirCount] = 0;
    visited[start.point.y][start.point.x][None] = std::list<CountCost>{ { 0, 0 } };

    while (!toProcess.empty()) {
        auto pointCandidate = toProcess.begin();
        
        static const bool DEBUG_DISPLAY = false;
        if (DEBUG_DISPLAY) {
            for (auto& row : visited) {
                for (auto& entry : row) {
                    int lowest = INT_MAX;
                    for (auto& elem : entry) {
                        for (auto& cost : elem.second) {
                            if (cost.cost < lowest) {
                                lowest = cost.cost;
                            }
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
        }

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

                // disallow reverse
                if (currentDirectionCount.direction == Up && direction == Down) {
                    continue;
                } else if (currentDirectionCount.direction == Down && direction == Up) {
                    continue;
                } else if (currentDirectionCount.direction == Left && direction == Right) {
                    continue;
                } else if (currentDirectionCount.direction == Right && direction == Left) {
                    continue;
                }

                if (minMovement > 0) {
                    if (currentDirectionCount.direction != -1 && currentDirectionCount.direction != direction && currentDirectionCount.count < minMovement) {
                        continue;
                    }
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

                if (nextDirectionCount.dirCount.count > maxMovement) {
                    continue;
                }

                nextDirectionCount.cost += maze[nextDirectionCount.point.y][nextDirectionCount.point.x];

                auto& visitedEntry = visited[nextDirectionCount.point.y][nextDirectionCount.point.x];

                auto visitedIt = visitedEntry.find(nextDirectionCount.dirCount.direction);
                if (visitedIt == visitedEntry.end()) {
                    visitedEntry[nextDirectionCount.dirCount.direction] = std::list<CountCost> { { nextDirectionCount.dirCount.count, nextDirectionCount.cost } };
                    toProcess[nextDirectionCount.point][nextDirectionCount.dirCount] = nextDirectionCount.cost;

                    previousPoint[ { nextDirectionCount.point, nextDirectionCount.dirCount, nextDirectionCount.cost }] = { currentPoint, currentDirectionCount, currentCost };
                } else {
                    bool ignore=false;
                    for (auto it = visitedIt->second.begin(); it != visitedIt->second.end();) {
                        auto& visitedElem = *it;

                        // Replace worse entries (new entry is better on cost and direction count)
                        if (visitedElem.count > nextDirectionCount.dirCount.count && visitedElem.cost > nextDirectionCount.cost && minMovement == 0) {
                            // Remove from toProcess as well
                            auto toProcessIt = toProcess[nextDirectionCount.point].find( { nextDirectionCount.dirCount.direction, visitedElem.count } );
                            if (toProcessIt != toProcess[nextDirectionCount.point].end()) {
                                toProcess[nextDirectionCount.point].erase(toProcessIt);
                            }
                            it = visitedIt->second.erase(it);
                            continue;
                        }

                        // Replace worse entries (new entry is better on cost, and same on direction count)
                        if (visitedElem.count == nextDirectionCount.dirCount.count && visitedElem.cost > nextDirectionCount.cost && minMovement == 0) {
                            auto toProcessIt = toProcess[nextDirectionCount.point].find( { nextDirectionCount.dirCount.direction, visitedElem.count } );
                            if (toProcessIt != toProcess[nextDirectionCount.point].end()) {
                                toProcess[nextDirectionCount.point].erase(toProcessIt);
                            }
                            it = visitedIt->second.erase(it);
                            continue;
                        }

                        // Replace worse entries (new entry is same on cost, and better on direction count)
                        if (visitedElem.count > nextDirectionCount.dirCount.count && visitedElem.cost == nextDirectionCount.cost && minMovement == 0) {
                            auto toProcessIt = toProcess[nextDirectionCount.point].find( { nextDirectionCount.dirCount.direction, visitedElem.count } );
                            if (toProcessIt != toProcess[nextDirectionCount.point].end()) {
                                toProcess[nextDirectionCount.point].erase(toProcessIt);
                            }
                            it = visitedIt->second.erase(it);
                            continue;
                        }

                        // do nothing if the entry is the same (ignore it)
                        if (visitedElem.count == nextDirectionCount.dirCount.count && visitedElem.cost == nextDirectionCount.cost) {
                            ignore = true;
                            ++it;
                            continue;
                        }

                        // do nothing if the entry has same cost but higher count
                        if (visitedElem.cost == nextDirectionCount.cost && visitedElem.count < nextDirectionCount.dirCount.count && minMovement == 0) {
                            ignore = true;
                            ++it;
                            continue;
                        }

                        // do nothing if the entry has higher cost but same count
                        if (visitedElem.cost < nextDirectionCount.cost && visitedElem.count == nextDirectionCount.dirCount.count) {
                            ignore = true;
                            ++it;
                            continue;
                        }

                        // do nothing if the entry has higher cost and higher count
                        if (visitedElem.cost < nextDirectionCount.cost && visitedElem.count < nextDirectionCount.dirCount.count && minMovement == 0) {
                            ignore = true;
                            ++it;
                            continue;
                        }
                        ++it;
                    }

                    if (!ignore) {
                        visitedEntry[nextDirectionCount.dirCount.direction].push_back({ nextDirectionCount.dirCount.count, nextDirectionCount.cost });
                        toProcess[nextDirectionCount.point][nextDirectionCount.dirCount] = nextDirectionCount.cost;

                        previousPoint[ { nextDirectionCount.point, nextDirectionCount.dirCount, nextDirectionCount.cost }] = { currentPoint, currentDirectionCount, currentCost };
                    }
                }
            }
        }

        toProcess.erase(pointCandidate);
    }

    // get the best cost from bottom right position
    int bestCost = INT_MAX;
    PointDirection lastPoint;

    for (auto& entry : visited[maze.size() - 1][maze[0].size() - 1]) {
        for (auto& countCost : entry.second) {
            if (countCost.cost < bestCost && countCost.count >= minMovement) {
                bestCost = countCost.cost;

                auto lastPointsIt = previousPoint.find( { { (int)maze[0].size() - 1, (int)maze.size() - 1 }, { entry.first, countCost.count }, countCost.cost });
                for (; lastPointsIt != previousPoint.end(); ++lastPointsIt) {
                    if (lastPointsIt->first.dirCount.count == countCost.count && lastPointsIt->first.dirCount.direction == entry.first) {
                        lastPoint = lastPointsIt->first;
                        break;
                    }
                }
            }
        }
    }

    // display solution in reverse from lastPoint until { 0, 0 }
    while (lastPoint.point.x != 0 || lastPoint.point.y != 0) {
        std::cout << lastPoint.point.x << "," << lastPoint.point.y << std::endl;
        lastPoint = previousPoint[ { lastPoint.point, lastPoint.dirCount, lastPoint.cost }];
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
        std::vector<std::vector<int>> maze;
        std::string line;
        while (getline(newfile, line)) {
            std::vector<int> row;
            for (int i = 0; i < line.size(); i++) {
                row.push_back(line[i] - '0');
            }
            maze.push_back(row);
        }

        int least = solve(maze, 4, 10);
        std::cout << least << std::endl;
        newfile.close();
    }

    return 0;
}
 
int main() {
    first();
    second();
}


