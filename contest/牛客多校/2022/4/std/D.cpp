#include <bits/stdc++.h>
using namespace std;

const int P = 998244353;
int add(int a, int b) { a += b; return a < P ? a : a - P; }
int mul(int a, int b) { return 1ll * a * b % P; }

const int M = 401;
short g[M][M][M], pc[1<<10];

int main(void) {
    for (int i = 1; i < (1 << 10); ++i) pc[i] = pc[i >> 1] + (i & 1);

    int n, q; scanf("%d %d", &n, &q);
    for (int i = 0; i < n; ++i) {
        int k; scanf("%d", &k);
        while (k--) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            g[a][b][c] |= (1 << i);
        }
    }

    for (int i = 0; i + 1 < M; ++i)
        for (int j = 0; j < M; ++j)
            for (int k = 0; k < M; ++k)
                g[i + 1][j][k] |= g[i][j][k];

                
    for (int j = 0; j + 1 < M; ++j)
        for (int i = 0; i < M; ++i)
            for (int k = 0; k < M; ++k)
                g[i][j + 1][k] |= g[i][j][k];
    
    for (int k = 0; k + 1 < M; ++k)
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < M; ++j)
                g[i][j][k + 1] |= g[i][j][k];

    int seed, lastans = 0;
    scanf("%d", &seed);
    std::mt19937 rng(seed);
    std::uniform_int_distribution<> u(1,400);
    int ans = 0, cnt = 0;
    while (q--) {
        int IQ=(u(rng)^lastans)%400+1;  // The IQ of the i-th friend
        int EQ=(u(rng)^lastans)%400+1;  // The EQ of the i-th friend
        int AQ=(u(rng)^lastans)%400+1;  // The AQ of the i-th friend
        lastans=pc[g[IQ][EQ][AQ]];  // The answer to the i-th friend
        // printf("%d %d %d %d\n", IQ, EQ, AQ, lastans);
        ans = add(mul(ans, seed), lastans);
        // if (++cnt == 100) break;
    }
    printf("%d\n", ans);

    return 0;
}