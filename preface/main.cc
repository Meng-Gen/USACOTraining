/*
ID: plover1
TASK: preface
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

char roman_digits[7] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
int values[13] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
int value_roman_digit_map[13][7] = {
    { 0, 0, 0, 0, 0, 0, 1 }, // 1000 = M
    { 0, 0, 0, 0, 1, 0, 1 }, // 900 = CM
    { 0, 0, 0, 0, 0, 1, 0 }, // 500 = D
    { 0, 0, 0, 0, 1, 1, 0 }, // 400 = CD
    { 0, 0, 0, 0, 1, 0, 0 }, // 100 = C
    { 0, 0, 1, 0, 1, 0, 0 }, // 90 = XC
    { 0, 0, 0, 1, 0, 0, 0 }, // 50 = L
    { 0, 0, 1, 1, 0, 0, 0 }, // 40 = XL
    { 0, 0, 1, 0, 0, 0, 0 }, // 10 = X
    { 1, 0, 1, 0, 0, 0, 0 }, // 9 = IX
    { 0, 1, 0, 0, 0, 0, 0 }, // 5 = V
    { 1, 1, 0, 0, 0, 0, 0 }, // 4 = IV
    { 1, 0, 0, 0, 0, 0, 0 }, // 1 = I
};

int main() {
    ofstream fout("preface.out");
    ifstream fin("preface.in");

    int N;
    fin >> N;

    int counting[7] = {0};
    for (int i = 1; i <= N; i++) {
        int n = i;
        for (int j = 0; j < 13; j++) {
            if (n >= values[j]) {
                int repeated_count = n / values[j];
                n %= values[j];
                for (int k = 0; k < 7; k++) {
                    counting[k] += repeated_count * value_roman_digit_map[j][k];
                }
            }
        }
    }

    for (int i = 0; i < 7; i++) {
        if (counting[i] > 0) {
            fout << roman_digits[i] << ' ' << counting[i] << '\n';
        }
    }

    return 0;
}