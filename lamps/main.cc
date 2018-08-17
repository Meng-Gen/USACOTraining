/*
ID: plover1
TASK: lamps
LANG: C++
*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

using namespace std;

struct LampState {
    bool lamp[6];

    LampState() {
        for (int i = 0; i < 6; i++) {
            lamp[i] = true;
        }
    }

    bool operator < (const LampState &other) const {
        for (int i = 0; i < 6; i++) {
            if (lamp[i] != other.lamp[i]) {
                return lamp[i] < other.lamp[i];
            }
        }
        return false;
    }

    LampState PressButton(int button) const {
        LampState output(*this);
        for (int i = 0; i < 6; i++) {
            if ((button == 1) || (button == 2 && i % 2 == 0) || (button == 3 && i % 2 == 1) || (button == 4 && i % 3 == 0)) {
                output.lamp[i] = !output.lamp[i];
            }
        }
        return output;
    }

    string ToString(int N) const {
        string output;
        for (int i = 0; i < N; i++) {
            output += (lamp[i % 6] + '0');
        }
        return output;
    }
};

typedef set<LampState> LampStates;

vector<int> ReadConfigs(ifstream& fin) {
    vector<int> configs;
    int config;
    while (true) {
        fin >> config;
        if (config == -1) {
            break;
        } else {
            configs.push_back(config);
        }
    }
    return configs;
}

LampStates GetInitialLampStates() {
    LampStates states;
    states.insert(LampState());
    return states;
}

LampStates GetNextLampStates(const LampStates& states) {
    LampStates next;
    for (LampStates::iterator it = states.begin(); it != states.end(); it++) {
        for (int button = 1; button <= 4; button++) {
            next.insert(it->PressButton(button));
        }
    }
    return next;
}

int GetEquivalentPressed(int n) {
    if (n <= 4) {
        return n;
    } else {
        return (n % 2 == 0) ? 4 : 3;
    }
}

bool IsValidLampState(LampState& state, vector<int>& on_configs, vector<int>& off_configs) {
    for (int i = 0; i < on_configs.size(); i++) {
        if (!state.lamp[(on_configs[i] - 1) % 6]) {
            return false;
        }
    }
    for (int i = 0; i < off_configs.size(); i++) {
        if (state.lamp[(off_configs[i] - 1) % 6]) {
            return false;
        }
    }
    return true;
}

int main() {
    ofstream fout("lamps.out");
    ifstream fin("lamps.in");

    int N, C;
    fin >> N >> C;
    vector<int> on_configs = ReadConfigs(fin);
    vector<int> off_configs = ReadConfigs(fin);

    int pressed = GetEquivalentPressed(C);
    LampStates lamp_states = GetInitialLampStates();
    for (int i = 0; i < pressed; i++) {
        lamp_states = GetNextLampStates(lamp_states);
    }
    vector<string> filter;
    for (LampStates::iterator it = lamp_states.begin(); it != lamp_states.end(); it++) {
        LampState state = *it;
        if (IsValidLampState(state, on_configs, off_configs)) {
            filter.push_back(it->ToString(N));
        }
    }
    sort(filter.begin(), filter.end());

    if (filter.size() == 0) {
        fout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < filter.size(); i++) {
            fout << filter[i] << '\n';
        }
    }

    return 0;
}