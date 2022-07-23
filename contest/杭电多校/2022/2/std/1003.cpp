#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int a[N];
bitset<N> dp, low, high;
array<int, 3> v[N];

void solve() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= q; i++) {
        scanf("%d", &v[i][0]);
        if (v[i][0] == 1) {
            scanf("%d%d", &v[i][1], &v[i][2]);
        } else {
            scanf("%d", &v[i][1]);
        }
    }
    dp = 0;
    for (int i = q; i >= 1; i--) {
        if (v[i][0] == 1) {
            int l = v[i][1], r = v[i][2];
            low = dp & (~bitset<N>(0) >> (N - r - 1));
            high = dp & (~bitset<N>(0) << (r + 1));
            dp = low ^ (high >> (r + 1 - l));
        } else {
            int x = v[i][1];
            dp[x] = !dp[x];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i]) {
            ans ^= a[i];
        }
    }
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}