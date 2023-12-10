
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

void replace(std::string& str,
    const std::string& oldStr,
    const std::string& newStr)
{
    std::string::size_type pos = 0u;
    while ((pos = str.find(oldStr, pos)) != std::string::npos) {
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
}

/*
Time:        54     94     65     92
Distance:   302   1476   1029   1404
*/
struct RaceInfo {
    unsigned long long time;
    unsigned long long  distance;
};

int first() {
    RaceInfo races[4] = {
        {54, 302},
        {94, 1476},
        {65, 1029},
        {92, 1404}
    };

    unsigned long long totalNumWays = 1;

    for (auto& race: races) {
        unsigned long long numWays = 0;
        for (int i = 0; i < race.time; ++i) {
            unsigned long long distance = (race.time - i) * i;
            if (distance >= race.distance) {
                numWays++;
            }
        }

        totalNumWays *= numWays;
    }

    std::cout << totalNumWays << std::endl;

    return 0;
}

int second() {
    RaceInfo race;
    race.time = 54946592ULL;
    race.distance = 302147610291404ULL;

    unsigned long long numWays = 0;
    for (unsigned long long i = 0; i < race.time; ++i) {
        unsigned long long distance = (race.time - i) * i;
        if (distance >= race.distance) {
            numWays++;
        }
    }

    std::cout << numWays << std::endl;

    return 0;
}

int main() {
    first();
    second();
}


