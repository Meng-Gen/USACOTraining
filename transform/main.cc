/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: plover1
TASK: transform
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Pattern {
    vector< vector<char> > content;

    Pattern(int N) {
        content = vector< vector<char> >(N);
        for (int i = 0; i < N; i++) {
            content[i] = vector<char>(N);
        }
    }

    Pattern Rotate() {
        int N = content.size();
        Pattern rotation = Pattern(N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                rotation.content[j][N - 1 - i] = content[i][j];
            }
        }
        return rotation;
    }

    Pattern Reflect() {
        int N = content.size();
        Pattern reflection = Pattern(N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                reflection.content[i][N - 1 - j] = content[i][j];
            }
        }
        return reflection;
    }

    bool Equals(Pattern& another) {
        int N = content.size();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (content[i][j] != another.content[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
};

Pattern ReadPatternFromFile(ifstream& fin, int N) {
    Pattern pattern = Pattern(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> pattern.content[i][j];
        }
    }
    return pattern;
}

int main() {
    ofstream fout("transform.out");
    ifstream fin("transform.in");
    int N;
    fin >> N;

    Pattern before = ReadPatternFromFile(fin, N);
    Pattern after = ReadPatternFromFile(fin, N);

    if (before.Rotate().Equals(after)) {
        fout << "1\n";
    } else if (before.Rotate().Rotate().Equals(after)) {
        fout << "2\n";
    } else if (before.Rotate().Rotate().Rotate().Equals(after)) {
        fout << "3\n";
    } else if (before.Reflect().Equals(after)) {
        fout << "4\n";
    } else if (before.Reflect().Rotate().Equals(after)) {
        fout << "5\n";
    } else if (before.Reflect().Rotate().Rotate().Equals(after)) {
        fout << "5\n";
    } else if (before.Reflect().Rotate().Rotate().Rotate().Equals(after)) {
        fout << "5\n";
    } else if (before.Equals(after)) {
        fout << "6\n";
    } else {
        fout << "7\n";
    }
    return 0;
}