
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

using Path = std::list<std::pair<int, int>>;

Path findShortestPath(std::vector<std::vector<bool>>& matrix, int start, int end) {
    std::list<std::pair<int, int>> path;

    std::set<int> visited;
    std::set<int> toVisit;
    std::map<int, int> parent;

    toVisit.insert(start);
    visited.insert(start);

    while (!toVisit.empty()) {
        auto node = *toVisit.begin();
        toVisit.erase(node);

        for (int i = 0; i < matrix.size(); i++) {
            if (node == i) {
                continue;
            }

            if (matrix[node][i]) {
                if (visited.count(i)) {
                    continue;
                }

                toVisit.insert(i);
                visited.insert(i);
                parent[i] = node;

                if (i == end) {
                    break;
                }
            }
        }
    }

    if (visited.count(end)) {
        auto current = end;
        while (current != start) {
            path.push_front({parent[current], current});
            current = parent[current];
        }
    }

    return path;
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);

    std::vector<std::vector<bool>> matrix;
    std::map<std::string, int> nameToIndex;

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

        std::set<int> groupA;
        std::set<int> toVisit;
        std::set<std::pair<int, int>> separatorEdges;

        groupA.insert(0);
        toVisit.insert(0);
        
        while (!toVisit.empty()) {
            auto node = *toVisit.begin();
            toVisit.erase(node);

            for (int i = 0; i < matrix.size(); i++) {
                if (node == i) {
                    continue;
                }

                if (!matrix[node][i]) {
                    continue;
                }

                if (groupA.count(i)) {
                    continue;
                }

                Path allPaths;
                int numLoops = 3 - separatorEdges.size();
                while (numLoops > 0) {
                    auto path = findShortestPath(matrix, node, i);

                    if (path.size() == 0) {
                        break;
                    }

                    allPaths.insert(allPaths.end(), path.begin(), path.end());

                    for (auto& edge : path) {
                        matrix[edge.first][edge.second] = false;
                        matrix[edge.second][edge.first] = false;
                    }

                    numLoops--;
                }

                auto path = findShortestPath(matrix, node, i);

                for (auto& edge : allPaths) {
                    matrix[edge.first][edge.second] = true;
                    matrix[edge.second][edge.first] = true;
                }

                if (path.size() == 0) {
                    separatorEdges.insert({node, i});

                    matrix[node][i] = false;
                    matrix[i][node] = false;
                } else {
                    groupA.insert(i);
                    toVisit.insert(i);
                }
            }
        }

        int result = groupA.size() * (matrix.size() - groupA.size());
        std::cout << result << std::endl;

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
