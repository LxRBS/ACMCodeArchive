#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
char s[N];

void solve() {
    scanf("%s", s);
    for (int i = 0; s[i]; i++) {
        if (s[i] != ':' && s[i] != '_' && !isalpha(s[i])) {
            putchar(s[i]);
        }
    }
    puts("");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}