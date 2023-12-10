
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

struct RangeMap {
    unsigned long long source;
    unsigned long long destination;
    unsigned long long length;
};

struct Range {
    unsigned long long location;
    unsigned long long length;

    unsigned long long end() const {
        return location + length;
    }

    bool isBeginningBefore(RangeMap const& map) const {
        return location < map.source;
    }

    bool isBeginningInside(RangeMap const& map) const {
        return location >= map.source && location < map.source + map.length;
    }

    bool isBeginningAfter(RangeMap const& map) const {
        return location >= map.source + map.length;
    }

    bool isEndBefore(RangeMap const& map) const {
        return end() < map.source;
    }

    bool isEndInside(RangeMap const& map) const {
        return end() >= map.source && end() < map.source + map.length;
    }

    bool isEndAfter(RangeMap const& map) const {
        return end() >= map.source + map.length;
    }
};

struct UsageMap {
    std::vector<RangeMap> maps;

    unsigned long long map(unsigned long long source) const; // return destination 
};

unsigned long long UsageMap::map(unsigned long long source) const {
    for (auto& map : maps) {
        if (source >= map.source && source <= map.source + map.length) {
            return map.destination + (source - map.source);
        }
    }
    return source;
}

void transform(std::vector<Range>& seedsRanges, UsageMap& usageMap) {
    std::vector<Range> newSeedsRanges;
    for (auto& map : usageMap.maps) {
        for (size_t i = 0; i < seedsRanges.size(); ++i) {
            // Case 1 - Seed start before, ends inside
            if (seedsRanges[i].isBeginningBefore(map) && seedsRanges[i].isEndInside(map)) {
                Range newRange;
                newRange.location = map.destination + (map.source - seedsRanges[i].location);
                newRange.length = seedsRanges[i].length - (map.source - seedsRanges[i].location);
                newSeedsRanges.push_back(newRange);

                if (newRange.length == 0) {
                    int k;
                    k = 2;
                }

                seedsRanges[i].length = map.source - seedsRanges[i].location;
                if (seedsRanges[i].length == 0) {
                    int k;
                    k = 2;
                }

            }
            // Case 2 - Seed start before, ends after
            else if (seedsRanges[i].isBeginningBefore(map) && seedsRanges[i].isEndAfter(map)) {
                Range newRange;
                newRange.location = map.destination;
                newRange.length = map.length;
                newSeedsRanges.push_back(newRange);

                if (newRange.length == 0) {
                    int k;
                    k = 2;
                }

                // Now we need to figure out the part after
                Range newRangeAfter;
                newRangeAfter.location = map.source + map.length;
                newRangeAfter.length = seedsRanges[i].length - (map.source + map.length - seedsRanges[i].location);

                if (newRangeAfter.length > 0) {
                    seedsRanges.push_back(newRangeAfter);
                }

                // And the seed before is reduced
                seedsRanges[i].length = map.source - seedsRanges[i].location;
                if (seedsRanges[i].length == 0) {
                    int k;
                    k = 2;
                }
            }
            // Case 3 - Seed starts inside, ends inside
            else if (seedsRanges[i].isBeginningInside(map) && seedsRanges[i].isEndInside(map)) {
                seedsRanges[i].location = map.destination + (seedsRanges[i].location - map.source);
            }
            // Case 4 - Seeds start inside, ends after
            else if (seedsRanges[i].isBeginningInside(map) && seedsRanges[i].isEndAfter(map)) {
                Range newRange;
                newRange.location = map.destination + (seedsRanges[i].location - map.source);
                newRange.length = map.source + map.length - seedsRanges[i].location;
                newSeedsRanges.push_back(newRange);

                if (newRange.length == 0) {
                    int k;
                    k = 2;
                }

                unsigned long long newLocation = map.source + map.length;
                seedsRanges[i].length = seedsRanges[i].location + seedsRanges[i].length - newLocation;
                seedsRanges[i].location = newLocation;


            }
        }
    }

    // push back whatever left-over
    for (auto& seedRange : seedsRanges) {
        if (seedRange.length > 0) {
            newSeedsRanges.push_back(seedRange);
        }
    }

    seedsRanges = newSeedsRanges;
}


void test1() {
    Range seed;
    seed.location = 30;
    seed.length = 20;

    RangeMap map;
    map.destination = 1000;
    map.source = 35;
    map.length = 5000;

    std::vector<Range> rangeSeeds;
    rangeSeeds.push_back(seed);
    UsageMap usageMap;
    usageMap.maps.push_back(map);
    transform(rangeSeeds, usageMap);

    if (rangeSeeds.size() != 2) {
        std::cout << "Test 1 failed" << std::endl;
    } else {
        if (rangeSeeds[1].location != 30 || rangeSeeds[1].length != 5) {
            std::cout << "Test 1 failed" << std::endl;
        }
        else if (rangeSeeds[0].location != 1005 || rangeSeeds[0].length != 15) {
            std::cout << "Test 1 failed" << std::endl;
        }
        else {
            std::cout << "Test 1 passed" << std::endl;
        }
    }
}

