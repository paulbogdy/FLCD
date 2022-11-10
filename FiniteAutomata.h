#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>

enum FAType {
    Initial, Aux, Final
};

class FiniteAutomata {
public:
    inline static const std::string INIT_STATE { "p" };
    FiniteAutomata(std::string file_path) {
        states.insert({INIT_STATE, FAType::Initial});
        std::string line;
        std::ifstream fa(file_path);
        if (fa.is_open())
        {
            // Read Aux States
            if (! getline(fa, line))
            {
                throw std::runtime_error("Invalid Finite Automata File\n");
            }
            std::istringstream ss(line);
            std::string state;
            while(ss >> state) {
                if (states.find(state) != states.end()) {
                    throw std::runtime_error("Invalid Finite Automata, duplicated states\n");
                }
                states.insert({state, FAType::Aux});
            }

            // Read Final States
            if (! getline(fa, line))
            {
                throw std::runtime_error("Invalid Finite Automata File\n");
            }
            ss = std::istringstream(line);

            while(ss >> state) {
                if (states.find(state) != states.end()) {
                    throw std::runtime_error("Invalid Finite Automata, duplicated states\n");
                }
                states.insert({state, FAType::Final});
            }

            // Read Transitions
            while (getline(fa, line)) {
                addTransition(line);
            }

            fa.close();
        }
        else {
            throw std::runtime_error("Invalid Finite Automata file path\n");
        }
    }
    bool matches(std::string elem) {
        std::string current = INIT_STATE;
        for(auto c: elem) {
            if(transitions.find(current) == transitions.end()) {
                return false;
            }
            auto &trans = transitions[current];
            if(trans.find(c) == trans.end()) {
                return false;
            }
            current = trans[c];
        }
        if(states.find(current) == states.end()){
            return false;
        }
        return states[current] == FAType::Final;
    }
private:
    void addTransition(std::string &line) {
        std::string starting_state = "";
        std::string next_state = "";
        char transElem;
        int i=0;
        while(line[i] != ',' && i < line.size()) {
            starting_state.push_back(line[i]);
            i++;
        }
        if (i >= line.size() || line[i] != ',') {
            throw std::runtime_error("Invalid Transition: " + line + "\n");
        }
        if (states.find(starting_state) == states.end()) {
            throw std::runtime_error("Invalid Starting State in Transition: " + line + "\n");
        }
        i++;
        if (i+1 >= line.size() || line[i+1] != ',') {
            throw std::runtime_error("Invalid Transition" + line + "\n");
        }
        transElem = line[i];
        i+=2;
        while(i < line.size()) {
            next_state.push_back(line[i]);
            i++;
        }
        if (states.find(next_state) == states.end()) {
            throw std::runtime_error("Invalid Next State: " + next_state + "\n");
        }
        if(transElem == '*') {
            for(int i=0; i<255; i++) {
                transitions[starting_state][(char)i] = next_state;
            }
        } else {
            transitions[starting_state][transElem] = next_state;
        }

    }
    std::unordered_map<std::string, FAType> states;
    std::unordered_map<std::string, std::unordered_map<char, std::string>> transitions;
};
