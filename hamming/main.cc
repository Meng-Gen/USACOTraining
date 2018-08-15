/*
ID: plover1
TASK: hamming
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int GetHammingDistance(int a, int b, int length) {
    int distance = 0;
    for (int i = 0; i < length; i++) {
        if ((a & (1 << i)) != (b & (1 << i))) {
            distance++;
        }
    }
    return distance;
}

bool IsSatisfied(int n, vector<int>& codewords, int min_distance, int length) {
    for (int i = 0; i < codewords.size(); i++) {
        if (GetHammingDistance(n, codewords[i], length) < min_distance) {
            return false;
        }
    }
    return true;
}

int main() {
    ofstream fout("hamming.out");
    ifstream fin("hamming.in");

    int N, B, D;
    fin >> N >> B >> D;

    vector<int> codewords;
    for (int i = 0; i < (1 << B); i++) {
        if (IsSatisfied(i, codewords, D, B)) {
            codewords.push_back(i);
        }
        if (codewords.size() == N) {
            break;
        }
    }

    for (int i = 0; i < codewords.size(); i++) {
        fout << codewords[i] << (((i + 1) % 10 == 0 || i == codewords.size() - 1) ? '\n' : ' ');
    }

    return 0;
}