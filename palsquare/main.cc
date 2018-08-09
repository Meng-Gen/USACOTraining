/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: plover1
TASK: palsquare
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

int main() {
    ofstream fout("palsquare.out");
    ifstream fin("palsquare.in");
    int B;
    fin >> B;

    for (int i = 1; i <= 300; i++) {
        string numberLiteral = ConvertToBase(i, B);
        string squareLiteral = ConvertToBase(i * i, B);
        if (IsPalindromic(squareLiteral)) {
            fout << numberLiteral << ' ' << squareLiteral << '\n';
        }
    }
    return 0;
}