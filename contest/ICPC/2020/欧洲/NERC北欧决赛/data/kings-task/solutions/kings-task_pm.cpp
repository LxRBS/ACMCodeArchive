#include <bits/stdc++.h>

#define long long long int
using namespace std;

// @author: pashka

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;
    n *= 2;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    int res = INT_MAX;
    for (int st = 0; st < 2; st++) {
        auto b = a;
        for (int i = 0; i < n; i++) {
            bool ok = true;
            for (int j = 0; j < n - 1; j++) {
                if (b[j] > b[j + 1]) ok = false;
            }
            if (ok) {
                res = min(res, i);
                break;
            }
            if ((i + st) % 2) {
                for (int j = 0; j < n / 2; j++) {
                    swap(b[2 * j], b[2 * j + 1]);
                }
            } else {
                for (int j = 0; j < n / 2; j++) {
                    swap(b[j], b[j + n / 2]);
                }
            }
        }
    }

    if (res == INT_MAX) res = -1;
    cout << res << "\n";

    return 0;
}