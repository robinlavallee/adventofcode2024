
#include <algorithm>
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

struct Node {
    std::string name;
    Node* left = nullptr;
    Node* right = nullptr;
    bool isStartNode = false;
    bool isEndNode = false;
};

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::map<std::string, Node*> nodeMap;

        std::string sequence;
        std::getline(newfile, sequence);

        // then it will be empty lines OR
        // AAA = (BBB, BBB)

        std::string line;
        while (std::getline(newfile, line)) {
            if (line.empty()) {
                continue;
            }

            std::string name = line.substr(0, line.find(" "));
            std::string left = line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1);
            std::string right = line.substr(line.find(",") + 2, line.find(")") - line.find(",") - 2);

            Node* node;
            if (nodeMap.find(name) == nodeMap.end()) {
                nodeMap[name] = new Node();
            }

            node = nodeMap[name];
            node->name = name;
                
            if (nodeMap.find(left) == nodeMap.end()) {
                nodeMap[left] = new Node();
                nodeMap[left]->name = left;
            }
            node->left = nodeMap[left];

            if (nodeMap.find(right) == nodeMap.end()) {
                nodeMap[right] = new Node();
                nodeMap[right]->name = right;
            }
            node->right = nodeMap[right];
        }

        // now follow the instructions until we find the exit at ZZZ
        Node* node = nodeMap["AAA"];
        int sequenceIndex = 0;
        int numSteps = 0;
        while (node->name != "ZZZ") {
            numSteps++;
            if (sequence[sequenceIndex++] == 'L') {
                node = node->left;
            } else {
                node = node->right;
            }

            if (sequenceIndex == sequence.size()) {
                sequenceIndex = 0;
            }

            if (node->name == "ZZZ") {
                break;
            }
        }

        std::cout << "Number of steps: " << numSteps << std::endl;

        newfile.close();
    }

    return 0;
}

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {

        std::map<std::string, Node*> nodeMap;
        std::set<Node*> startNodes;
        std::set<Node*> endNodes;

        std::string sequence;
        std::getline(newfile, sequence);

        // then it will be empty lines OR
        // AAA = (BBB, BBB)

        std::string line;
        while (std::getline(newfile, line)) {
            if (line.empty()) {
                continue;
            }

            std::string name = line.substr(0, line.find(" "));
            std::string left = line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1);
            std::string right = line.substr(line.find(",") + 2, line.find(")") - line.find(",") - 2);

            Node* node;
            if (nodeMap.find(name) == nodeMap.end()) {
                nodeMap[name] = new Node();
            }

            node = nodeMap[name];
            node->name = name;
            if (node->name[2] == 'A') {
                node->isStartNode = true;
                startNodes.insert(node);
            } else if (node->name[2] == 'Z') {
                node->isEndNode = true;
                endNodes.insert(node);
            }

            if (nodeMap.find(left) == nodeMap.end()) {
                nodeMap[left] = new Node();
                nodeMap[left]->name = left;
                if (node->name[2] == 'A') {
                    node->isStartNode = true;
                    startNodes.insert(node);
                } else if (node->name[2] == 'Z') {
                    node->isEndNode = true;
                    endNodes.insert(node);
                }
            }
            node->left = nodeMap[left];

            if (nodeMap.find(right) == nodeMap.end()) {
                nodeMap[right] = new Node();
                nodeMap[right]->name = right;
                if (node->name[2] == 'A') {
                    node->isStartNode = true;
                    startNodes.insert(node);
                } else if (node->name[2] == 'Z') {
                    node->isEndNode = true;
                    endNodes.insert(node);
                }
            }
            node->right = nodeMap[right];
        }

        std::vector<Node*> nodesSolver;
        for (auto& node : startNodes) {
            nodesSolver.push_back(node);
        }
        
        // I think this can be solved by prime factorization
        std::vector<int> primes;
        primes.resize(nodesSolver.size());

        int sequenceIndex = 0;
        int numSteps = 0;
        while (true) {
            bool solved=true;
            int index = 0;
            for (auto& node : nodesSolver) {
                if (!node->isEndNode) {
                    solved=false;
                } else {
                    if (primes[index] == 0) {
                        primes[index] = numSteps;
                        std::cout << "Prime: index " << index << " numSteps " << numSteps << std::endl;
                    }
                }
                index++;
            }

            if (solved) {
                break;
            }

            numSteps++;
            if (sequence[sequenceIndex++] == 'L') {
                for (auto& node : nodesSolver) {
                    node = node->left;
                }
            } else {
                for (auto& node : nodesSolver) {
                    node = node->right;
                }
            }

            if (sequenceIndex == sequence.size()) {
                sequenceIndex = 0;
            }
        };

        std::cout << "Number of steps: " << numSteps << std::endl;

        newfile.close();
    }
    return 0;
}

int main() {
    //first();
    second();
}


