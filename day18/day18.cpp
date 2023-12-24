
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

struct Point {
    int x;
    int y;

    bool operator<(const Point& other) const {
        if (y < other.y) {
            return true;
        } else if (y == other.y) {
            return x < other.x;
        } else {
            return false;
        }
    }
};	

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;
        Point topLeft = {0, 0};
        Point bottomRight = {0, 0};
        Point current = { 0, 0 };
        while (getline(newfile, line)) {
            // R 6 (#70c710)

            char direction = line[0];
            int steps = std::stoi(line.substr(2, line.length() - 2));

            if (direction == 'U') {
                current.y -= steps;
            } else if (direction == 'D') {
                current.y += steps;
            } else if (direction == 'L') {
                current.x -= steps;
            } else if (direction == 'R') {
                current.x += steps;
            }

            topLeft.x = std::min(topLeft.x, current.x);
            topLeft.y = std::min(topLeft.y, current.y);

            bottomRight.x = std::max(bottomRight.x, current.x);
            bottomRight.y = std::max(bottomRight.y, current.y);
        }

        Point origin = {0 - topLeft.x, 0 - topLeft.y};
        int width = bottomRight.x - topLeft.x + 1;
        int height = bottomRight.y - topLeft.y + 1;

        current = origin;
        std::vector<std::string> grid(height, std::string(width, '.'));
        grid[current.y][current.x] = '#';

        newfile.clear();
        newfile.seekg(0, std::ios::beg);
        while (getline(newfile, line)) {
            // R 6 (#70c710)
            char direction = line[0];
            int steps = std::stoi(line.substr(2, line.length() - 2));

            if (direction == 'U') {
                for (int i = 0; i < steps; i++) {
                    current.y--;
                    grid[current.y][current.x] = '#';
                }
            } else if (direction == 'D') {
                for (int i = 0; i < steps; i++) {
                    current.y++;
                    grid[current.y][current.x] = '#';
                }
            } else if (direction == 'L') {
                for (int i = 0; i < steps; i++) {
                    current.x--;
                    grid[current.y][current.x] = '#';
                }
            } else if (direction == 'R') {
                for (int i = 0; i < steps; i++) {
                    current.x++;
                    grid[current.y][current.x] = '#';
                }
            }
        }       
        newfile.close();

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cout << grid[i][j];
            }
            std::cout << std::endl;
        }

        // flood fill the outside and let's see what's left

        std::set<Point> toVisit;
        for (int i = 0; i < width; i++) {
            if (grid[0][i] == '.') {
                toVisit.insert({i, 0});
            }

            if (grid[height - 1][i] == '.') {
                toVisit.insert({i, height - 1});
            }
        }

        for (int i = 0; i < height; i++) {
            if (grid[i][0] == '.') {
                toVisit.insert({0, i});
            }

            if (grid[i][width - 1] == '.') {
                toVisit.insert({width - 1, i});
            }
        }

        while (!toVisit.empty()) {
            Point current = *toVisit.begin();
            toVisit.erase(toVisit.begin());

            if (current.x < 0 || current.x >= width || current.y < 0 || current.y >= height) {
                continue;
            }

            if (grid[current.y][current.x] == '.') {
                grid[current.y][current.x] = 'O';
                toVisit.insert({current.x - 1, current.y});
                toVisit.insert({current.x + 1, current.y});
                toVisit.insert({current.x, current.y - 1});
                toVisit.insert({current.x, current.y + 1});
            }
        }

        // convert all insides to #
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++){
                if (grid[i][j] == '.') {
                    grid[i][j] = '#';
                }
            }
        }

        // count all #
        int count = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0;j < width; j++) {
                if (grid[i][j] == '#') {
                    count++;
                }
            }
        }

        std::cout << count << std::endl;
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


