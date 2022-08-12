#include <bits/stdc++.h>
using namespace std;

int main(void) {
    typedef pair<int, int> pii;
    int T; scanf("%d", &T);
    while (T--) {
        int n; scanf("%d", &n);
        vector<int> w(n);
        vector<int> c(n, 0);
        c[0] = 0;
        c[1] = 1;
        c[2] = 2;
        for (int i = 0; i < n; ++i)
            scanf("%d", &w[i]);

        for (int i = 3; i < n; ++i) {
            int j, k;
            scanf("%d %d", &j, &k);
            j--; k--;
            c[i] = (3 - c[j] - c[k]) % 3;
        }

        long long ans[3] = { 0, 0, 0 };
        for (int i = 0; i < n; ++i)
            ans[c[i]] += w[i];

        cout << max({ ans[0], ans[1], ans[2] }) << endl;
    }

    return 0;
}