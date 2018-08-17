/*
ID: plover1
TASK: zerosum
LANG: C++
*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int Power(int a, int n) {
    int result = 1;
    while (n-- > 0) {
        result *= a;
    }
    return result;
}

string ConfigToString(int config, int N) {
    string result("1");
    int n = config;
    for (int i = 1; i < N; i++) {
        int op = n % 3;
        if (op == 0) {
            result += '+';
        } else if (op == 1) {
            result += '-';
        } else if (op == 2) {
            result += ' ';
        }
        result += (i + 1 + '0');
        n /= 3;
    }
    return result;
}

bool IsSatisfied(int config, int N) {
    int n = config;
    int total_sum = 0;
    int sign = 1;
    int buffer = 1;
    for (int i = 1; i < N; i++) {
        int op = n % 3;
        if (op == 0) {
            total_sum += (sign * buffer);
            sign = 1;
            buffer = i + 1;
        } else if (op == 1) {
            total_sum += (sign * buffer);
            sign = -1;
            buffer = i + 1;
        } else if (op == 2) {
            buffer = 10 * buffer + (i + 1);
        }
        n /= 3;
    }
    total_sum += (sign * buffer);
    return total_sum == 0;
}

int main() {
    ofstream fout("zerosum.out");
    ifstream fin("zerosum.in");

    int N;
    fin >> N;

    vector<string> solutions;
    for (int i = 0; i < Power(3, N - 1); i++) {
        if (IsSatisfied(i, N)) {
            solutions.push_back(ConfigToString(i, N));
        }
    }
    sort(solutions.begin(), solutions.end());

    for (int i = 0; i < solutions.size(); i++) {
        fout << solutions[i] << '\n';
    }
    return 0;
}