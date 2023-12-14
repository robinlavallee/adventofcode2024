
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

enum class Pipe {
    Vertical,
    Horizontal,
    NorthEast,
    NorthWest,
    SouthEast,
    SouthWest,
    None,
    Unknown,
};

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

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        Point start;

        std::vector<std::string> maze;        
        int row=-1;
        std::string line;
        while (getline(newfile, line)) {
            row++;
            maze.push_back(line);
            if (line.find("S") != std::string::npos) {
                // found the start
                int column = line.find("S");
                start = { column, row };
            }
        }

        char possibilities[6] = { '|', '-', 'L', 'J', '7', 'F' };

        for (char possibility : possibilities) {
            auto localMaze = maze;
            localMaze[start.y][start.x] = possibility;
            std::set<Point> visited;

            Point current = start;
            Point previous = start;

            bool success=false;
            int distance = 0;
            while (true) {
                char pipeType;
                if (current.x == start.x && current.y == start.y) {
                    pipeType = possibility;
                } else {
                    pipeType = localMaze[current.y][current.x];
                }

                Point first, second;

                if (pipeType == '|') { // north and south
                    // going out of bounds vertically
                    if (current.y == 0) {
                        break;
                    } else if (current.y == localMaze.size() - 1) {
                        break;
                    }

                    first = { current.x, current.y - 1 };
                    second = { current.x, current.y + 1 };

                    // north
                    if (localMaze[first.y][first.x] != '|' && localMaze[first.y][first.x] != '7' && localMaze[first.y][first.x] != 'F') {
                        break;
                    }

                    // south
                    if (localMaze[second.y][second.x] != '|' && localMaze[second.y][second.x] != 'J' && localMaze[second.y][second.x] != 'L') {
                        break;
                    }
                } else if (pipeType == '-') { // east and west
                    if (current.x == 0) {
                        break;
                    } else if (current.x == localMaze[current.y].size() - 1) {
                        break;
                    }

                    first = { current.x - 1, current.y };
                    second = { current.x + 1, current.y };

                    // west
                    if (localMaze[first.y][first.x] != '-' && localMaze[first.y][first.x] != 'L' && localMaze[first.y][first.x] != 'F') {
                        break;
                    }

                    // east
                    if (localMaze[second.y][second.x] != '-' && localMaze[second.y][second.x] != 'J' && localMaze[second.y][second.x] != '7') {
                        break;
                    }
                } else if (pipeType == 'L') { // north and east
                    if (current.y == 0) {
                        break;
                    } else if (current.x == localMaze[current.y].size() - 1) {
                        break;
                    }

                    first = { current.x + 1, current.y };
                    second = { current.x, current.y - 1 };

                    // east
                    if (localMaze[first.y][first.x] != '-' && localMaze[first.y][first.x] != 'J' && localMaze[first.y][first.x] != '7') {
                        break;
                    }

                    // north
                    if (localMaze[second.y][second.x] != '|' && localMaze[second.y][second.x] != '7' && localMaze[second.y][second.x] != 'F') {
                        break;
                    }
                } else if (pipeType == 'J') { // north and west
                    if (current.x == 0) {
                        break;
                    } else if (current.y == 0) {
                        break;
                    }

                    first = { current.x - 1, current.y };
                    second = { current.x, current.y - 1 };

                    // west
                    if (localMaze[first.y][first.x] != '-' && localMaze[first.y][first.x] != 'F' && localMaze[first.y][first.x] != 'L') {
                        break;
                    }

                    // north
                    if (localMaze[second.y][second.x] != '|' && localMaze[second.y][second.x] != '7' && localMaze[second.y][second.x] != 'F') {
                        break;
                    }
                } else if (pipeType == '7') { // south and west
                    if (current.x == 0) {
                        break;
                    } else if (current.y == localMaze.size() - 1) {
                        break;
                    }

                    first = { current.x - 1, current.y };
                    second = { current.x, current.y + 1 };

                    // west
                    if (localMaze[first.y][first.x] != '-' && localMaze[first.y][first.x] != 'F' && localMaze[first.y][first.x] != 'L') {
                        break;
                    }

                    // south 
                    if (localMaze[second.y][second.x] != '|' && localMaze[second.y][second.x] != 'J' && localMaze[second.y][second.x] != 'L') {
                        break;
                    }
                } else if (pipeType == 'F') { // south and east
                    if (current.x == localMaze[current.y].size() - 1 || current.y == localMaze.size() - 1) {
                        break;
                    }

                    first = { current.x + 1, current.y };
                    second = { current.x, current.y + 1 };

                    // east
                    if (localMaze[first.y][first.x] != '-' && localMaze[first.y][first.x] != 'J' && localMaze[first.y][first.x] != '7') {
                        break;
                    }

                    // south 
                    if (localMaze[second.y][second.x] != '|' && localMaze[second.y][second.x] != 'J' && localMaze[second.y][second.x] != 'L') {
                        break;
                    }
                } else {
                    // out of bounds
                    break;
                }

                // compatible, move, never go back to previous
                visited.insert(current);
                distance++;                
                
                if (visited.find(first) == visited.end()) {
                    current = first;
                } else if (visited.find(second) == visited.end()) {
                    current = second;
                } else {
                    if (first == start || second == start) {
                        success = true;
                    }
                    break;
                }
            }

            if (success) {
                std::cout << "Total length: " << distance << std::endl; // don't forget to divide the answer by two in AOC
            }
        }
    }

    return 0;
}