void test2() {
    Range seed;
    seed.location = 30;
    seed.length = 150;

    RangeMap map;
    map.destination = 1000;
    map.source = 35;
    map.length = 100;

    std::vector<Range> rangeSeeds;
    rangeSeeds.push_back(seed);
    UsageMap usageMap;
    usageMap.maps.push_back(map);
    transform(rangeSeeds, usageMap);

    if (rangeSeeds.size() != 3) {
        std::cout << "Test 2 failed" << std::endl;
    } else {
        if (rangeSeeds[2].location != 30 || rangeSeeds[2].length != 5) {
            std::cout << "Test 2 failed" << std::endl;
        }
        else if (rangeSeeds[1].location != 135 || rangeSeeds[1].length != 45) {
            std::cout << "Test 2 failed" << std::endl;
        } else if (rangeSeeds[0].location != 1000 || rangeSeeds[0].length != 100) {
            std::cout << "Test 2 failed" << std::endl;
        }
        else {
            std::cout << "Test 2 passed" << std::endl;
        }
    }
}

void test3() {
    Range seed;
    seed.location = 30;
    seed.length = 50;

    RangeMap map;
    map.destination = 1000;
    map.source = 20;
    map.length = 100;

    std::vector<Range> rangeSeeds;
    rangeSeeds.push_back(seed);
    UsageMap usageMap;
    usageMap.maps.push_back(map);
    transform(rangeSeeds, usageMap);

    if (rangeSeeds.size() != 1) {
        std::cout << "Test 3 failed" << std::endl;
    } else {
        if (rangeSeeds[0].location != 1010 || rangeSeeds[0].length != 50) {
            std::cout << "Test 3 failed" << std::endl;
        } else {
            std::cout << "Test 3 passed" << std::endl;
        }
    }
}

void test4() {
    Range seed;
    seed.location = 30;
    seed.length = 100;

    RangeMap map;
    map.destination = 1000;
    map.source = 20;
    map.length = 50;

    std::vector<Range> rangeSeeds;
    rangeSeeds.push_back(seed);
    UsageMap usageMap;
    usageMap.maps.push_back(map);
    transform(rangeSeeds, usageMap);

    if (rangeSeeds.size() != 2) {
        std::cout << "Test 4 failed" << std::endl;
    } else {
        if (rangeSeeds[0].location != 1010 || rangeSeeds[0].length != 40) {
            std::cout << "Test 4 failed" << std::endl;
        } else if (rangeSeeds[1].location != 70 || rangeSeeds[1].length != 60) {
            std::cout << "Test 4 failed" << std::endl;
        } else {
            std::cout << "Test 4 passed" << std::endl;
        }
    }
}

// start inside, ends right on it
void test5() {
    Range seed;
    seed.location = 10;
    seed.length = 35;

    RangeMap map;
    map.destination = 1000;
    map.source = 5; 
    map.length = 40;

    std::vector<Range> rangeSeeds;
    rangeSeeds.push_back(seed);
    UsageMap usageMap;
    usageMap.maps.push_back(map);
    transform(rangeSeeds, usageMap);

    if (rangeSeeds.size() != 1) {
        std::cout << "Test 5 failed" << std::endl;
    } else {
        if (rangeSeeds[0].location != 1005 || rangeSeeds[0].length != 35) {
            std::cout << "Test 5 failed" << std::endl;
        } else {
            std::cout << "Test 5 passed" << std::endl;
        }
    }
}

// start before, ends right on it
void test6() {
    Range seed;
    seed.location = 2;
    seed.length = 43;

    RangeMap map;
    map.destination = 1000;
    map.source = 5; 
    map.length = 40;

    std::vector<Range> rangeSeeds;
    rangeSeeds.push_back(seed);
    UsageMap usageMap;
    usageMap.maps.push_back(map);
    transform(rangeSeeds, usageMap);

    if (rangeSeeds.size() != 2) {
        std::cout << "Test 6 failed" << std::endl;
    } else {
        if (rangeSeeds[0].location != 1000 || rangeSeeds[0].length != 40) {
            std::cout << "Test 6 failed" << std::endl;
        } else if (rangeSeeds[1].location != 2 || rangeSeeds[1].length != 3) {
            std::cout << "Test 6 failed" << std::endl;
        } else {
            std::cout << "Test 6 passed" << std::endl;
        }
    }
}

