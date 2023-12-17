
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

struct Space {
    char type;
    bool directions[4] = { false, false, false, false };
};

static const int Up = 0;
static const int Down = 1;
static const int Left = 2;
static const int Right = 3;

struct ActiveLight {
    int x;
    int y;
    int direction;

    bool operator<(const ActiveLight& other) const {
        if (x < other.x) {
            return true;
        } else if (x > other.x) {
            return false;
        } else if (y < other.y) {
            return true;
        } else if (y > other.y) {
            return false;
        } else if (direction < other.direction) {
            return true;
        } else {
            return false;
        }
    }
};

int energize(std::vector<std::vector<Space>> rows, ActiveLight initialLight = { 0, 0, Right }) {
    std::map<ActiveLight, bool> activeLights;
    activeLights.insert({ initialLight, true });
    
    bool veryFirstLight = true;
    while (activeLights.size() > 0) {
        ActiveLight originalLight = activeLights.begin()->first;
        ActiveLight nextLight = originalLight;

        if (!veryFirstLight) {
            if (nextLight.direction == Up) {
                nextLight.y--;
            } else if (nextLight.direction == Down) {
                nextLight.y++;
            } else if (nextLight.direction == Left) {
                nextLight.x--;
            } else if (nextLight.direction == Right) {
                nextLight.x++;
            }
        } else {
            veryFirstLight = false;
        }

        if (nextLight.x < 0 || nextLight.x >= rows[0].size() || nextLight.y < 0 || nextLight.y >= rows.size()) {
            activeLights.erase(activeLights.begin());
            continue;
        }

        Space& nextSpace = rows[nextLight.y][nextLight.x];

        // Now check if we have been there before in that direction
        if (nextSpace.directions[nextLight.direction]) {
            activeLights.erase(activeLights.begin());
            continue;
        }

        // Ok, it's a new space, awesome, note that we have entered from a specific direction
        nextSpace.directions[nextLight.direction] = true;

        // now check what we do next
        // NOTE: currentLight gets invalidated here because we are adding to an active iterator
        if (nextLight.direction == Up) {
            if (nextSpace.type == '/') {
                nextLight.direction = Right;
            } else if (nextSpace.type == '\\') {
                nextLight.direction = Left;
            } else if (nextSpace.type == '-') {
                nextLight.direction = Left;
                ActiveLight newLight = nextLight;
                newLight.direction = Right;
                activeLights[newLight] = true;
                
            }
        } else if (nextLight.direction == Down) {
            if (nextSpace.type == '/') {
                nextLight.direction = Left;
            } else if (nextSpace.type == '\\') {
                nextLight.direction = Right;
            } else if (nextSpace.type == '-') {
                nextLight.direction = Right;
                ActiveLight newLight = nextLight;
                newLight.direction = Left;
                activeLights[newLight] = true;
            }
        } else if (nextLight.direction == Left) {
            if (nextSpace.type == '/') {
                nextLight.direction = Down;
            } else if (nextSpace.type == '\\') {
                nextLight.direction = Up;
            } else if (nextSpace.type == '|') {
                nextLight.direction = Up;
                ActiveLight newLight = nextLight;
                newLight.direction = Down;
                activeLights[newLight] = true;
            }
        } else if (nextLight.direction == Right) {
            if (nextSpace.type == '/') {
                nextLight.direction = Up;
            } else if (nextSpace.type == '\\') {
                nextLight.direction = Down;
            } else if (nextSpace.type == '|') {
                nextLight.direction = Down;
                ActiveLight newLight = nextLight;
                newLight.direction = Up;
                activeLights[newLight] = true;
            }
        }

        activeLights.erase(originalLight);
        activeLights[nextLight] = true;
    }
    
    // count the number of energized light, this will be the number of spaces with any direction set
    int numEnergized = 0;
    for (int j = 0; j < rows.size(); j++) {
        for (int i = 0; i < rows[j].size(); i++) {
            Space& space = rows[j][i];
            if (space.directions[Up] || space.directions[Down] || space.directions[Left] || space.directions[Right]) {
                //std::cout << "#";
                numEnergized++;
            } else {
                //std::cout << ".";
            }
        }
        //std::cout << std::endl;
    }

    return numEnergized;
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::vector<std::vector<Space>> rows;
        std::string line;
        while (getline(newfile, line)) {
            std::vector<Space> row;
            for (int i = 0; i < line.size(); i++) {
                Space space;
                space.type = line[i];
                row.push_back(space);
            }
            rows.push_back(row);
        }

        int numEnergized = energize(rows);
        std::cout << numEnergized << std::endl;

        newfile.close();
    }

    return 0;
}


int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::vector<std::vector<Space>> rows;
        std::string line;
        while (getline(newfile, line)) {
            std::vector<Space> row;
            for (int i = 0; i < line.size(); i++) {
                Space space;
                space.type = line[i];
                row.push_back(space);
            }
            rows.push_back(row);
        }     

        int maxEnergized = 0;
        // try all vertical
        for (int i = 0; i < rows[0].size(); i++) {
            int numEnergized = energize(rows, { i, 0, Down });
            if (numEnergized > maxEnergized) {
                maxEnergized = numEnergized;
            }

            numEnergized = energize(rows, { i, (int)rows.size() - 1, Up });
            if (numEnergized > maxEnergized) {
                maxEnergized = numEnergized;
            }
        }

        // try all horizontal
        for (int j = 0; j < rows.size(); j++) {
            int numEnergized = energize(rows, { 0, j, Right });
            if (numEnergized > maxEnergized) {
                maxEnergized = numEnergized;
            }

            numEnergized = energize(rows, { (int)rows[0].size() - 1, j, Left });
            if (numEnergized > maxEnergized) {
                maxEnergized = numEnergized;
            }
        }

        std::cout << maxEnergized << std::endl;

        newfile.close();
    }

    return 0;
}

int main() {
    first();
    second();
}


