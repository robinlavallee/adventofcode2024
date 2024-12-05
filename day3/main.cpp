
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <regex>

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;
        long long sum = 0;
        while (std::getline(newfile, line)) {
            std::regex re("mul\\((\\d{1,3}),(\\d{1,3})\\)");
            std::smatch match;
            std::string::const_iterator searchStart( line.cbegin() );
            while ( std::regex_search( searchStart, line.cend(), match, re ) ) {
                std::cout << "Match: " << match[0] << std::endl;
                searchStart = match.suffix().first;
                long long mul = std::stoll(match[1]) * std::stoll(match[2]);
                sum += mul;
            }
        }

        std::cout << "Sum: " << sum << std::endl;
    }

    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;
        long long sum = 0;
        bool enabled = true;
        while (std::getline(newfile, line)) {
            std::regex mul_re("mul\\((\\d{1,3}),(\\d{1,3})\\)");
            std::regex do_re("do\\(\\)");
            std::regex donot_re("don't\\(\\)");
            std::smatch mul_match, do_match, donot_match;
            std::string::const_iterator searchStart( line.cbegin() );

            while (1) {
                std::regex_search( searchStart, line.cend(), mul_match, mul_re );
                std::regex_search( searchStart, line.cend(), do_match, do_re );
                std::regex_search( searchStart, line.cend(), donot_match, donot_re );

                if (mul_match.empty() && do_match.empty() && donot_match.empty()) {
                    break;
                }

                // check the closest match
                if (!mul_match.empty() && (do_match.empty() || mul_match.position() < do_match.position()) && (donot_match.empty() || mul_match.position() < donot_match.position())) {
                    searchStart = mul_match.suffix().first;
                    if (enabled) {
                        long long mul = std::stoll(mul_match[1]) * std::stoll(mul_match[2]);
                        sum += mul;
                    }
                } else if (!do_match.empty() && (mul_match.empty() || do_match.position() < mul_match.position()) && (donot_match.empty() || do_match.position() < donot_match.position())) {
                    searchStart = do_match.suffix().first;
                    enabled = true;
                } else if (!donot_match.empty() && (mul_match.empty() || donot_match.position() < mul_match.position()) && (do_match.empty() || donot_match.position() < do_match.position())) {
                    searchStart = donot_match.suffix().first;
                    enabled = false;
                }
            }
        }

        std::cout << "Sum: " << sum << std::endl;
    }

    return 0;
}

int main() {
    first();
    second();
}


