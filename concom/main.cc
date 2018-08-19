/*
ID: plover1
TASK: concom
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

int book_shares[101][101];
bool is_controlled[101][101] = { false };

void InitIsControlled() {
    for (int i = 1; i <= 100; i++) {
        is_controlled[i][i] = true;
        for (int j = 1; j <= 100; j++) {
            if (book_shares[i][j] >= 50) {
                is_controlled[i][j] = true;
            }
        }
    }
}

void Search(int i) {
    bool has_more = true;
    while (has_more) {
        has_more = false;
        for (int j = 1; j <= 100; j++) {
            if (!is_controlled[i][j]) {
                int real_share = 0;
                for (int k = 1; k <= 100; k++) {
                    if (is_controlled[i][k]) {
                        real_share += book_shares[k][j];
                    }
                }
                if (real_share >= 50) {
                    is_controlled[i][j] = true;
                    has_more = true;
                }
            }
        }
    }
}

int main() {
    ofstream fout("concom.out");
    ifstream fin("concom.in");

    int n;
    fin >> n;
    int i, j, p;
    for (int k = 0; k < n; k++) {
        fin >> i >> j >> p;
        book_shares[i][j] = p;
    }

    InitIsControlled();
    for (int i = 1; i <= 100; i++) {
        Search(i);
    }

    for (int i = 1; i <= 100; i++) {
        for (int j = 1; j <= 100; j++) {
            if (i != j && is_controlled[i][j]) {
                fout << i << ' ' << j << '\n';
            }
        }
    }

    return 0;
}