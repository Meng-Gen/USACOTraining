/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: plover1
TASK: friday
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool IsLeapYear(int year) {
    if (year % 400 == 0) {
        return true;
    } else if (year % 100 == 0) {
        return false;
    } else {
        return year % 4 == 0;
    }
}

int main() {
    ofstream fout("friday.out");
    ifstream fin("friday.in");
    int N;
    fin >> N;

    int counts[7] = {0};
    int total_days = 0;
    for (int i = 1; i <= N; i++) {
        int year = 1900 + i - 1;
        for (int j = 0; j < 12; j++) {
            counts[(total_days + 5) % 7]++;
            total_days += days_in_month[j];
            if ((j == 1) && IsLeapYear(year)) {
                total_days++;
            }
        }
    }

    for (int i = 0; i < 7; i++) {
        fout << counts[(i + 5) % 7];
        fout << ((i < 6) ? ' ' : '\n');
    }
    return 0;
}