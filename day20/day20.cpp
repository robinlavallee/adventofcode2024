#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

struct Wire {
    Module* prevConnector = nullptr;
    Module* nextConnector = nullptr;
    bool pulse = false;
};

struct PulseStats {
    int lowPulseCount = 0;
    int highPulseCount = 0;
};

struct Context {
    PulseStats pulseStats;
};

struct Module {
    std::string name;
    std::vector<Wire*> inputs;
    std::vector<Wire*> output;

    virtual void update(Context& context) = 0;
};

std::set<Wire*> activeWires;

struct FlipFlopModule : public Module {
    bool state = false;

    FlipFlopModule(std::string name) {
        this->name = name;
    }

    void update(Context& context) override {
    }
};

struct NandModule : public Module {
    NandModule(std::string name) {
        this->name = name;
    }

    void update(Context& context) override {
    }
};

struct BroadcastModule : public Module {
    BroadcastModule(std::string name) {
        this->name = name;
    }

    void update(Context& context) override {

    }
};

struct ButtonModule : public Module {
    ButtonModule() {
        this->name = "button";
    }

    void update(Context& context) override {

    }
};

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);

    std::map<std::string, Module*> modules;

    if (newfile.is_open()) {
        
        std::string line;
        while (getline(newfile, line)) {
            /* 
            broadcaster -> a, b, c
            %a -> b
            %b -> c
            %c -> inv
            &inv -> a
            */

            auto arrow = line.find("->");
            auto left = line.substr(0, arrow - 1);

            std::string moduleName = left;
            if (left[0] == '%' || left[0] == '&') {
                moduleName = moduleName.substr(1);
            }

            if (left[0] == '%') {
                auto module = new FlipFlopModule(moduleName);
                modules[moduleName] = module;
            } else if (left[0] == '&') {
                auto module = new NandModule(moduleName);
                modules[moduleName] = module;
            } else {
                auto module = new BroadcastModule(moduleName);
                modules[moduleName] = module;
            }
        }

        newfile.clear();
        newfile.seekg(0, std::ios::beg);

        while (getline(newfile, line)) {
            auto arrow = line.find("->");
            auto left = line.substr(0, arrow - 1);

            std::string moduleName = left;
            if (left[0] == '%' || left[0] == '&') {
                moduleName = moduleName.substr(1);
            }

            auto right = line.substr(arrow + 3);
            right += ",";

            auto comma = right.find(",");
            while (comma != std::string::npos) {
                auto outputModuleName = right.substr(0, comma);

                Module* module = modules[moduleName];
                Module* outputModule = modules[outputModuleName];

                Wire* wire = new Wire();
                wire->prevConnector = module;
                wire->nextConnector = outputModule;

                module->output.push_back(wire);
                outputModule->inputs.push_back(wire);

                right = right.substr(comma + 1);
                comma = right.find(",");
            }
        }

        // create the special "button" module
        auto button = new ButtonModule();
        modules["button"] = button;
        auto buttonWire = new Wire();
        buttonWire->prevConnector = button;
        buttonWire->nextConnector = modules["broadcaster"];
        button->output.push_back(buttonWire);

        // look at all flipflop state since they make a global stats, and check when we loop back so that we can optimize
        int numCycles = 1000;
        // figure out how many flipflops modules there are
        std::map<unsigned long long, PulseStats> stateToPulseStatsMap;
        PulseStats totalPulseStats;


        button->update();


        newfile.close();

        std::cout << "Low Pulse: " << totalPulseStats.lowPulseCount << " High Pulse: " << totalPulseStats.highPulseCount << std::endl;
        std::cout << "Multiplication: " << totalPulseStats.lowPulseCount * totalPulseStats.highPulseCount << std::endl;
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


