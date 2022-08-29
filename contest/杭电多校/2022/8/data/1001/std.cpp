//1001, std
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

char s[MAXN];
int n, cnt[2][2];

void solve() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    cnt[0][0] = cnt[0][1] = cnt[1][0] = cnt[1][1] = 0;
    for (int i = 1; i <= n; ++i) {
        ++cnt[i & 1][s[i] == '1'];
    }
    for (int i = 1; i <= n; ++i) {
        if (cnt[i & 1][0]) {
            putchar('0');
            --cnt[i & 1][0];
        } else {
            putchar('1');
        }
    }
    puts("");
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
