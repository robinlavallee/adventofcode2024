
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

unsigned long long findHash(std::string& token) {
    unsigned long long hash = 0;
    for (int i = 0; i < token.size(); i++) {
        hash += token[i];
        hash *= 17;
        hash %= 256;
    }

    return hash;
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::string line;
        getline(newfile, line);

        line += ',';

        unsigned long long sum = 0;
        std::string token;
        while (line.find(',') != std::string::npos) {
            token = line.substr(0, line.find(','));

            unsigned long long hash = findHash(token);
            sum += hash;

            line.erase(0, line.find(',') + 1);
        }

        std::cout << sum << std::endl;



        newfile.close();
    }

    return 0;
}


int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;
        getline(newfile, line);

        line += ',';

        struct Box {
            std::string label;
            int focalLength;

            bool operator==(const std::string& label) const {
                return this->label == label;
            }
        };

        std::map<int, std::list<Box>> boxes;

        while (line.find(',') != std::string::npos) {
            std::string token = line.substr(0, line.find(','));

            // token is separated by a = or +
            bool add=true;
            std::string label;
            size_t separator = token.find('=');
            if (separator != std::string::npos) {
                label = token.substr(0, separator);
            } else {
                separator = token.find('-');
                label = token.substr(0, separator);
                add = false;
            }

            int focalLength = 0;
            if (add) {
                std::string focalLengthStr = token.substr(separator + 1);
                focalLength = std::stoi(focalLengthStr);
            }

            int boxNumber = findHash(label);
            auto boxIt = boxes.find(boxNumber);
            if (!add) {
                if (boxIt != boxes.end()) {
                    auto boxItemIt = std::find(boxIt->second.begin(), boxIt->second.end(), label);
                    if (boxItemIt != boxIt->second.end()) {
                        boxIt->second.erase(boxItemIt);
                    }
                }
            } else {
                if (boxIt == boxes.end()) {
                    std::list<Box> boxList = {Box{label, focalLength}};
                    boxes[boxNumber] = boxList;
                } else {
                    // add to the end or replace the label if it exists
                    auto boxItemIt = std::find(boxIt->second.begin(), boxIt->second.end(), label);
                    if (boxItemIt != boxIt->second.end()) {
                        boxItemIt->focalLength = focalLength;
                    } else {
                        boxIt->second.push_back(Box{label, focalLength});
                    }
                }
            }

            line.erase(0, line.find(',') + 1);
        }

        int total = 0;
        for (auto& box : boxes) {
            int slot=0;
            for (auto& boxItem : box.second) {
                slot++;
                int boxPower = (box.first+1) * slot * boxItem.focalLength;

                std::cout << boxItem.label << " " << box.first+1 << " " << slot << " " << boxItem.focalLength << " " << boxPower << std::endl;
                total += boxPower;                
            }
        }

        std::cout << total << std::endl;

        newfile.close();
    }

    return 0;
}

int main() {
    first();
    second();
}


