/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: plover1
TASK: ride
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int GetNumber(string& s) {
    int number = 1;
    for (string::size_type i = 0; i < s.size(); i++) {
        number = (number * (s[i] - 'A' + 1)) % 47;
    }
    return number;
}

int main() {
    ofstream fout("ride.out");
    ifstream fin("ride.in");
    string s, t;
    fin >> s >> t;
    fout << ((GetNumber(s) == GetNumber(t)) ? "GO" : "STAY") << '\n';
    return 0;
}