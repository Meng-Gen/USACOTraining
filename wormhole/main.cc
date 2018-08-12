/*
ID: plover1
TASK: wormhole
LANG: C++
*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

#define INVALID_ID (-1)

using namespace std;

struct Point {
    int x;
    int y;

    bool operator < (const Point& other) const {
        return (y == other.y) ? (x < other.x) : y < other.y;
    }
};

typedef vector<int> IntegerList;
typedef vector<Point> PointList;

IntegerList GetRightmostNeighborhood(PointList& sortedWormholes, int N) {
    IntegerList neighborhood(N, INVALID_ID);
    for (int i = 0; i < N - 1; i++) {
        if (sortedWormholes[i].y == sortedWormholes[i + 1].y) {
            neighborhood[i] = i + 1;
        }
    }
    return neighborhood;
}

int GetFirstUnpairedPos(IntegerList& pair, int N) {
    for (int i = 0; i < N; i++) {
        if (pair[i] == INVALID_ID) {
            return i;
        }
    }
    return N;
}

void Backtrack(vector<IntegerList>& all_pairs, IntegerList& curr_pair, int N) {
    int i = GetFirstUnpairedPos(curr_pair, N);
    if (i == N) {
        all_pairs.push_back(IntegerList(curr_pair));
    } else {
        for (int j = i + 1; j < N; j++) {
            if (curr_pair[j] == INVALID_ID) {
                curr_pair[i] = j;
                curr_pair[j] = i;
                Backtrack(all_pairs, curr_pair, N);
                curr_pair[i] = INVALID_ID;
                curr_pair[j] = INVALID_ID;
            }
        }
    }
}

vector<IntegerList> GetAllPairs(int N) {
    vector<IntegerList> all_pairs;
    IntegerList curr_pair(N, INVALID_ID);
    Backtrack(all_pairs, curr_pair, N);
    return all_pairs;
}

bool IsInCycle(IntegerList& pair, IntegerList& neighborhood, int N) {
    for (int i = 0; i < N; i++) {
        int pos = i;
        for (int j = 0; j < N; j++) {
            if (pos == INVALID_ID) {
                break;
            }
            pos = neighborhood[pair[pos]];
        }
        if (pos != INVALID_ID) {
            return true;
        }
    }
    return false;
}

int main() {
    ofstream fout("wormhole.out");
    ifstream fin("wormhole.in");

    int N;
    fin >> N;
    PointList wormholes(N);
    for (int i = 0; i < N; i++) {
        fin >> wormholes[i].x >> wormholes[i].y;
    }

    sort(wormholes.begin(), wormholes.end());
    IntegerList neighborhood = GetRightmostNeighborhood(wormholes, N);

    int solution_count = 0;
    vector<IntegerList> all_pairs = GetAllPairs(N);
    for (int i = 0; i < all_pairs.size(); i++) {
        if (IsInCycle(all_pairs[i], neighborhood, N)) {
            solution_count++;
        }
    }
    fout << solution_count << '\n';

    return 0;
}