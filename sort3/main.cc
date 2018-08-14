/*
ID: plover1
TASK: sort3
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream fout("sort3.out");
    ifstream fin("sort3.in");

    int N;
    fin >> N;

    int values[1000] = {0};
    int value_counts[3] = {0};
    int swapping_map[3][3] = {0};
    for (int i = 0; i < N; i++) {
        fin >> values[i];
        value_counts[values[i] - 1]++;
    }

    int begin_pos = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < value_counts[i]; j++) {
            swapping_map[i][values[begin_pos + j] - 1]++;
        }
        begin_pos += value_counts[i];
    }

    int swapping_count = 0;
    swapping_count += min(swapping_map[0][1], swapping_map[1][0]); // 1 <-> 2
    swapping_count += min(swapping_map[1][2], swapping_map[2][1]); // 2 <-> 3
    swapping_count += min(swapping_map[2][0], swapping_map[0][2]); // 3 <-> 1
    swapping_count += 2 * abs(swapping_map[0][1] - swapping_map[1][0]); // 1 -> 2 -> 3
    fout << swapping_count << '\n';

    return 0;
}