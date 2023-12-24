
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


