
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

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        /* format is
Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11        
        */

       // hardest is splitting everything up

        std::string line;
        int points = 0;
        while (getline(newfile, line)) {
            // parse line in the following format: 
            
            // remove double space if any
            replace(line, "  ", " ");
            line += " ";

            // split line into cards
            int separator = line.find(": ");
            std::string card = line.substr(0, separator);
            std::string rest = line.substr(separator + 2);

            std::set<int> winningNumbers;

            // split each number until you find a | character
            separator = rest.find("| ");
            std::string winningNumbersString = rest.substr(0, separator);
            std::string rest2 = rest.substr(separator + 2);

            // split by space for each number in the winning numbers
            int space = winningNumbersString.find(" ");
            while (space != std::string::npos) {
                std::string number = winningNumbersString.substr(0, space);
                winningNumbers.insert(std::stoi(number));
                winningNumbersString = winningNumbersString.substr(space + 1);
                space = winningNumbersString.find(" ");
            }

            // split by space for each number in the cards
            space = rest2.find(" ");
            int point = 0;
            while (space != std::string::npos) {
                std::string number = rest2.substr(0, space);
                if (winningNumbers.find(std::stoi(number)) != winningNumbers.end()) {
                    if (point == 0) {
                        point = 1;
                    } else {
                        point *= 2;
                    }
                }
                rest2 = rest2.substr(space + 1);
                space = rest2.find(" ");
            }

            points += point;
        }

        std::cout << points << std::endl;
    }

    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        /* format is
Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11
        */

        // hardest is splitting everything up

        std::string line;
        std::vector<int> numMatches;

        while (getline(newfile, line)) {
            // parse line in the following format: 

            // remove double space if any
            replace(line, "  ", " ");
            line += " ";

            // split line into cards
            int separator = line.find(": ");
            std::string card = line.substr(0, separator);
            std::string rest = line.substr(separator + 2);

            std::set<int> winningNumbers;

            // split each number until you find a | character
            separator = rest.find("| ");
            std::string winningNumbersString = rest.substr(0, separator);
            std::string rest2 = rest.substr(separator + 2);

            // split by space for each number in the winning numbers
            int space = winningNumbersString.find(" ");
            while (space != std::string::npos) {
                std::string number = winningNumbersString.substr(0, space);
                winningNumbers.insert(std::stoi(number));
                winningNumbersString = winningNumbersString.substr(space + 1);
                space = winningNumbersString.find(" ");
            }

            // split by space for each number in the cards
            space = rest2.find(" ");
            int matches = 0;
            while (space != std::string::npos) {
                std::string number = rest2.substr(0, space);
                if (winningNumbers.find(std::stoi(number)) != winningNumbers.end()) {
                    matches++;
                }
                rest2 = rest2.substr(space + 1);
                space = rest2.find(" ");
            }

            numMatches.push_back(matches);
        }

        std::vector<int> numCards;
        numCards.resize(numMatches.size());
        for (int i = 0; i < numCards.size(); i++) {
            numCards[i] = 1;
        }

        // now loop and make duplicate !!
        for (int i = 0; i < numMatches.size(); i++) {
            for (int k = 1; k <= numMatches[i]; k++) {
                numCards[i+k] += numCards[i]; // each instance of the card will add to the next ones
            }
        }

        int total = 0;
        for (int i = 0; i < numCards.size(); i++) {
            total += numCards[i];
        }

        std::cout << total << std::endl;
    }


    return 0;
}

int main() {
    first();
    second();
}


