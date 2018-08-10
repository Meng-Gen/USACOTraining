/*
ID: plover1
TASK: milk
LANG: C++
*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Farmer {
    int price;
    int units;

    bool operator < (const Farmer& farmer) const {
        return (price < farmer.price);
    }
};

int main() {
    ofstream fout("milk.out");
    ifstream fin("milk.in");

    int N, M;
    fin >> N >> M;

    vector<Farmer> farmers(M);
    for (int i = 0; i < M; i++) {
        fin >> farmers[i].price >> farmers[i].units;
    }

    sort(farmers.begin(), farmers.end());

    int total_cost = 0;
    int total_bought = 0;
    for (int i = 0; i < M; i++) {
        int price = farmers[i].price;
        int bought = min(N - total_bought, farmers[i].units);
        total_cost += price * bought;
        total_bought += bought;
        if (total_bought == N) {
            break;
        }
    }
    fout << total_cost << '\n';

    return 0;
}