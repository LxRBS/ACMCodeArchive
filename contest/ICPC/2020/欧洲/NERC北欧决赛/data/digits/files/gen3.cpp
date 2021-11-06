#include "testlib.h"
#include <iostream>

using namespace std;

vector<vector<string>> types =
        {
                {"2", "333", "34"},
                {"4", "22",  "33"},
                {"3", "222", "42"}
        };

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);
    int mx = atoi(argv[2]);
    vector<string> type = types[atoi(argv[3])];
    int target = atoi(argv[4]);

    while (true) {
        int mx2 = pow(mx, 0.5);
        vector<vector<int>> a(5);
        vector<int> cnt(5);
        int m = type.size();
        vector<vector<int>> cnt2(m, vector<int>(5));
        for (int i = 0; i < m; i++) {
            for (auto c : type[i]) {
                cnt2[i][c - '0']++;
            }
            for (int j = 0; j < 5; j++) cnt[j] = max(cnt[j], cnt2[i][j]);
        }
        for (int i = 0; i < 5; i++) {
            while (true) {
                a[i].clear();
                for (int j = 0; j < cnt[i]; j++) {
                    a[i].push_back(rnd.next(mx2 / 5) * 5 + i);
                }
                sort(a[i].begin(), a[i].end());
                bool ok = true;
                for (int j = 0; j < cnt[i]; j++) {
                    if (j < cnt2[target][i] && a[i][j] % 2 == 1) ok = false;
                    if (j >= cnt2[target][i] && a[i][j] % 2 == 0) ok = false;
                }
                if (ok) break;
            }
        }
        while (true) {
            vector<int> ss(type.size(), 1);
            for (int i = 0; i < m; i++) {
                for (int k = 0; k < 5; k++) {
                    for (int j = 0; j < cnt2[i][k]; j++) ss[i] *= a[k][j];
                }
            }
            bool ok = true;
            for (int i = 0; i < (int) type.size(); i++) {
                if (i != target && ss[i] < ss[target]) {
                    for (int j = 0; j < 5; j++) {
                        if (cnt2[i][j] > cnt2[target][j]) {
                            a[j].back() += 10;
                            break;
                        }
                    }
                    ok = false;
                }
            }
            if (ok) break;
        }
        bool ok = true;
        for (int i = 0; i < 5; i++) {
            for (int j : a[i]) {
                if (j > mx) ok = false;
            }
        }
        if (!ok) continue;
        vector<int> q;
        int d = 6;
        for (int i = 0; i < 5; i++) {
            for (int x : a[i]) q.push_back(x);
            for (int j = cnt2[target][i]; j < cnt[i]; j++) {
                d = (d * i) % 10;
            }
        }
        while ((int) q.size() < n) {
            while (true) {
                int x = rnd.next(mx * 9 / 20, mx / 2 - 1) * 2 + 1;
                if (x % 5 != 0 && (a[x % 5].empty() || x >= a[x % 5].back())) {
                    q.push_back(x);
                    d = (d * x) % 10;
                    break;
                }
            }
        }
        shuffle(q.begin(), q.end());
        cout << n << " " << d << "\n";
        for (int i = 0; i < n; i++) {
            cout << q[i] << " \n"[i == n - 1];
        }
        break;

    }

}