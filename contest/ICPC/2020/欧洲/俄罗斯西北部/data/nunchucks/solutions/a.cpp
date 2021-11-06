#include <bits/stdc++.h>
#define long long long int
using namespace std;

// @author: pashka

const int MAX = 50;
long c[MAX + 1][MAX + 1];

long calc(int n, int k) {
    assert(n <= MAX && k >= 0 && k <= n);
    long r = c[n][k];
    if (n % 2 == 1 || k % 2 == 0) {
        int nn = n / 2;
        int kk = k / 2;
        r += c[nn][kk];
    }
    assert(r % 2 == 0);
    r /= 2;
    return r;
}

int main() {
    ios::sync_with_stdio(false);

    for (int i = 0; i <= MAX; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }

    int n, k;
    cin >> n >> k;
    long res = 0;
    for (int k1 = 0; k1 <= k; k1++) {
        int k2 = k - k1;
        if (k1 > n || k2 > n) continue;
        long q = calc(n, k1);
        if (k1 == k2) {
            res += 2 * q;
        } else {
            res += q;
        }
    }
    cout << res << "\n";
    return 0;
}