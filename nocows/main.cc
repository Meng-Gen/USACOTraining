/*
ID: plover1
TASK: nocows
LANG: C++
*/
#include <iostream>
#include <fstream>

#define UNVISITED (-1)
#define MAX_N (201)
#define MAX_K (100)
#define MOD (9901)

using namespace std;

int pedigrees[MAX_N][MAX_K];

void InitPedigrees(int n, int h) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= h; j++) {
            pedigrees[i][j] = ((n & 1) == 0) ? 0 : UNVISITED;
        }
    }
    for (int j = 1; j <= h; j++) {
        pedigrees[1][j] = 1;
    }
}

int GetPedigree(int n, int h) {
    if (pedigrees[n][h] == UNVISITED) {
        int curr = 0;
        for (int i = 1; i < n - 1; i += 2) {
            curr = (curr + GetPedigree(i, h - 1) * GetPedigree(n - i - 1, h - 1)) % MOD;
        }
        pedigrees[n][h] = curr;
    }
    return pedigrees[n][h];
}

int main() {
    ofstream fout("nocows.out");
    ifstream fin("nocows.in");

    int N, K;
    fin >> N >> K;
    InitPedigrees(N, K);

    int solution = (GetPedigree(N, K) + MOD - GetPedigree(N, K - 1)) % MOD;
    fout << solution << '\n';

    return 0;
}