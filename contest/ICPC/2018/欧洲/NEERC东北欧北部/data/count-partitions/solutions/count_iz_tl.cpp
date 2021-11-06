#pragma GCC optimize("O3") 
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx") 
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
void add(int &x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

int main() {
    const int N = 2e5 + 1;
    vector<int> dp(N + 1);
    dp[0] = 1;
    for (int i = 1; i <= N; i += 2) {
        for (int j = N - i; j >= 0; j--) {
            add(dp[j + i], dp[j]);
        }
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", dp[n]);
    } 
}

