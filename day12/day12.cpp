
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

struct CacheEntry {
    std::string record;
    std::vector<int> numbers;

    bool operator<(const CacheEntry& other) const
    {
        if (record < other.record) {
            return true;
        }

        if (record > other.record) {
            return false;
        }

        if (numbers.size() < other.numbers.size()) {
            return true;
        }

        if (numbers.size() > other.numbers.size()) {
            return false;
        }

        for (int i = 0; i < numbers.size(); ++i) {
            if (numbers[i] < other.numbers[i]) {
                return true;
            }

            if (numbers[i] > other.numbers[i]) {
                return false;
            }
        }

        return false;
    }
};

std::map<CacheEntry, unsigned long long> cache;

unsigned long long computeArrangements(std::string record, std::vector<int> numbers) {
    CacheEntry entry = { record, numbers };
    if (cache.find(entry) != cache.end()) {
        return cache[entry];
    }

    if (numbers.size() == 0) {
        cache[entry] = 0;
        return 0;
    }
    
    int numRequired = 0;
    for (int i = 0; i < numbers.size(); ++i) {
        numRequired += numbers[i];
    }

    numRequired += numbers.size() - 1;
    if (numRequired > record.size()) {
        cache[entry] = 0;
        return 0;
    }

    // ???.### 1,1,3

    // If we want to do 1, then we need to do #. so we can look everywhere and place it, if we see anything else like ##., then it doesn't work, then recurse

    unsigned long long totalArrangements = 0;
    int number = numbers[0];
    for (int i = 0; i < record.size()-number+1; ++i) {

        {
            bool valid = true;
            for (int j = 0; j < number; ++j) {
                if (record[i+j] != '#' && record[i+j] != '?') {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                continue;
            }
        }

        // need to be end of the record string OR a space if not at the end
        if (i + number < record.size()) {
            if (record[i+number] == '#') {
                continue;
            }
        }

        if (i > 0) {
            bool valid=true;
            for (int k = 1; k <= i; ++k) {
                if (record[i-k] == '#') {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                continue;
            }
        }

        if (numbers.size() == 1) {
            if (i + number < record.size()) {
                std::string subRecords = record.substr(i + number);
                bool valid=true;
                for (int i = 0; i < subRecords.size(); ++i) {
                    if (subRecords[i] == '#') {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    totalArrangements++;
                }
            } else {
                totalArrangements++;
            }
        } else { 
            if (i + number + 1 >= record.size()) {
                continue;
            }

            unsigned long long numArrangement = computeArrangements(record.substr(i + number + 1), std::vector<int>(numbers.begin() + 1, numbers.end()));
            totalArrangements += numArrangement;
        }
    }

    cache[entry] = totalArrangements;
    return totalArrangements;
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        /* format looks like:
???.### 1,1,3
.??..??...?##. 1,1,3
?#?#?#?#?#?#?#? 1,3,1,6
????.#...#... 4,1,1
????.######..#####. 1,6,5
?###???????? 3,2,1        
        */

        std::string line;
        int totalValidArrangements = 0;
        while (getline(newfile, line)) {
            line += ",";
            
            int space = line.find(" ");
            std::string record = line.substr(0, space);

            // split by comma
            std::vector<int> numbers;
            std::string rest = line.substr(space + 1);
            space = rest.find(",");
            while (space != std::string::npos) {
                std::string number = rest.substr(0, space);
                numbers.push_back(std::stoi(number));
                rest = rest.substr(space + 1);
                space = rest.find(",");
            }

            unsigned long long numArrangement = computeArrangements(record, numbers);
            std::cout << numArrangement << std::endl;
            totalValidArrangements += numArrangement;
        }

        std::cout << totalValidArrangements << std::endl;
            
        newfile.close();
    }
      

    return 0;
}

int second() {
        /* format looks like:
???.### 1,1,3
.??..??...?##. 1,1,3
?#?#?#?#?#?#?#? 1,3,1,6
????.#...#... 4,1,1
????.######..#####. 1,6,5
?###???????? 3,2,1        
        */
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;
        unsigned long long totalValidArrangements = 0;
        while (getline(newfile, line)) {
            line += ",";
            
            int space = line.find(" ");
            std::string record = line.substr(0, space);

            record += "?" + record + "?" + record + "?" + record + "?" + record;

            // split by comma
            std::vector<int> numbers;
            std::string rest = line.substr(space + 1);
            space = rest.find(",");
            while (space != std::string::npos) {
                std::string number = rest.substr(0, space);
                numbers.push_back(std::stoi(number));
                rest = rest.substr(space + 1);
                space = rest.find(",");
            }

            // duplicate numbers, 4 times
            std::vector<int> newNumbers = numbers;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < numbers.size(); ++j) {
                    newNumbers.push_back(numbers[j]);
                }
            }

            std::swap(newNumbers, numbers);

            unsigned long long numArrangement = computeArrangements(record, numbers);
            //std::cout << numArrangement << std::endl;
            totalValidArrangements += numArrangement;
        }

        std::cout << totalValidArrangements << std::endl;
        newfile.close();
    }
       

    return 0;
}

int main() {
    first();
    second();
}


