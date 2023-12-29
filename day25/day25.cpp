
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

// We will use a matrix to represent the graph
// we will associate each node with a number, starting from 0
// so it's easier to read the file twice and create the matrix

std::map<std::string, int> nameToIndex;

int solve(std::vector<std::vector<bool>>& matrix) {
    std::set<int> visited;

    std::list<int> queue;
    queue.push_back(0);
    visited.insert(0);

    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop_front();

        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[node][i] && !visited.count(i)) {
                visited.insert(i);
                queue.push_back(i);
            }
        }
    }

    return visited.size();
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);

    std::vector<std::vector<bool>> matrix;
    if (newfile.is_open()) {
        std::string line;
        int index = 0;
        while (getline(newfile, line)) {
            // jqt: rhn xhk nvd
            auto colon = line.find(":");
            auto name = line.substr(0, colon);

            if (nameToIndex.find(name) == nameToIndex.end()) {
                nameToIndex[name] = index;
                index++;
            }

            auto right = line.substr(colon + 2);
            right += " ";

            auto space = right.find(" ");
            while (space != std::string::npos) {
                auto otherName = right.substr(0, space);
                if (nameToIndex.find(otherName) == nameToIndex.end()) {
                    nameToIndex[otherName] = index;
                    index++;
                }

                right = right.substr(space + 1);
                space = right.find(" ");
            }
        }

        matrix.resize(nameToIndex.size());
        for (auto& row : matrix) {
            row.resize(nameToIndex.size());
            row.assign(row.size(), false);
        }

        newfile.clear();
        newfile.seekg(0, std::ios::beg);

        while (getline(newfile, line)) {
            // jqt: rhn xhk nvd
            auto colon = line.find(":");
            auto name = line.substr(0, colon);

            // rhn xhk nvd
            auto right = line.substr(colon + 2);
            right += " ";

            auto space = right.find(" ");
            while (space != std::string::npos) {
                auto otherName = right.substr(0, space);
                matrix[nameToIndex[name]][nameToIndex[otherName]] = true;
                matrix[nameToIndex[otherName]][nameToIndex[name]] = true;

                right = right.substr(space + 1);
                space = right.find(" ");
            }
        }

        for (int source1 = 0; source1 < matrix.size(); source1++) {
            for (int dest1 = source1 + 1; dest1 < matrix.size(); dest1++) {
                if (!matrix[source1][dest1]) {
                    continue;
                }

                for (int source2 = source1; source2 < matrix.size(); source2++) {
                    for (int dest2 = source2 + 1; dest2 < matrix.size(); dest2++) {
                        if (!matrix[source2][dest2]) {
                            continue;
                        }

                        for (int source3 = source2; source3 < matrix.size(); source3++) {
                            for (int dest3 = source3 + 1; dest3 < matrix.size(); dest3++) {
                                if (!matrix[source3][dest3]) {
                                    continue;
                                }

                                matrix[source1][dest1] = false;
                                matrix[dest1][source1] = false;
                                matrix[source2][dest2] = false;
                                matrix[dest2][source2] = false;
                                matrix[source3][dest3] = false;
                                matrix[dest3][source3] = false;

                                int visited = solve(matrix);

                                if (visited != matrix.size()) {
                                    int solution = visited * (matrix.size() - visited);
                                    std::cout << solution << std::endl;
                                    return 0;
                                }

                                matrix[source1][dest1] = true;
                                matrix[dest1][source1] = true;
                                matrix[source2][dest2] = true;
                                matrix[dest2][source2] = true;
                                matrix[source3][dest3] = true;
                                matrix[dest3][source3] = true;
                            }
                        }
                    }
                }
            }
        }

        newfile.close();
    }

    return 0;
}


int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        newfile.close();
    }

    return 0;
}

int main() {
    first();
    second();
}