// exact overlap
void test7() {
    Range seed;
    seed.location = 10;
    seed.length = 20;

    RangeMap map;
    map.destination = 1000;
    map.source = 10;
    map.length = 20;

    std::vector<Range> rangeSeeds;
    rangeSeeds.push_back(seed);
    UsageMap usageMap;
    usageMap.maps.push_back(map);
    transform(rangeSeeds, usageMap);

    if (rangeSeeds.size() != 1) {
        std::cout << "Test 7 failed" << std::endl;
    } else {
        if (rangeSeeds[0].location != 1000 || rangeSeeds[0].length != 20) {
            std::cout << "Test 7 failed" << std::endl;
        } else {
            std::cout << "Test 7 passed" << std::endl;
        }
    }
}

// map over multiple seeds
void test8() {
    Range seed1;
    seed1.location = 10;
    seed1.length = 20;

    Range seed2;
    seed2.location = 40;
    seed2.length = 25;

    RangeMap map;
    map.destination = 1000;
    map.source = 5;
    map.length = 4000;

    std::vector<Range> rangeSeeds;
    rangeSeeds.push_back(seed1);
    rangeSeeds.push_back(seed2);
    UsageMap usageMap;
    usageMap.maps.push_back(map);
    transform(rangeSeeds, usageMap);

    if (rangeSeeds.size() != 2) {
        std::cout << "Test 8 failed" << std::endl;
    } else {
        if (rangeSeeds[0].location != 1005 || rangeSeeds[0].length != 20) {
            std::cout << "Test 8 failed" << std::endl;
        } else if (rangeSeeds[1].location != 1035 || rangeSeeds[1].length != 25) {
            std::cout << "Test 8 failed" << std::endl;
        } else {
            std::cout << "Test 8 passed" << std::endl;
        }
    }
}

// seed over multiple maps
void test9() {
    Range seed;
    seed.location = 10;
    seed.length = 100;

    RangeMap map1;
    map1.destination = 1000;
    map1.source = 15;
    map1.length = 40;

    RangeMap map2;
    map2.destination = 2000;
    map2.source = 60;
    map2.length = 20;

    std::vector<Range> rangeSeeds;
    rangeSeeds.push_back(seed);
    UsageMap usageMap;
    usageMap.maps.push_back(map1);
    usageMap.maps.push_back(map2);
    transform(rangeSeeds, usageMap);

    if (rangeSeeds.size() != 5) {
        std::cout << "Test 9 failed" << std::endl;
    } else {
        if (rangeSeeds[2].location != 10 || rangeSeeds[2    ].length != 5) {
            std::cout << "Test 9 failed" << std::endl;
        } else if (rangeSeeds[0].location != 1000 || rangeSeeds[0].length != 40) {
            std::cout << "Test 9 failed" << std::endl;
        } else if (rangeSeeds[3].location != 55 || rangeSeeds[3].length != 5) {
            std::cout << "Test 9 failed" << std::endl;
        } else if (rangeSeeds[1].location != 2000 || rangeSeeds[1].length != 20) {
            std::cout << "Test 9 failed" << std::endl;
        } else if (rangeSeeds[4].location != 80 || rangeSeeds[4].length != 30) {
            std::cout << "Test 9 failed" << std::endl;
        } else {
            std::cout << "Test 9 passed" << std::endl;
        }
    }
}
                

