#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int M = 1000;
int ans[M + 1];

int check(int x) {
    auto s = to_string(x);
    int n = s.length();
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            string tmp = s.substr(i, j - i + 1);
            int val = atoi(tmp.c_str());
            if (val % 3 == 0) return 1;
        }
    }
    return 0;
}

LL solve(LL x) {
    if (x <= M) return ans[x];
    return ans[M] + (x - M);
}

int main() {
    ans[0] = 0;
    for (int i = 1; i <= M; i++) {
        ans[i] = check(i) + ans[i - 1];
    }
    int T;
    scanf("%d",&T);
    while(T--) {
        LL L, R;
        scanf("%lld%lld",&L,&R);
        printf("%lld\n",solve(R) - solve(L - 1));
    }
}