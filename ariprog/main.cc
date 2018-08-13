/*
ID: plover1
TASK: ariprog
LANG: C++
*/
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream fout("ariprog.out");
    ifstream fin("ariprog.in");

    int N, M;
    fin >> N >> M;

    bool visited[125001];
    int square_sums[125001];
    int S = 0;
    for (int p = 0; p <= M; p++) {
        for (int q = 0; q <= M; q++) {
            int i = p * p + q * q;
            if (!visited[i]) {
                visited[i] = true;
                square_sums[S++] = i;
            }
        }
    }

    sort(square_sums, square_sums + S);

    int a0_array[10001] = {0};
    int d_array[10001] = {0};
    int solution_count = 0;
    for (int i = 0; i < S; i++) {
        for (int j = i + 1; j < S; j++) {
            int a0 = square_sums[i];
            int d = square_sums[j] - square_sums[i];
            int last_term = a0 + (N - 1) * d;
            if (last_term > square_sums[S - 1]) {
                break;
            }

            int k = 1;
            for (; k < N; k++) {
                if (!visited[a0 + k * d]) {
                    break;
                }
            }
            if (k == N) {
                a0_array[solution_count] = a0;
                d_array[solution_count] = d;
                solution_count++;
            }
        }
    }

    if (solution_count == 0) {
        fout << "NONE\n";
    } else {
        for (int i = 1; i < solution_count; i++) {
            int d = d_array[i];
            int a0 = a0_array[i];
            int j = i - 1;
            while (j >= 0 && d_array[j] > d) {
                d_array[j + 1] = d_array[j];
                a0_array[j + 1] = a0_array[j];
                j--;
            }
            d_array[j + 1] = d;
            a0_array[j + 1] = a0;
        }
        for (int i = 0; i < solution_count; i++) {
            fout << a0_array[i] << ' ' << d_array[i] << '\n';
        }
    }

    return 0;
}