/*
ID: plover1
TASK: ttwo
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

struct State {
    int x;
    int y;
    int direction;

    State() {
        x = -1;
        y = -1;
        direction = 0;
    }

    bool operator==(const State& other) const {
        return x == other.x && y == other.y;
    }
};

int dx[] = { -1, 0, 1,  0 };
int dy[] = {  0, 1, 0, -1 };

char forest[10][10];
int minutes = 0;

void Input() {
    ifstream fin("ttwo.in");
    char c;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            fin >> forest[i][j];
        }
    }
}

State GetFarmerState() {
    State state;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (forest[i][j] == 'F') {
                state.x = i;
                state.y = j;
                state.direction = 0;
            }
        }
    }
    return state;
}

State GetCowsState() {
    State state;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (forest[i][j] == 'C') {
                state.x = i;
                state.y = j;
                state.direction = 0;
            }
        }
    }
    return state;
}

void Move(State& state) {
    int next_x = state.x + dx[state.direction];
    int next_y = state.y + dy[state.direction];
    if (next_x < 0 || next_x >= 10 || next_y < 0 || next_y >= 10 || forest[next_x][next_y] == '*') {
        state.direction = (state.direction + 1) % 4;
    } else {
        state.x = next_x;
        state.y = next_y;
    }
}

void Solve() {
    State farmer_state = GetFarmerState();
    State cows_state = GetCowsState();
    for (int i = 0; i < 160000; i++) { // search space = (10 * 10 * 4)^2
        if (farmer_state == cows_state) {
            minutes = i;
            break;
        }
        Move(farmer_state);
        Move(cows_state);
    }
}

void Output() {
    ofstream fout("ttwo.out");
    fout << minutes << '\n';
}

int main() {
    Input();
    Solve();
    Output();
    return 0;
}