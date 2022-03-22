#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> ans(n, string(n, 'W'));

    for (int i = n - 1; i > 0; i -= 2) {
        ans[i][i] = 'B';
        for (int j = 0; j < i - 1; j++) {
            ans[i][j] = 'B';
            ans[j][i] = 'B';
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
