
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

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

            // basically the numbers are telling us how many '1's bits we have
            // the # are already 1s
            // the . are already 0s
            // the number of commas tell us how many regions with 0s we have

            // ???.###    and 1,1,3
            // we know we need 5 bits and we already have 3
            // there are 2 bits left out of 3 arrangement
            // so we can try all combinations of 2 bits out of 3, basically looping over 0 to 2^3-1 and then applying the bits from left to right
            // then we can count the sequence of bits and see if matches the expectation
            // so it would go like:
            // 000 (wrong)
            // 001 (wrong)
            // 010 (wrong)
            // 011 (possible)   --> 011.111  --> 2, 3 -> wrong
            // 100 (wrong)
            // 101 (possible)   --> 101.111  --> 1, 1, 3 -> right (SUCCESS )
            // 110 (possible)   --> 110.111  --> 2, 3 -> wrong
            // 111 (wrong)      

            int howManyBits = record.size();
            int howManyOnes = 0;
            for (int i = 0; i < record.size(); ++i) {
                if (record[i] == '#') {
                    howManyOnes++;
                }
            }

            int howManyOnesNeeded = 0;
            for (int i = 0; i < numbers.size(); ++i) {
                howManyOnesNeeded += numbers[i];
            }

            int howManyQuestions = 0;
            for (int i = 0; i < record.size(); ++i) {
                if (record[i] == '?') {
                    howManyQuestions++;
                }
            }

            int max = 1 << howManyQuestions;
            int onesRemaining = howManyOnesNeeded - howManyOnes;
            int numValidArrangements = 0;
            for (int i = 0; i < max; ++i) {
                // count how many bits are set in i
                int bitsSet = 0;
                int temp = i;
                while (temp > 0) {
                    if (temp & 1) {
                        bitsSet++;
                    }
                    temp >>= 1;
                }

                if (bitsSet != onesRemaining) {
                    continue;
                }

                // ???.###
                // go from left to right, and for each ? replace with the next bit in i
                int bitIndex = 0;
                std::string newRecord = "";
                for (int j = 0; j < record.size(); ++j) {
                    if (record[j] == '?') {
                        if (i & (1 << bitIndex)) {
                            newRecord += '#';
                        } else {
                            newRecord += '.';
                        }
                        bitIndex++;
                    } else {
                        newRecord += record[j];
                    }
                }

                // now check if newRecord bits sequence matches the expectation in numbers
                int currentSequence = 0;
                int expectedSequence = 0;
                bool valid = true;
                for (int j = 0; j < newRecord.size(); ++j) {
                    if (newRecord[j] == '#') {
                        currentSequence++;
                    } else {
                        if (currentSequence > 0) {
                            expectedSequence++;
                            if (expectedSequence > numbers.size()) {
                                valid = false;
                                break;
                            }
                            if (currentSequence != numbers[expectedSequence - 1]) {
                                valid = false;
                                break;
                            }
                            currentSequence = 0;
                        }
                    }
                }

                if (!valid) {
                    continue;
                }

                if (currentSequence > 0) {
                    expectedSequence++;
                    if (expectedSequence > numbers.size()) {
                        continue;
                    }
                    if (currentSequence != numbers[expectedSequence - 1]) {
                        continue;
                    }
                }

                // I think we need to fix the last number

                if (expectedSequence == numbers.size()) {
                    //std::cout << newRecord << std::endl;
                    numValidArrangements++;
                }
            }

            std::cout << numValidArrangements << std::endl;
            totalValidArrangements += numValidArrangements;
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

            // basically the numbers are telling us how many '1's bits we have
            // the # are already 1s
            // the . are already 0s
            // the number of commas tell us how many regions with 0s we have

            // ???.###    and 1,1,3
            // we know we need 5 bits and we already have 3
            // there are 2 bits left out of 3 arrangement
            // so we can try all combinations of 2 bits out of 3, basically looping over 0 to 2^3-1 and then applying the bits from left to right
            // then we can count the sequence of bits and see if matches the expectation
            // so it would go like:
            // 000 (wrong)
            // 001 (wrong)
            // 010 (wrong)
            // 011 (possible)   --> 011.111  --> 2, 3 -> wrong
            // 100 (wrong)
            // 101 (possible)   --> 101.111  --> 1, 1, 3 -> right (SUCCESS )
            // 110 (possible)   --> 110.111  --> 2, 3 -> wrong
            // 111 (wrong)      

            int howManyBits = record.size();
            int howManyOnes = 0;
            for (int i = 0; i < record.size(); ++i) {
                if (record[i] == '#') {
                    howManyOnes++;
                }
            }

            int howManyOnesNeeded = 0;
            for (int i = 0; i < numbers.size(); ++i) {
                howManyOnesNeeded += numbers[i];
            }

            int howManyQuestions = 0;
            for (int i = 0; i < record.size(); ++i) {
                if (record[i] == '?') {
                    howManyQuestions++;
                }
            }

            unsigned long long max = 1ULL << howManyQuestions;
            int onesRemaining = howManyOnesNeeded - howManyOnes;
            unsigned long long numValidArrangements = 0;
            for (unsigned long long i = 0; i < max; ++i) {
                // count how many bits are set in i
                int bitsSet = 0;
                unsigned long long temp = i;
                while (temp > 0) {
                    if (temp & 1) {
                        bitsSet++;
                        if (bitsSet > onesRemaining)
                            break;
                    }
                    temp >>= 1;
                }

                if (bitsSet != onesRemaining) {
                    continue;
                }

                // ???.###
                // go from left to right, and for each ? replace with the next bit in i
                int bitIndex = 0;
                std::string newRecord = "";
                for (int j = 0; j < record.size(); ++j) {
                    if (record[j] == '?') {
                        if (i & (1ULL << bitIndex)) {
                            newRecord += '#';
                        } else {
                            newRecord += '.';
                        }
                        bitIndex++;
                    } else {
                        newRecord += record[j];
                    }
                }

                // now check if newRecord bits sequence matches the expectation in numbers
                int currentSequence = 0;
                int expectedSequence = 0;
                bool valid = true;
                for (int j = 0; j < newRecord.size(); ++j) {
                    if (newRecord[j] == '#') {
                        currentSequence++;
                    } else {
                        if (currentSequence > 0) {
                            expectedSequence++;
                            if (expectedSequence > numbers.size()) {
                                valid = false;
                                break;
                            }
                            if (currentSequence != numbers[expectedSequence - 1]) {
                                valid = false;
                                break;
                            }
                            currentSequence = 0;
                        }
                    }
                }

                if (!valid) {
                    continue;
                }

                if (currentSequence > 0) {
                    expectedSequence++;
                    if (expectedSequence > numbers.size()) {
                        continue;
                    }
                    if (currentSequence != numbers[expectedSequence - 1]) {
                        continue;
                    }
                }

                // I think we need to fix the last number

                if (expectedSequence == numbers.size()) {
                    //std::cout << newRecord << std::endl;
                    numValidArrangements++;
                }
            }

            std::cout << numValidArrangements << std::endl;
            totalValidArrangements += numValidArrangements;
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


