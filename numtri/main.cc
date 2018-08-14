/*
ID: plover1
TASK: numtri
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream fout("numtri.out");
    ifstream fin("numtri.in");

    int R;
    fin >> R;
    int triangles[1000][1000] = {0};
    for (int i = 0; i < R; i++) {
        for (int j = 0; j <= i; j++) {
            fin >> triangles[i][j];
        }
    }

    for (int i = R - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            triangles[i][j] += max(triangles[i + 1][j], triangles[i + 1][j + 1]);
        }
    }

    fout << triangles[0][0] << '\n';

    return 0;
}