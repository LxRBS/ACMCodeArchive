#include<bits/stdc++.h>
using namespace std;

int main(void) {
    int n, e, b;
    scanf("%d%d%d", &n, &e, &b);
    vector<int> borked(n+1, false);
    for (int i = 0; i < b; ++i) {
        int x;
        scanf("%d", &x);
        borked[x] = true;
    }
    string ans = e % 2 ? "1" : "0";
    for (int i = 2; i <= n; ++i) {
        // oops: quadratic time string building
        ans = ans + (!borked[i] && e > 0 && ans.back() == '0' ? "1" : "0");
        e -= ans[i-1] != ans[i-2];
    }
    printf("%s\n", ans.c_str());
}
