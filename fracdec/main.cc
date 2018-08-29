/*
ID: plover1
TASK: fracdec
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void Output(string& literal, ofstream& fout) {
    for (int i = 0; i < literal.size(); i++) {
        fout << literal[i];
        if ((i == literal.size() - 1) || ((i + 1) % 76 == 0)) {
            fout << '\n';
        }
    }
}

string GetIntegerLiteral(int n, int d) {
    return to_string(n / d) + ".0";
}

string GetFractionLiteral(int n, int d) {
    string literal = to_string(n / d) + ".";
    n -= (n / d) * d;

    map<int, int> visited;
    vector<int> digits;
    int curr_pos = 0;
    int repeating_start_pos = -1;
    while (n != 0) {
        n *= 10;
        if (visited.find(n) != visited.end()) {
            repeating_start_pos = visited[n];
            break;
        }
        visited[n] = curr_pos++;
        digits.push_back(n / d);
        n -= (n / d) * d;
    }

    for (int i = 0; i < digits.size(); i++) {
        if (i == repeating_start_pos) {
            literal += "(";
        }
        literal += to_string(digits[i]);
    }
    if (repeating_start_pos != -1) {
        literal += ")";
    }
    return literal;
}

int main() {
    ofstream fout("fracdec.out");
    ifstream fin("fracdec.in");

    int n, d;
    fin >> n >> d;

    string literal = (n % d == 0) ? GetIntegerLiteral(n, d) : GetFractionLiteral(n, d);
    Output(literal, fout);

    return 0;
}