void floodFill(std::vector<std::string>& maze, std::list<Point> pointsToVisit) {
    while (!pointsToVisit.empty()) {
        Point current = pointsToVisit.front();
        pointsToVisit.pop_front();

        if (current.x < 0 || current.y < 0 || current.y >= maze.size() || current.x >= maze[current.y].size()) {
            continue;
        }

        if (maze[current.y][current.x] == '.') {
            maze[current.y][current.x] = 'O';
            pointsToVisit.push_back({ current.x - 1, current.y });
            pointsToVisit.push_back({ current.x + 1, current.y });
            pointsToVisit.push_back({ current.x, current.y - 1 });
            pointsToVisit.push_back({ current.x, current.y + 1 });
        }
    }
}

int handleLoop(std::vector<std::string> maze, std::set<Point> visited) {
    // mark all the mazes visited point as '#' and everything else as '.', then your goal is to flood-fill everything that touches the boundaries as 'O'. Everything remaining
    // are enclosed by the loops

    for (int j = 0; j < maze.size(); ++j) {
        for (int i = 0; i < maze[j].size(); ++i) {
            if (visited.find({ i, j }) == visited.end()) {
                maze[j][i] = '.';
            } else {
                maze[j][i] = '#';
            }
        }
    }

    // now go ahead and apply the painting algorithms from the sides
    std::list<Point> pointsToVisit;
    for (int j = 0; j < maze.size(); ++j) {
        for (int i = 0; i < maze[j].size(); ++i) {
            if (maze[j][i] == '.' && (i == 0 || i == maze[j].size() - 1 || j == 0 || j == maze.size() - 1)) {
                pointsToVisit.push_back({ i, j });
                floodFill(maze, pointsToVisit);
            }
        }
    }

    int total = 0;

    return total;
}

