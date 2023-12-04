
#include <iostream>
#include <fstream>
#include <string>
#include <map>

int first() {
    std::fstream newfile;
    newfile.open("day1_input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string tp;
        int sum = 0;
        while (getline(newfile, tp)) {
            int first = -1;
            int last = -1;

            const char* ptr = tp.c_str();
            while (*ptr != 0) {
                if (*ptr >= '0' && *ptr <= '9') {
                    if (first == -1) {
                        first = *ptr - '0';
                        last = first;
                    }
                    else {
                        last = *ptr - '0';
                    }
                }
                ptr++;
            }

            if (first == -1) {
                continue;
            }

            sum += first * 10 + last;
        }
        newfile.close();
        printf("Sum: %d\n", sum);
    }

    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("day1_input.txt", std::ios::in);

    std::map<std::string, int> digitMap = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
    };

    if (newfile.is_open()) {
        std::string tp;
        int sum = 0;
        while (getline(newfile, tp)) {
            int first = -1;
            int last = -1;

            const char* ptr = tp.c_str();
            while (*ptr != 0) {
                int digit = -1;
                if (*ptr >= '0' && *ptr <= '9') {
                    digit = *ptr - '0';
                } else {
                    for (const auto& pair : digitMap) {
                        auto substring = std::string(ptr);
                        if (substring.length() < pair.first.length()) {
                            continue;
                        }

                        if (memcmp(substring.c_str(), pair.first.c_str(), pair.first.length()) == 0) {
                            digit = pair.second;
                            break;
                        }
                    }
                }

                if (digit != -1) {
                    if (first == -1) {
                        first = digit;
                    }
                    last = digit;
                }

                ptr++;
            }

            if (first == -1) {
                continue;
            }

            printf("%d\n", first * 10 + last);
            sum += first * 10 + last;
        }
        newfile.close();
        printf("Sum: %d\n", sum);
    }

    return 0;
}

int main() {
    first();
    second();
}


