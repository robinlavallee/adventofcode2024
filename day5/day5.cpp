
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

unsigned stou(std::string const& str, size_t* idx = 0, int base = 10) {
    unsigned long result = std::stoul(str, idx, base);
    if (result > std::numeric_limits<unsigned>::max()) {
        throw std::out_of_range("stou");
    }
    return result;
}

struct RangeMap {
    unsigned long destination;
    unsigned long source;
    unsigned long length;
};

struct UsageMap {
    std::vector<RangeMap> maps;

    unsigned long map(unsigned long source) const; // return destination 
};

unsigned long UsageMap::map(unsigned long source) const {
    for (auto& map : maps) {
        if (source >= map.source && source <= map.source + map.length) {
            return map.destination + (source - map.source);
        }
    }
    return source;
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
        std::vector<unsigned long> seeds;
        unsigned long space = line.find(" ");
        while (space != std::string::npos) {
            std::string number = line.substr(0, space);
            seeds.push_back(stou(number));
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
            map.destination = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = stou(number);
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
            map.destination = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = stou(number);
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
            map.destination = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = stou(number);
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
            map.destination = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = stou(number);
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
            map.destination = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = stou(number);
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
            map.destination = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = stou(number);
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
            map.destination = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.source = stou(number);
            line = line.substr(space + 1);
            space = line.find(" ");
            number = line.substr(0, space);
            map.length = stou(number);
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
        for (auto& seed: seeds) {
            unsigned long location = seed;
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

    return 0;
}

int main() {
    first();
    second();
}


