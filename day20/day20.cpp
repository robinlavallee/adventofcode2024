#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <queue>

struct Module;
struct Context;

enum class PulseType {
    Low,
    High,
};

struct PulseStats {
    unsigned long long lowPulseCount = 0;
    unsigned long long highPulseCount = 0;
};

struct Pulse {
    PulseType type = PulseType::Low;
    std::string from;
    std::string destination;
};

struct Context {
    PulseStats pulseStats;
    std::queue<Pulse> activePulses;
};

struct Module {
    std::string name;

    std::map<std::string, PulseType> inputs;
    std::vector<std::string> outputs;

    virtual void update(Context& context, Pulse& pulse) = 0;
};


struct FlipFlopModule : public Module {
    bool state = false;

    FlipFlopModule(std::string name) {
        this->name = name;
    }

    void update(Context& context, Pulse& pulse) override {
        if (pulse.type == PulseType::Low) {
            state = !state;
            std::cout << "FlipFlop " << name << " to " << state << std::endl;
            for (auto& output : outputs) {
                Pulse pulse;
                pulse.type = state ? PulseType::High : PulseType::Low;               
                pulse.from = name.substr(1);
                pulse.destination = output;
                if (state) {
                    context.pulseStats.highPulseCount++;
                } else {
                    context.pulseStats.lowPulseCount++;
                }
                std::cout << "Flipflop " << name << " sending " << (pulse.type == PulseType::High ? "high" : "low") << " pulse to " << output << std::endl;
                context.activePulses.push(pulse);
            }
        }
    }
};

struct NandModule : public Module {
    NandModule(std::string name) {
        this->name = name;
    }

    void update(Context& context, Pulse& pulse) override {
        bool allHigh = true;
        for (auto& input : inputs) {
            if (pulse.from == input.first) {
                input.second = pulse.type;
            }

            if (input.second == PulseType::Low) {
                allHigh = false;
                break;
            }
        }

        for (auto& output : outputs) {
            Pulse pulse;
            pulse.type = allHigh ? PulseType::Low : PulseType::High;
            pulse.from = name.substr(1);
            pulse.destination = output;
            if (pulse.type == PulseType::Low) {
                context.pulseStats.lowPulseCount++;
            } else {
                context.pulseStats.highPulseCount++;
            }
            std::cout << "Nand " << name << " sending " << (pulse.type == PulseType::High ? "high" : "low") << " pulse to " << pulse.destination << std::endl;
            context.activePulses.push(pulse);
        }
    }
};

struct BroadcastModule : public Module {
    BroadcastModule(std::string name) {
        this->name = name;
    }

    void update(Context& context, Pulse& pulse) override {
        for (auto& output : outputs) {
            Pulse pulse;
            pulse.type = PulseType::Low;
            pulse.from = name;
            pulse.destination = output;
            std::cout << "Broadcast " << name << " sending " << (pulse.type == PulseType::High ? "high" : "low") << " pulse to " << pulse.destination << std::endl;
            context.pulseStats.lowPulseCount++;
            context.activePulses.push(pulse);
        }
    }
};

struct ButtonModule : public Module {
    ButtonModule() {
        this->name = "button";
    }

    void update(Context& context, Pulse& pulse) override {
        Pulse outputPulse;
        outputPulse.type = PulseType::Low;
        outputPulse.from = name;
        outputPulse.destination = "broadcaster";

        std::cout << "Button " << name << " sending " << (outputPulse.type == PulseType::High ? "high" : "low") << " pulse to " << outputPulse.destination << std::endl;
        context.pulseStats.lowPulseCount++;
        context.activePulses.push(outputPulse);
    }
};

struct OutputModule : public Module {
    OutputModule(std::string name) {
        this->name = name;
    }

    void update(Context& context, Pulse& pulse) override {
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

                if (!outputModule) {
                    outputModule = new OutputModule(outputModuleName);
                    modules[outputModuleName] = outputModule;
                }

                module->outputs.push_back(outputModuleName);
                outputModule->inputs[shortModuleName] = PulseType::Low;

                right = right.substr(comma + 2);
                comma = right.find(", ");
            }
        }

        auto button = new ButtonModule();
        modules["button"] = button;
        button->outputs.push_back("broadcaster");

        int numCycles = 1000;
        
        std::map<unsigned long long, PulseStats> stateToPulseStatsMap;
        PulseStats totalPulseStats;

        auto hash = computeFlipFlopHash(modules);
        auto lastHash = hash;
        std::map<unsigned long long, unsigned long long> hashSequence;
        while (stateToPulseStatsMap.find(hash) == stateToPulseStatsMap.end() && numCycles > 0) {
            Context context;

            Pulse initialPulse;
            initialPulse.type = PulseType::Low;
            initialPulse.destination = "broadcaster";
            context.pulseStats.lowPulseCount++;
            context.activePulses.push(initialPulse);

            while (!context.activePulses.empty()) {
                auto activePulse = context.activePulses.front();
                context.activePulses.pop();
                
                auto module = modules[activePulse.destination];
                module->update(context, activePulse);
            }

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


