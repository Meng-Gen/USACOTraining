/*
ID: plover1
TASK: money
LANG: C++
*/
#include <iostream>
#include <fstream>

#define MAX_COIN_COUNT (26)
#define MAX_MONEY (10001)

using namespace std;

int main() {
    ofstream fout("money.out");
    ifstream fin("money.in");

    int V, N;
    fin >> V >> N;

    long long coins[MAX_COIN_COUNT];
    coins[0] = 0; // set 0 as a special coin for simplicity.
    for (int i = 1; i <= V; i++) {
        fin >> coins[i];
    }
    long long coin_change[MAX_MONEY][MAX_COIN_COUNT];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= V; j++) {
            if (i == 0) {
                coin_change[i][j] = 1;
            } else if (j == 0) {
                coin_change[i][j] = 0;
            } else if (coins[j] > i) {
                coin_change[i][j] = coin_change[i][j - 1];
            } else {
                coin_change[i][j] = coin_change[i][j - 1] + coin_change[i - coins[j]][j];
            }
        }
    }
    fout << coin_change[N][V] << '\n';

    return 0;
}