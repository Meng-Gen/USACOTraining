/*
ID: plover1
TASK: combo
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int GetOverlapCount(int x, int y, int N) {
    set<int> x_overlap;
    set<int> y_overlap;
    for (int i = 0; i < 5; i++) {
        x_overlap.insert((x + N - 3 + i) % N + 1);
        y_overlap.insert((y + N - 3 + i) % N + 1);
    }

    int count = 0;
    for (set<int>::iterator it = y_overlap.begin(); it != y_overlap.end(); ++it) {
        if (x_overlap.find(*it) != x_overlap.end()) {
            count++;
        }
    }
    return count;
}

int main() {
    ofstream fout("combo.out");
    ifstream fin("combo.in");

    int N;
    fin >> N;

    int farmer[3], master[3];
    for (int i = 0; i < 3; i++) {
        fin >> farmer[i];
    }
    for (int i = 0; i < 3; i++) {
        fin >> master[i];
    }

    int width = min(5, N);
    int combination_count = width * width * width;

    int common_count = 1;
    for (int i = 0; i < 3; i++) {
        common_count *= GetOverlapCount(farmer[i], master[i], N);
    }

    fout << (2 * combination_count - common_count) << '\n';

    return 0;
}