int second() {
std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        Point start;

        std::vector<std::string> maze;        
        int row=-1;
        std::string line;
        while (getline(newfile, line)) {
            row++;
            maze.push_back(line);
            if (line.find("S") != std::string::npos) {
                // found the start
                int column = line.find("S");
                start = { column, row };
            }
        }

        char possibilities[6] = { '|', '-', 'L', 'J', '7', 'F' };

        for (char possibility : possibilities) {
            auto localMaze = maze;
            localMaze[start.y][start.x] = possibility;
            std::set<Point> visited;

            Point current = start;
            Point previous = start;

            bool success=false;
            int distance = 0;
            while (true) {
                char pipeType;
                if (current.x == start.x && current.y == start.y) {
                    pipeType = possibility;
                } else {
                    pipeType = localMaze[current.y][current.x];
                }

                Point first, second;

                if (pipeType == '|') { // north and south
                    // going out of bounds vertically
                    if (current.y == 0) {
                        break;
                    } else if (current.y == localMaze.size() - 1) {
                        break;
                    }

                    first = { current.x, current.y - 1 };
                    second = { current.x, current.y + 1 };

                    // north
                    if (localMaze[first.y][first.x] != '|' && localMaze[first.y][first.x] != '7' && localMaze[first.y][first.x] != 'F') {
                        break;
                    }

                    // south
                    if (localMaze[second.y][second.x] != '|' && localMaze[second.y][second.x] != 'J' && localMaze[second.y][second.x] != 'L') {
                        break;
                    }
                } else if (pipeType == '-') { // east and west
                    if (current.x == 0) {
                        break;
                    } else if (current.x == localMaze[current.y].size() - 1) {
                        break;
                    }

                    first = { current.x - 1, current.y };
                    second = { current.x + 1, current.y };

                    // west
                    if (localMaze[first.y][first.x] != '-' && localMaze[first.y][first.x] != 'L' && localMaze[first.y][first.x] != 'F') {
                        break;
                    }

                    // east
                    if (localMaze[second.y][second.x] != '-' && localMaze[second.y][second.x] != 'J' && localMaze[second.y][second.x] != '7') {
                        break;
                    }
                } else if (pipeType == 'L') { // north and east
                    if (current.y == 0) {
                        break;
                    } else if (current.x == localMaze[current.y].size() - 1) {
                        break;
                    }

                    first = { current.x + 1, current.y };
                    second = { current.x, current.y - 1 };

                    // east
                    if (localMaze[first.y][first.x] != '-' && localMaze[first.y][first.x] != 'J' && localMaze[first.y][first.x] != '7') {
                        break;
                    }

                    // north
                    if (localMaze[second.y][second.x] != '|' && localMaze[second.y][second.x] != '7' && localMaze[second.y][second.x] != 'F') {
                        break;
                    }
                } else if (pipeType == 'J') { // north and west
                    if (current.x == 0) {
                        break;
                    } else if (current.y == 0) {
                        break;
                    }

                    first = { current.x - 1, current.y };
                    second = { current.x, current.y - 1 };

                    // west
                    if (localMaze[first.y][first.x] != '-' && localMaze[first.y][first.x] != 'F' && localMaze[first.y][first.x] != 'L') {
                        break;
                    }

                    // north
                    if (localMaze[second.y][second.x] != '|' && localMaze[second.y][second.x] != '7' && localMaze[second.y][second.x] != 'F') {
                        break;
                    }
                } else if (pipeType == '7') { // south and west
                    if (current.x == 0) {
                        break;
                    } else if (current.y == localMaze.size() - 1) {
                        break;
                    }

                    first = { current.x - 1, current.y };
                    second = { current.x, current.y + 1 };

                    // west
                    if (localMaze[first.y][first.x] != '-' && localMaze[first.y][first.x] != 'F' && localMaze[first.y][first.x] != 'L') {
                        break;
                    }

                    // south 
                    if (localMaze[second.y][second.x] != '|' && localMaze[second.y][second.x] != 'J' && localMaze[second.y][second.x] != 'L') {
                        break;
                    }
                } else if (pipeType == 'F') { // south and east
                    if (current.x == localMaze[current.y].size() - 1 || current.y == localMaze.size() - 1) {
                        break;
                    }

                    first = { current.x + 1, current.y };
                    second = { current.x, current.y + 1 };

                    // east
                    if (localMaze[first.y][first.x] != '-' && localMaze[first.y][first.x] != 'J' && localMaze[first.y][first.x] != '7') {
                        break;
                    }

                    // south 
                    if (localMaze[second.y][second.x] != '|' && localMaze[second.y][second.x] != 'J' && localMaze[second.y][second.x] != 'L') {
                        break;
                    }
                } else {
                    // out of bounds
                    break;
                }

                // compatible, move, never go back to previous
                visited.insert(current);
                distance++;                
                
                if (visited.find(first) == visited.end()) {
                    current = first;
                } else if (visited.find(second) == visited.end()) {
                    current = second;
                } else {
                    if (first == start || second == start) {
                        success = true;
                    }
                    break;
                }
            }

            if (success) {
                int total = handleLoop(localMaze, visited);
                std::cout << "Total inner loops tiles: " << total << std::endl;
            }
        }
    }

    return 0;
}

int main() {
    first();
    second();
}


