/*
ID: plover1
TASK: crypt1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

bool IsThreeDigitsNumber(int number) {
    return (number >= 100) && (number < 1000);
}

bool IsFourDigitsNumber(int number) {
    return (number >= 1000) && (number < 10000);
}

bool IsValidNumber(int number, set<int>& digits) {
    int digit;
    while (number > 0) {
        digit = number % 10;
        if (digits.find(digit) == digits.end()) {
            return false;
        }
        number /= 10;
    }
    return true;
}

bool IsSolution(int abc, int de, set<int>& digits) {
    int d = de / 10;
    int e = de % 10;
    return IsValidNumber(abc, digits)
        && IsValidNumber(de, digits)
        && IsValidNumber(abc * e, digits) && IsThreeDigitsNumber(abc * e)
        && IsValidNumber(abc * d, digits) && IsThreeDigitsNumber(abc * d)
        && IsValidNumber(abc * de, digits) && IsFourDigitsNumber(abc * de);
}

int main() {
    ofstream fout("crypt1.out");
    ifstream fin("crypt1.in");

    int N;
    fin >> N;

    set<int> digits;
    int digit;
    for (int i = 0; i < N; i++) {
        fin >> digit;
        digits.insert(digit);
    }

    int count = 0;
    for (int abc = 100; abc < 1000; abc++) {
        for (int de = 10; de < 100; de++) {
            if (IsSolution(abc, de, digits)) {
                count++;
            }
        }
    }
    fout << count << '\n';

    return 0;
}