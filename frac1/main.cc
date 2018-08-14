/*
ID: plover1
TASK: frac1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void DepthFirstSearch(int N, ofstream& fout, int begin_n, int begin_d, int end_n, int end_d) {
    int middle_n = begin_n + end_n;
    int middle_d = begin_d + end_d;
    if (middle_d > N) {
        return;
    }
    DepthFirstSearch(N, fout, begin_n, begin_d, middle_n, middle_d);
    fout << middle_n << '/' << middle_d << '\n';
    DepthFirstSearch(N, fout, middle_n, middle_d, end_n, end_d);
}

int main() {
    ofstream fout("frac1.out");
    ifstream fin("frac1.in");

    int N;
    fin >> N;

    fout << "0/1\n";
    DepthFirstSearch(N, fout, 0, 1, 1, 1);
    fout << "1/1\n";

    return 0;
}