
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

int handleLoop(std::vector<std::string> maze, std::set<Point> loopMembers) {
    // We will expand the maze and turn each tile into a 2x2 tile so that we can reason about what is inside and what is outside

    std::vector<std::string> expandedMaze;
    expandedMaze.resize(maze.size() * 2);

    int numInside = 0;
    int numCols = maze[0].size();
    for (int j = 0; j < maze.size(); j++) {
        for (int i = 0; i < maze[j].size(); i++) {
            if (i == 0) {
                expandedMaze[j*2].resize(numCols * 2);
                expandedMaze[j*2+1].resize(numCols * 2);
            }

            if (i == 0 && j == 0) { // special case for starting point
                expandedMaze[0][0] = 'O';
            } else {
                if (i == 0) {
                    expandedMaze[j*2][i*2] = expandedMaze[j*2-1][i*2];
                } else {
                    expandedMaze[j*2][i*2] = expandedMaze[j*2][i*2-1];
                }
            }

            // now it depends on the type of the tile and if it's part of the loop
            bool isMember = loopMembers.find({ i, j }) != loopMembers.end();

            char opposite = expandedMaze[j*2][i*2] == 'O' ? 'I' : 'O';

            if (!isMember) {
                expandedMaze[j*2][i*2+1] = expandedMaze[j*2][i*2];
                expandedMaze[j*2+1][i*2] = expandedMaze[j*2][i*2];
                expandedMaze[j*2+1][i*2+1] = expandedMaze[j*2][i*2];

                if (expandedMaze[j*2][i*2] == 'I') {
                    numInside++;
                }
            } else {
                // Let's look at the type
                char pipeType = maze[j][i];
                switch (pipeType) {
                    case '-':
                        expandedMaze[j*2][i*2+1] = expandedMaze[j*2][i*2];
                        expandedMaze[j*2+1][i*2] = opposite;
                        expandedMaze[j*2+1][i*2+1] = opposite;
                    break;
                    case '|':
                        expandedMaze[j*2][i*2+1] = opposite;
                        expandedMaze[j*2+1][i*2] = expandedMaze[j*2][i*2];
                        expandedMaze[j*2+1][i*2+1] = opposite;
                    break;
                    case 'L':
                        expandedMaze[j*2][i*2+1] = opposite;
                        expandedMaze[j*2+1][i*2] = expandedMaze[j*2][i*2];;
                        expandedMaze[j*2+1][i*2+1] = expandedMaze[j*2][i*2];
                    break;
                    case 'J':
                        expandedMaze[j*2][i*2+1] = opposite;
                        expandedMaze[j*2+1][i*2] = opposite;
                        expandedMaze[j*2+1][i*2+1] = opposite;
                    break;
                    case '7':
                        expandedMaze[j*2][i*2+1] = expandedMaze[j*2][i*2];
                        expandedMaze[j*2+1][i*2] = opposite;
                        expandedMaze[j*2+1][i*2+1] = expandedMaze[j*2][i*2];
                    break;
                    case 'F':
                        expandedMaze[j*2][i*2+1] = expandedMaze[j*2][i*2];
                        expandedMaze[j*2+1][i*2] = expandedMaze[j*2][i*2];
                        expandedMaze[j*2+1][i*2+1] = opposite;
                    break;
                }
            }
        }
    }

    return numInside;
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


