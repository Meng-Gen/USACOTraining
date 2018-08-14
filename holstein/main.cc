/*
ID: plover1
TASK: holstein
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> GetBitPositions(int bitmask, int G) {
    vector<int> position;
    for (int i = 0; i < G; i++) {
        if (bitmask & (1 << i)) {
            position.push_back(i);
        }
    }
    return position;
}

int main() {
    ofstream fout("holstein.out");
    ifstream fin("holstein.in");

    // Input
    int V;
    fin >> V;

    int min_vitamins[25] = {0};
    for (int i = 0; i < V; i++) {
        fin >> min_vitamins[i];
    }

    int G;
    fin >> G;

    int feeds[15][25] = {0};
    for (int i = 0; i < G; i++) {
        for (int j = 0; j < V; j++) {
            fin >> feeds[i][j];
        }
    }

    // Check all possible subsets of feeds. (2^15 = 32768 is small enough.)
    int min_feed_count = G + 1;
    vector<int> min_subset;
    for (int bitmask = 0; bitmask < (1 << G); bitmask++) {
        vector<int> subset = GetBitPositions(bitmask, G);
        int feed_subset[25] = {0};
        for (int i = 0; i < subset.size(); i++) {
            for (int j = 0; j < V; j++) {
                feed_subset[j] += feeds[subset[i]][j];
            }
        }

        int i = 0;
        for (; i < V; i++) {
            if (feed_subset[i] < min_vitamins[i]) {
                break;
            }
        }
        if ((i == V) && (subset.size() < min_feed_count)) {
            min_feed_count = subset.size();
            min_subset = subset;
        }
    }

    fout << min_subset.size() << ' ';
    for (int i = 0; i < min_subset.size(); i++) {
        fout << min_subset[i] + 1 << ((i == min_subset.size() - 1) ? '\n' : ' ');
    }

    return 0;
}