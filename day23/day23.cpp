
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

int solveLongest(std::list<Point>& path, std::vector<std::string>& maze, Point end, bool canClimb) {

    std::list<Point> candidates;
    while (true) {
        Point current = path.back();
        if (current == end) {
            return path.size() - 1;
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
            path.push_back(candidates.front());
            maze[candidates.front().y][candidates.front().x] = 'O';
            candidates.pop_front();
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
        auto newPath = path;

        newPath.push_back(candidate);
        newMaze[candidate.y][candidate.x] = 'O';

        longest = std::max(longest, solveLongest(newPath, newMaze, end, canClimb));
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
        std::list<Point> path;
        while (getline(newfile, line)) {
            maze.push_back(line);

            if (first) {
                path.push_back({(int)line.find('.'), 0});
                maze[0][line.find('.')] = 'O';
                first = false;
            }
        }

        Point end = {maze[maze.size() - 1].find('.'), maze.size() - 1};
        int longest = solveLongest(path, maze, end, false);
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
        std::list<Point> path;
        while (getline(newfile, line)) {
            maze.push_back(line);

            if (first) {
                path.push_back({(int)line.find('.'), 0});
                maze[0][line.find('.')] = 'O';
                first = false;
            }
        }

        Point end = {maze[maze.size() - 1].find('.'), maze.size() - 1};
        int longest = solveLongest(path, maze, end, true);
        std::cout << longest << std::endl;

        newfile.close();
    }

    return 0;
}

int main() {
    first();
    second();
}
