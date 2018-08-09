/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: plover1
TASK: dualpal
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string ConvertToBase(int number, int base) {
    string output;
    while (number > 0) {
        int digit = number % base;
        char digitLiteral = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        output += digitLiteral;
        number /= base;
    }
    return string(output.rbegin(), output.rend());
}

bool IsPalindromic(string& word) {
    for (int i = 0, j = word.size() - 1; i <= j; i++, j--) {
        if (word[i] != word[j]) {
            return false;
        }
    }
    return true;
}

bool IsDualPalindromic(int number) {
    int palindromic_count = 0;
    for (int B = 2; B <= 10; B++) {
        string literal = ConvertToBase(number, B);
        if (IsPalindromic(literal)) {
            palindromic_count++;
        }
        if (palindromic_count == 2) {
            return true;
        }
    }
    return false;
}

int main() {
    ofstream fout("dualpal.out");
    ifstream fin("dualpal.in");
    int N, S;
    fin >> N >> S;

    int found_count = 0;
    int number = S + 1;
    while (found_count < N) {
        if (IsDualPalindromic(number)) {
            fout << number << '\n';
            found_count++;
        }
        number++;
    }
    return 0;
}