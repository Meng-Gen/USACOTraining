/*
ID: plover1
TASK: runround
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool HasRepeatedDigits(int n) {
    bool visited[10] = {false};
    while (n > 0) {
        int digit = n % 10;
        if (visited[digit]) {
            return true;
        }
        visited[digit] = true;
        n /= 10;
    }
    return false;
}

bool IsCyclic(int n) {
    string num_literal = to_string(n);
    int num_length = num_literal.size();
    int curr_pos = 0;
    for (int i = 0; i < num_length; i++) {
        curr_pos = (curr_pos + num_literal[curr_pos] - '0') % num_length;
        if (i < num_length - 1 && curr_pos == 0) {
            return false;
        }
    }
    return curr_pos == 0;
}

int main() {
    ofstream fout("runround.out");
    ifstream fin("runround.in");

    int N;
    fin >> N;

    for (int i = N + 1; ; i++) {
        if (!HasRepeatedDigits(i) && IsCyclic(i)) {
            fout << i << '\n';
            break;
        }
    }

    return 0;
}