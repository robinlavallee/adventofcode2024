
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>


struct record {
    int blue = 0;
    int red = 0;
    int green = 0;
};

using game = std::list<record>;

// parse a string like 1 red, 2 green, 6 blue
record parse_record(std::string line) {
    record r;
    int separator = line.find(", ");
    if (separator == std::string::npos) {
        separator = line.length();
    }
    std::string part = line.substr(0, separator);
    while (part.length() > 0) {
        int space = part.find(" ");
        std::string number = part.substr(0, space);
        std::string color = part.substr(space + 1);
        if (color == "blue") {
            r.blue = std::stoi(number);
        } else if (color == "red") {
            r.red = std::stoi(number);
        } else if (color == "green") {
            r.green = std::stoi(number);
        }
        
        if (separator + 2 >= line.length()) {
            break;
        }
        line = line.substr(separator + 2);

        separator = line.find(", ");
        if (separator == std::string::npos) {
            separator = line.length();
        }
        part = line.substr(0, separator);
    }

    return r;
}


int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;

        std::vector<game> games;

        while(getline(newfile, line)) {
            // parse line in the following format: Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
            game g;

            // find the colon and split string
            int colon = line.find(": ");
            std::string game = line.substr(0, colon);
            std::string rest = line.substr(colon + 2); //  3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green

            // split the string by each semi-colon part
            int separator = rest.find(";");
            if (separator == std::string::npos) {
                separator = rest.length();
            }
            
            std::string part = rest.substr(0, separator); // 3 blue, 4 red
            while (part.length() > 0) {
                record r = parse_record(part);
                g.push_back(r);

                if (separator + 2 >= rest.length()) {
                    break;
                }
                rest = rest.substr(separator + 2); // 1 red, 2 green, 6 blue; 2 green
                
                separator = rest.find("; ");
                if (separator == std::string::npos) {
                    separator = line.length();
                } 
                part = rest.substr(0, separator);
            }

            games.push_back(g);
        }

        int maxRed = 12;
        int maxGreen = 13;
        int maxBlue = 14;

        int sumPossible = 0;

        for (int i = 0; i < games.size(); i++) {
            bool possible = true;
            for (auto& record : games[i]) {
                if (record.red > maxRed || record.green > maxGreen || record.blue > maxBlue) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                sumPossible += (i + 1); // sum of IDs
            }
        }

        printf("Sum: %d\n", sumPossible);

    }
    
    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;

        std::vector<game> games;

        while(getline(newfile, line)) {
            // parse line in the following format: Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
            game g;

            // find the colon and split string
            int colon = line.find(": ");
            std::string game = line.substr(0, colon);
            std::string rest = line.substr(colon + 2); //  3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green

            // split the string by each semi-colon part
            int separator = rest.find(";");
            if (separator == std::string::npos) {
                separator = rest.length();
            }
            
            std::string part = rest.substr(0, separator); // 3 blue, 4 red
            while (part.length() > 0) {
                record r = parse_record(part);
                g.push_back(r);

                if (separator + 2 >= rest.length()) {
                    break;
                }
                rest = rest.substr(separator + 2); // 1 red, 2 green, 6 blue; 2 green
                
                separator = rest.find("; ");
                if (separator == std::string::npos) {
                    separator = line.length();
                } 
                part = rest.substr(0, separator);
            }

            games.push_back(g);
        }

        int sumPossible = 0;

        for (int i = 0; i < games.size(); i++) {
            int power = 0;
            int maxRed = 0;
            int maxGreen = 0;
            int maxBlue = 0;

            for (auto& record : games[i]) {
                maxRed = std::max(maxRed, record.red);
                maxGreen = std::max(maxGreen, record.green);
                maxBlue = std::max(maxBlue, record.blue);
            }
            power = maxRed * maxGreen * maxBlue;
            sumPossible += power;
        }

        printf("Sum: %d\n", sumPossible);

    }
    return 0;
}

int main() {
    first();
    second();
}


