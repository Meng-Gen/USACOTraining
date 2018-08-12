/*
ID: plover1
TASK: skidesign
LANG: C++
*/
#include <limits.h> // INT_MAX
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int GetCost(vector<int>& hills, int lower_bound, int upper_bound) {
    int cost = 0;
    for (int i = 0; i < hills.size(); i++) {
        if (hills[i] < lower_bound) {
            cost += (lower_bound - hills[i]) * (lower_bound - hills[i]);
        } else if (hills[i] > upper_bound) {
            cost += (hills[i] - upper_bound) * (hills[i] - upper_bound);
        }
    }
    return cost;
}

int main() {
    ofstream fout("skidesign.out");
    ifstream fin("skidesign.in");

    int N;
    fin >> N;
    vector<int> hills(N);
    for (int i = 0; i < N; i++) {
        fin >> hills[i];
    }

    int min_cost = INT_MAX;
    for (int lower_bound = 0; lower_bound <= 100 - 17; lower_bound++) {
        min_cost = min(min_cost, GetCost(hills, lower_bound, lower_bound + 17));
    }

    fout << min_cost << '\n';

    return 0;
}