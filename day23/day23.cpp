
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

int solveLongest(std::list<Point>& path, std::vector<std::string>& maze, Point end) {

    std::list<Point> candidates;
    while (true) {
        Point current = path.back();
        if (current == end) {
            return path.size() - 1;
        }

        if (current.x > 0 && (maze[current.y][current.x - 1] == '.' || maze[current.y][current.x - 1] == '<')) {
            candidates.push_back({current.x - 1, current.y});
        }
        if (current.x < maze[0].size() - 1 && (maze[current.y][current.x + 1] == '.' || maze[current.y][current.x + 1] == '>')) {
            candidates.push_back({current.x + 1, current.y});
        }
        if (current.y > 0 && (maze[current.y - 1][current.x] == '.' || maze[current.y - 1][current.x] == '^')) {
            candidates.push_back({current.x, current.y - 1});
        }
        if (current.y < maze.size() - 1 && (maze[current.y + 1][current.x] == '.' || maze[current.y + 1][current.x] == 'v')) {
            candidates.push_back({current.x, current.y + 1});
        }

        if (candidates.size() == 1) {
            path.push_back(candidates.front());
            maze[candidates.front().y][candidates.front().x] = 'O';
            candidates.pop_front();
        } else if (candidates.size() > 1) {
            break;
        }
    } 

    // multiple paths! try them all
    int longest = 0;
    for (auto& candidate : candidates) {
        auto newMaze = maze;
        auto newPath = path;

        newPath.push_back(candidate);
        newMaze[candidate.y][candidate.x] = 'O';

        longest = std::max(longest, solveLongest(newPath, newMaze, end));
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
        int longest = solveLongest(path, maze, end);
        std::cout << longest << std::endl;

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
