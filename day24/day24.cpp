
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

struct Formula {
    double m;
    double b;
};

struct Hailstone {
    Point p;
    Formula f;
};

std::vector<Hailstone> stones;

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::string line;
        while (getline(newfile, line)) {
            // 19, 13, 30 @ -2,  1, -2

            auto at = line.find('@');
            auto left = line.substr(0, at);
            auto right = line.substr(at + 2);

            left += ",";
            right += ",";

            auto comma = left.find(",");
            auto x = std::stoi(left.substr(0, comma));
            left = left.substr(comma + 1);
            comma = left.find(",");
            auto y = std::stoi(left.substr(0, comma));
            left = left.substr(comma + 1);
            comma = left.find(",");
            auto z = std::stoi(left.substr(0, comma));

            Hailstone stone;
            stone.p = {x, y};

            comma = right.find(",");
            auto vx = std::stoi(right.substr(0, comma));
            right = right.substr(comma + 1);
            comma = right.find(",");
            auto vy = std::stoi(right.substr(0, comma));
            right = right.substr(comma + 1);
            comma = right.find(",");
            auto vz = std::stoi(right.substr(0, comma));

            // y = mx + b
            // y - b = mx
            // (y - b) / x = m

            stone.f.m = (double)vy / (double)vx;
            stone.f.b = (double)y - stone.f.m * (double)x;

            std::cout << "m=" << stone.f.m << " " << "b=" << stone.f.b << std::endl;

            stones.push_back(stone);
        }

        double min = 7;
        double max = 27;

        unsigned int count = 0;
        for (int i = 0; i < stones.size(); i++) {
            for (int j = i + 1; j < stones.size(); j++) {
                // find intersection point
                // y = m1x + b1
                // y = m2x + b2

                double left = stones[i].f.b - stones[j].f.b;
                double right = stones[j].f.m - stones[i].f.m;
                if (abs(right) < 0.0000001) {
                    continue;
                }
                
                double x = left / right;
                double y = stones[i].f.m * x + stones[i].f.b;

                std::cout << "Stones " << i << " and " << j << " intersect at (" << x << ", " << y << ")" << std::endl;

                if (x >= min && x <= max && y >= min && y <= max) {
                    std::cout << "Within test area" << std::endl;
                    count++;
                } else {
                    std::cout << "Outside test area" << std::endl;
                }
            }
        }

        std::cout << count << std::endl;

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
