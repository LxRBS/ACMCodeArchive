#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> pr(n + 1, -1);
    pr[0] = 0;
    for (int i = 1; i <= n; i += 2) {
        for (int j = n - i; j >= 0; j--) {
            if (pr[j] == -1) continue;
            if (pr[j + i] == -1) pr[j + i] = i;
        }
    }
    if (pr[n] == -1) {
        cout << -1 << endl;
    } else {
        vector<int> a;
        while (n) {
            a.push_back(pr[n]);
            n -= pr[n];
        }
        int k = (a[0] + 1) / 2;
        vector<string> b(k, string(k, '.'));
        for (int i = 0; i < (int)a.size(); i++) {
            for (int j = 0; j <= a[i] / 2; j++) {
                b[i][i + j] = b[i + j][i] = 'o';
            }
        }
        reverse(b.begin(), b.end());
        cout << k << endl;
        for (string s : b) cout << s << endl;
    }
}
