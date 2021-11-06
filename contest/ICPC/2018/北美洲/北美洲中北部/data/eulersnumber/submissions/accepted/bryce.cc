#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

typedef long long ll;

int main() {
    ll n;
    cin >> n;
    long double e = 1;
    for (ll i = 1; i <= min(n, 100LL); ++i) {
        long double term = 1;
        for (ll j = 1; j <= i; ++j) {
            term /= j;
        }
        e += term;
    }
    printf("%.16Lf\n", e);
}
