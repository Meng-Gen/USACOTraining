/*
ID: plover1
TASK: prefix
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ofstream fout("prefix.out");
    ifstream fin("prefix.in");

    vector<string> primitive_list;
    string primitive;
    while (true) {
        fin >> primitive;
        if (primitive == ".") {
            break;
        }
        primitive_list.push_back(primitive);
    }
    string sequence;
    string buffer;
    getline(fin, buffer); // consume the last newline of primitives.
    while (getline(fin, buffer)) {
        sequence += buffer;
    }

    vector<bool> visited(sequence.size() + 1);
    visited[0] = true;
    for (int i = 1; i < visited.size(); i++) {
        for (int j = 0; j < primitive_list.size(); j++) {
            primitive = primitive_list[j];
            int length = primitive.size();
            if (i >= length
                    && visited[i - length]
                    && sequence.substr(i - length, length) == primitive)
            {
                visited[i] = true;
                break;
            }
        }
    }

    for (int i = visited.size() - 1; i >= 0; i--) {
        if (visited[i]) {
            fout << i << '\n';
            break;
        }
    }

    return 0;
}