void tests() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        // format is like:
        /*
 seeds: 79 14 55 13

 seed-to-soil map:
 50 98 2
 52 50 48

 soil-to-fertilizer map:
 0 15 37
 37 52 2
 39 0 15

 fertilizer-to-water map:
 0 15 37

 water-to-light map:
 0 15 37

 light-to-temperature map:
 0 15 37

 temperature-to-humidity map:
 0 15 37

 humidity-to-location map:
 0 15 37
        */

        // parse seeds
        std::string line;
        getline(newfile, line);
        line += " ";
        replace(line, "seeds: ", "");
        std::vector<unsigned long long> seeds;
        unsigned long space = line.find(" ");
        while (space != std::string::npos) {
            std::string number = line.substr(0, space);
            seeds.push_back(std::stoull(number));
            line = line.substr(space + 1);
            space = line.find(" ");
        }

        // parse seed-to-soil map
        getline(newfile, line);
        getline(newfile, line);
        std::vector<RangeMap> seedToSoilMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            seedToSoilMaps.push_back(map);
        }

        // parse soil-to-fertilizer map
        getline(newfile, line);
        std::vector<RangeMap> soilToFertilizerMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            soilToFertilizerMaps.push_back(map);
        }

        // parse fertilizer-to-water map
        getline(newfile, line);
        std::vector<RangeMap> fertilizerToWaterMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            fertilizerToWaterMaps.push_back(map);
        }

        // parse water-to-light map
        getline(newfile, line);
        std::vector<RangeMap> waterToLightMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            waterToLightMaps.push_back(map);
        }

        // parse light-to-temperature map
        getline(newfile, line);
        std::vector<RangeMap> lightToTemperatureMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            lightToTemperatureMaps.push_back(map);
        }

        // parse temperature-to-humidity map
        getline(newfile, line);
        std::vector<RangeMap> temperatureToHumidityMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            temperatureToHumidityMaps.push_back(map);
        }

        // parse humidity-to-location map
        getline(newfile, line);
        std::vector<RangeMap> humidityToLocationMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            humidityToLocationMaps.push_back(map);
        }

        UsageMap allUsages[7];
        allUsages[0].maps = seedToSoilMaps;
        allUsages[1].maps = soilToFertilizerMaps;
        allUsages[2].maps = fertilizerToWaterMaps;
        allUsages[3].maps = waterToLightMaps;
        allUsages[4].maps = lightToTemperatureMaps;
        allUsages[5].maps = temperatureToHumidityMaps;
        allUsages[6].maps = humidityToLocationMaps;

        // now we have all the maps, we can start with the seeds
        unsigned long smallest = UINT_MAX;
        for (auto& seed : seeds) {
            unsigned long long location = seed;
            for (int i = 0; i < 7; i++) {
                location = allUsages[i].map(location);
            }

            if (location < smallest) {
                smallest = location;
            }
            std::cout << location << std::endl;
        }

        std::cout << "Smallest location is " << smallest << std::endl;
    }

    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
       // format is like:
       /*
seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
0 15 37

water-to-light map:
0 15 37

light-to-temperature map:
0 15 37

temperature-to-humidity map:
0 15 37

humidity-to-location map:
0 15 37
       */

        // parse seeds
        std::string line;
        getline(newfile, line);
        line += " ";
        replace(line, "seeds: ", "");
        std::vector<Range> seedsRanges;
        int space = line.find(" ");
        while (space != std::string::npos) {
            Range range;
            std::string number = line.substr(0, space);
            range.location = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            range.length = std::stoull(number);
            seedsRanges.push_back(range);
            line = line.substr(space + 1);
            space = line.find(" ");
        }

        // parse seed-to-soil map
        getline(newfile, line);
        getline(newfile, line);
        std::vector<RangeMap> seedToSoilMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            seedToSoilMaps.push_back(map);
        }

        // parse soil-to-fertilizer map
        getline(newfile, line);
        std::vector<RangeMap> soilToFertilizerMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            soilToFertilizerMaps.push_back(map);
        }

        // parse fertilizer-to-water map
        getline(newfile, line);
        std::vector<RangeMap> fertilizerToWaterMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            fertilizerToWaterMaps.push_back(map);
        }

        // parse water-to-light map
        getline(newfile, line);
        std::vector<RangeMap> waterToLightMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            waterToLightMaps.push_back(map);
        }

        // parse light-to-temperature map
        getline(newfile, line);
        std::vector<RangeMap> lightToTemperatureMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            lightToTemperatureMaps.push_back(map);
        }

        // parse temperature-to-humidity map
        getline(newfile, line);
        std::vector<RangeMap> temperatureToHumidityMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            temperatureToHumidityMaps.push_back(map);
        }

        // parse humidity-to-location map
        getline(newfile, line);
        std::vector<RangeMap> humidityToLocationMaps;
        while (getline(newfile, line)) {
            if (line.length() == 0) {
                break;
            }
            RangeMap map;
            int space = line.find(" ");
            std::string number = line.substr(0, space);
            map.destination = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = std::stoull(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = std::stoull(number);
            humidityToLocationMaps.push_back(map);
        }

        UsageMap allUsages[7];
        allUsages[0].maps = seedToSoilMaps;
        allUsages[1].maps = soilToFertilizerMaps;
        allUsages[2].maps = fertilizerToWaterMaps;
        allUsages[3].maps = waterToLightMaps;
        allUsages[4].maps = lightToTemperatureMaps;
        allUsages[5].maps = temperatureToHumidityMaps;
        allUsages[6].maps = humidityToLocationMaps;

        for (auto& usageMap: allUsages) {
            transform(seedsRanges, usageMap);
        }

        // now find the smallest
        unsigned long long smallest = ULLONG_MAX;
        for (auto& seedRange: seedsRanges) {
            if (seedRange.location < smallest) {
                smallest = seedRange.location;
            }
        }

        std::cout << "Smallest location is " << smallest << std::endl;
    }

    return 0;
}

int main() {
    tests();

    first();
    second();
}


