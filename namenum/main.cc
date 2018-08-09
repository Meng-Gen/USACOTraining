/*
ID: plover1
TASK: namenum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef map< string, vector<string> > LookupTable;

string GetNumber(string& word) {
    int N = word.length();
    string number(N, '\0');
    for (int i = 0; i < N; i++) {
        char c = word[i];
        if (c == 'Q' || c == 'Z') {
            number[i] = c;
        } else if (word[i] <= 'P') {
            number[i] = (char)((word[i] - 'A') / 3 + 2 + '0');
        } else {
            number[i] = (char)((word[i] - 'A' - 1) / 3 + 2 + '0');
        }
    }
    return number;
}

LookupTable BuildLookupTable() {
    LookupTable table;
    ifstream dict("dict.txt");
    string word;
    while (!dict.eof()) {
        dict >> word;
        string number = GetNumber(word);
        if (table.find(number) == table.end()) {
            table[number] = vector<string>();
        }
        table[GetNumber(word)].push_back(word);
    }
    return table;
}

int main() {
    ofstream fout("namenum.out");
    ifstream fin("namenum.in");
    LookupTable table = BuildLookupTable();
    string number;
    fin >> number;
    if (table.find(number) == table.end()) {
        fout << "NONE\n";
    } else {
        for (int i = 0; i < table[number].size(); i++) {
            fout << table[number][i] << '\n';
        }
    }
    return 0;
}