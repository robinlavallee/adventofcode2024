
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

struct Point {
    int x, y;

    bool operator<(const Point& other) const {
        if (x < other.x) {
            return true;
        } else if (x > other.x) {
            return false;
        } else if (y < other.y) {
            return true;
        } else if (y > other.y) {
            return false;
        } else {
            return false;
        }
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

int solveLongest(Point current, int length, std::vector<std::string>& maze, Point end, bool canClimb) {

    std::list<Point> candidates;
    while (true) {
        if (current == end) {
            return length;
        }

        char left = current.x > 0 ? maze[current.y][current.x - 1] : '#';
        bool canGoLeft = left == '.' || left == '<' || ((left == '>' || left == '^' || left == 'v') && canClimb);

        char right = current.x < maze[0].size() - 1 ? maze[current.y][current.x + 1] : '#';
        bool canGoRight = right == '.' || right == '>' || ((right == '<' || right == '^' || right == 'v') && canClimb);
        
        char up = current.y > 0 ? maze[current.y - 1][current.x] : '#';
        bool canGoUp = up == '.' || up == '^' || ((up == '<' || up == '>' || up == 'v') && canClimb);

        char down = current.y < maze.size() - 1 ? maze[current.y + 1][current.x] : '#';
        bool canGoDown = down == '.' || down == 'v' || ((down == '<' || down == '>' || down == '^') && canClimb);

        if (canGoLeft) {
            candidates.push_back({current.x - 1, current.y});
        }
        if (canGoRight) {
            candidates.push_back({current.x + 1, current.y});
        }
        
        if (canGoUp) {
            candidates.push_back({current.x, current.y - 1});
        }
        
        if (canGoDown) {
            candidates.push_back({current.x, current.y + 1});
        }

        if (candidates.size() == 1) {
            current = candidates.front();
            length++;
            maze[current.y][current.x] = 'O';
            candidates.clear();
        } else if (candidates.size() > 1) {
            break;
        } else if (candidates.size() == 0) {
            return -1; // invalid, got stuck
        }
    } 

    // multiple paths! try them all
    int longest = 0;
    for (auto& candidate : candidates) {
        auto newMaze = maze;
        newMaze[candidate.y][candidate.x] = 'O';
        longest = std::max(longest, solveLongest(candidate, length+1, newMaze, end, canClimb));
    }

    return longest;
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::vector<std::string> maze;

        std::string line;
        bool first = true;
        Point start;
        while (getline(newfile, line)) {
            maze.push_back(line);

            if (first) {
                start = {(int)line.find('.'), 0};
                maze[0][line.find('.')] = 'O';
                first = false;
            }
        }

        Point end = {maze[maze.size() - 1].find('.'), maze.size() - 1};
        int longest = solveLongest(start, 0, maze, end, false);
        std::cout << longest << std::endl;

        newfile.close();
    }

    return 0;
}


int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::vector<std::string> maze;

        std::string line;
        bool first = true;
        Point start;
        while (getline(newfile, line)) {
            maze.push_back(line);

            if (first) {
                start = { (int)line.find('.'), 0 };
                maze[0][line.find('.')] = 'O';
                first = false;
            }
        }

        Point end = {maze[maze.size() - 1].find('.'), maze.size() - 1};
        int longest = solveLongest(start, 0, maze, end, true);
        std::cout << longest << std::endl;

        newfile.close();
    }

    return 0;
}

int main() {
    first();
    second();
}
