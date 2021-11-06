#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    while (cin >> n >> k) {
        map<string, int> mp;
        for (int i = 0; i < k; i++) {
            string s;
            int cnt = 1;
            while (1) {
                cin >> s;
                if (s == "Re:") cnt++;
                else break;
            }
            mp[s] = max(mp[s], cnt);
        }
        int sum = 0, mx = 0;
        for (auto it : mp) {
            sum += it.second;
            mx = max(mx, it.second);
        }
        if (sum > n) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
}
