/*
ID: plover1
TASK: barn1
LANG: C++
*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ofstream fout("barn1.out");
    ifstream fin("barn1.in");

    int M, S, C;
    fin >> M >> S >> C;

    vector<int> stalls(C);
    for (int i = 0; i < C; i++) {
        fin >> stalls[i];
    }

    sort(stalls.begin(), stalls.end());

    vector<int> gaps;
    int prev_stall = 0;
    for (int i = 0; i < C; i++) {
        if (i > 0) {
            int gap = stalls[i] - prev_stall - 1;
            if (gap > 0) {
                gaps.push_back(gap);
            }
        }
        prev_stall = stalls[i];
    }
    sort(gaps.rbegin(), gaps.rend());

    int min_arrangement = stalls[C - 1] - stalls[0] + 1;
    int greedy_bound = min(M, (int)(gaps.size()) + 1);
    for (int i = 1; i < greedy_bound; i++) {
        min_arrangement -= gaps[i - 1];
    }
    fout << min_arrangement << '\n';

    return 0;
}