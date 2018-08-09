/*
ID: plover1
TASK: milk2
LANG: C++
*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");
    int N;
    fin >> N;

    vector<int> start = vector<int>(N);
    vector<int> end = vector<int>(N);
    for (int i = 0; i < N; i++) {
        fin >> start[i] >> end[i];
    }
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());

    vector<int> merged_start;
    vector<int> merged_end;
    for (int i = 0; i < N; i++) {
        if (i == N - 1 || end[i] < start[i + 1]) {
            merged_start.push_back(start[i]);
            merged_end.push_back(end[i]);
        } else if (end[i] >= start[i + 1]) {
            start[i + 1] = start[i];
        }
    }

    int milked_time = 0;
    int no_milked_time = 0;
    int merged_count = merged_start.size();
    for (int i = 0; i < merged_count; i++) {
        milked_time = max(milked_time, merged_end[i] - merged_start[i]);
        if (i < merged_count - 1) {
            no_milked_time = max(no_milked_time, merged_start[i + 1] - merged_end[i]);
        }
    }

    fout << milked_time << ' ' << no_milked_time << '\n';

    return 0;
}