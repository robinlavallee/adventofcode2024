#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

struct Module;

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
    std::set<Wire*> activeWires;
};

struct Module {
    std::string name;
    std::vector<Wire*> inputs;
    std::vector<Wire*> outputs;

    virtual void update(Context& context) = 0;
};

struct FlipFlopModule : public Module {
    bool state = false;

    FlipFlopModule(std::string name) {
        this->name = name;
    }

    void update(Context& context) override {
        // TODO: not sure how to handle multiple inputs for flip flops
        for (auto& input : inputs) {
            if (!input->pulse) {
                state = !state;
                for (auto& output : outputs) {
                    output->pulse = state;
                    context.activeWires.insert(output);
                }
                return;
            }
        }
    }
};

struct NandModule : public Module {
    NandModule(std::string name) {
        this->name = name;
    }

    void update(Context& context) override {
        for (auto& input : inputs) {
            if (!input->pulse) {
                for (auto& output : outputs) {
                    output->pulse = true;
                    context.activeWires.insert(output);
                }
                return;
            }
        }

        for (auto& output : outputs) {
            output->pulse = false;
            context.activeWires.insert(output);
        }
    }
};

struct BroadcastModule : public Module {
    BroadcastModule(std::string name) {
        this->name = name;
    }

    void update(Context& context) override {
        for (auto& output : outputs) {
            output->pulse = false;
            context.activeWires.insert(output);
        }
    }
};

struct ButtonModule : public Module {
    ButtonModule() {
        this->name = "button";
    }

    void update(Context& context) override {
        outputs[0]->pulse = false;
        context.activeWires.insert(outputs[0]);
    }
};

unsigned long long computeFlipFlopHash(std::map<std::string, Module*>& modules) {
    unsigned long long hash = 0;
    for (auto& module : modules) {
        if (module.second->name[0] == '%') {
            auto flipFlop = (FlipFlopModule*)module.second;
            hash = hash << 1;
            if (flipFlop->state) {
                hash |= 1;
            }
        }
    }

    return hash;
}

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

            std::string fullModuleName = left;
            std::string shortModuleName = fullModuleName;
            if (left[0] == '%' || left[0] == '&') {
                shortModuleName = shortModuleName.substr(1);
            }

            if (left[0] == '%') {
                auto module = new FlipFlopModule(fullModuleName);
                modules[shortModuleName] = module;
            } else if (left[0] == '&') {
                auto module = new NandModule(fullModuleName);
                modules[shortModuleName] = module;
            } else {
                auto module = new BroadcastModule(fullModuleName);
                modules[shortModuleName] = module;
            }
        }

        newfile.clear();
        newfile.seekg(0, std::ios::beg);

        while (getline(newfile, line)) {
            auto arrow = line.find("->");
            auto left = line.substr(0, arrow - 1);

            std::string shortModuleName = left;
            if (left[0] == '%' || left[0] == '&') {
                shortModuleName = shortModuleName.substr(1);
            }

            auto right = line.substr(arrow + 3);
            right += ", ";

            auto comma = right.find(", ");
            while (comma != std::string::npos) {
                auto outputModuleName = right.substr(0, comma);

                Module* module = modules[shortModuleName];
                Module* outputModule = modules[outputModuleName];

                Wire* wire = new Wire();
                wire->prevConnector = module;
                wire->nextConnector = outputModule;

                module->outputs.push_back(wire);
                outputModule->inputs.push_back(wire);

                right = right.substr(comma + 2);
                comma = right.find(", ");
            }
        }

        auto button = new ButtonModule();
        modules["button"] = button;
        auto buttonWire = new Wire();
        buttonWire->prevConnector = button;
        buttonWire->nextConnector = modules["broadcaster"];
        button->outputs.push_back(buttonWire);

        int numCycles = 1000;
        
        std::map<unsigned long long, PulseStats> stateToPulseStatsMap;
        PulseStats totalPulseStats;

        auto hash = computeFlipFlopHash(modules);
        auto lastHash = hash;
        std::map<unsigned long long, unsigned long long> hashSequence;
        while (stateToPulseStatsMap.find(hash) == stateToPulseStatsMap.end() && numCycles > 0) {
            Context context;
            button->update(context);

            std::set<Module*> modulesToUpdate;
            do {
                modulesToUpdate.clear();
                while (context.activeWires.size() > 0) {
                    auto wire = *context.activeWires.begin();
                    context.activeWires.erase(wire);
                    modulesToUpdate.insert(wire->nextConnector);                    
                }

                for (auto& module : modulesToUpdate) {
                    module->update(context);
                }
            } while (modulesToUpdate.size() > 0);

            stateToPulseStatsMap[hash] = context.pulseStats;
            totalPulseStats.lowPulseCount += context.pulseStats.lowPulseCount;
            totalPulseStats.highPulseCount += context.pulseStats.highPulseCount;

            lastHash = hash;
            hash = computeFlipFlopHash(modules);
            hashSequence[lastHash] = hash;
            numCycles--;
        }

        if (numCycles > 0) {
            unsigned long long moreLargeCyclesLeft = numCycles / stateToPulseStatsMap.size();

            totalPulseStats.lowPulseCount += totalPulseStats.lowPulseCount * moreLargeCyclesLeft;
            totalPulseStats.highPulseCount += totalPulseStats.highPulseCount * moreLargeCyclesLeft;
        }

        numCycles = numCycles % stateToPulseStatsMap.size();
        while (numCycles > 0) {
            totalPulseStats.lowPulseCount += stateToPulseStatsMap[hash].lowPulseCount;
            totalPulseStats.highPulseCount += stateToPulseStatsMap[hash].highPulseCount;
            hash = hashSequence[hash];
            numCycles--;
        }

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


