/*
ID: plover1
TASK: pprime
LANG: C++
*/
#include <iostream>
#include <fstream>

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

// BuildOddPalindrome(123, 6) returns 1236321.
int BuildOddPalindrome(int n, int middle_digit) {
    int palindrome = 10 * n + middle_digit;
    while (n > 0) {
        palindrome = 10 * palindrome + (n % 10);
        n = n / 10;
    }
    return palindrome;
}

int main() {
    InitPrimes();

    ofstream fout("pprime.out");
    ifstream fin("pprime.in");

    int a, b;
    fin >> a >> b;

    // Get all possible prime palindrome. Note that the only possible prime palindrome of even length is 11.
    for (int i = 0; i <= 999; i++) {
        for (int middle_digit = 0; middle_digit <= 9; middle_digit++) {
            int n = BuildOddPalindrome(i, middle_digit);
            if (n < a) {
                continue;
            } else if (n > b) {
                break;
            }
            if (IsPrime(n)) {
                fout << n << '\n';
            }
        }
        if (i == 0) {
            if ((a <= 11) && (11 <= b)) {
                fout << "11\n";
            }
        }
    }

    return 0;
}