/*
ID: plover1
TASK: subset
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

typedef map<long long, long long> CountMap;

long long GetSubsetCount(int n) {
    if ((n * (n + 1) % 4) != 0) {
        return 0;
    }

    CountMap count;
    count[0] = 1;
    for (int i = 0; i < n; i++) {
        CountMap next_count(count);
        for (CountMap::iterator it = count.begin(); it != count.end(); it++) {
            next_count[(it->first) + i + 1] += it->second;
        }
        count = next_count;
    }

    return count[n * (n + 1) / 4] / 2;
}

int main() {
    ofstream fout("subset.out");
    ifstream fin("subset.in");

    int N;
    fin >> N;
    fout << GetSubsetCount(N) << '\n';

    return 0;
}