/*
ID: plover1
TASK: sprime
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>

#define PRIME_BOUND (10001)
#define SQRT_PRIME_BOUND (100)
#define PRIME_COUNT (1229)

bool visited[PRIME_BOUND] = {false};
int prime[PRIME_COUNT] = {0};

using namespace std;

void InitPrimes() {
    visited[0] = true;
    visited[1] = true;
    for (int i = 2; i <= SQRT_PRIME_BOUND; i++) {
        if (!visited[i]) {
            for (int j = i * i; j < PRIME_BOUND; j += i) {
                visited[j] = true;
            }
        }
    }
    int pos = 0;
    for (int i = 2; i < PRIME_BOUND; i++) {
        if (!visited[i]) {
            prime[pos++] = i;
        }
    }
}

bool IsPrime(int n) {
    if (n < PRIME_BOUND) {
        return !visited[n];
    }
    for (int i = 0; i < PRIME_COUNT; i++) {
        if (prime[i] * prime[i] > n) {
            return true;
        }
        if (n % prime[i] == 0) {
            return false;
        }
    }
    return true;
}

void DepthFirstSearch(int n, vector<int>& solutions, int curr_length, int length) {
    if ((curr_length > 0) && (!IsPrime(n))) {
        return;
    }
    if (curr_length == length) {
        solutions.push_back(n);
        return;
    }

    for (int i = 0; i <= 9; i++) {
        DepthFirstSearch(10 * n + i, solutions, curr_length + 1, length);
    }
}

int main() {
    InitPrimes();

    ofstream fout("sprime.out");
    ifstream fin("sprime.in");

    int N;
    fin >> N;

    vector<int> solutions;
    DepthFirstSearch(0, solutions, 0, N);
    for (int i = 0; i < solutions.size(); i++) {
        fout << solutions[i] << '\n';
    }

    return 0;
}