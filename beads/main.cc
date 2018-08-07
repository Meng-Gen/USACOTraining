/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: plover1
TASK: beads
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ofstream fout("beads.out");
    ifstream fin("beads.in");
    int n;
    string s;
    fin >> n >> s;

    vector<int> leftmost_red = vector<int>(2 * n + 1);
    vector<int> leftmost_blue = vector<int>(2 * n + 1);
    vector<int> rightmost_red = vector<int>(2 * n + 1);
    vector<int> rightmost_blue = vector<int>(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++) {
        char color = s[(i - 1) % n];
        if (color == 'r') {
            leftmost_red[i] = leftmost_red[i - 1] + 1;
            leftmost_blue[i] = 0;
        } else if (color == 'b') {
            leftmost_red[i] = 0;
            leftmost_blue[i] = leftmost_blue[i - 1] + 1;
        } else {
            leftmost_red[i] = leftmost_red[i - 1] + 1;
            leftmost_blue[i] = leftmost_blue[i - 1] + 1;
        }
    }
    for (int i = 2 * n - 1; i >= 0; i--) {
        char color = s[i % n];
        if (color == 'r') {
            rightmost_red[i] = rightmost_red[i + 1] + 1;
            rightmost_blue[i] = 0;
        } else if (color == 'b') {
            rightmost_red[i] = 0;
            rightmost_blue[i] = rightmost_blue[i + 1] + 1;
        } else {
            rightmost_red[i] = rightmost_red[i + 1] + 1;
            rightmost_blue[i] = rightmost_blue[i + 1] + 1;
        }
    }

    int max_so_far = 0;
    for (int i = 0; i < 2 * n + 1; i++) {
        max_so_far = max(max_so_far, leftmost_red[i] + rightmost_blue[i]);
        max_so_far = max(max_so_far, leftmost_blue[i] + rightmost_red[i]);
    }
    fout << min(n, max_so_far) << '\n';
    return 0;
}