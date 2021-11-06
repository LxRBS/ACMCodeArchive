#include "testlib.h"
#include <iostream>

using namespace std;

vector<vector<string>> types =
        {
                {"2", "333", "34"},
                {"4", "22", "33"},
                {"3", "222", "42"}
        };

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);
    int mx = atoi(argv[2]);
    vector<string> type = types[atoi(argv[3])];
    int target = atoi(argv[4]);

    while (true) {
        int mx2 = mx / 10;
        vector<vector<int>> a(5);
        vector<int> cnt(5);
        for (auto s : type) {
            vector<int> cnt2(5);
            for (auto c : s) {
                cnt2[c - '0']++;
            }
            for (int i = 0; i < 5; i++) cnt[i] = max(cnt[i], cnt2[i]);
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < cnt[i]; j++) {
                a[i].push_back(rnd.next(mx2 / 5) * 5 + i);
            }
            sort(a[i].begin(), a[i].end());
        }
        vector<int> ss(type.size(), 1);
        for (int i = 0; i < (int)type.size(); i++) {
            string s = type[i];
            vector<int> cnt2(5);
            for (auto c : s) {
                cnt2[c - '0']++;
            }
            for (int k = 0; k < 5; k++) {
                for (int j = 0; j < cnt2[k]; j++) ss[i] *= a[k][j];
            }
        }
        bool ok = true;
        for (int i = 0; i < (int)type.size(); i++) {
            if (i != target && ss[i] < ss[target]) ok = false;
        }
        if (ok) {
            vector<int> cnt2(5);
            for (auto c : type[target]) {
                cnt2[c - '0']++;
            }
            vector<int> q;
            int d = 1;
            for (int i = 0; i < 5; i++) {
                for (int x : a[i]) q.push_back(x);
                for (int j = cnt2[i]; j < cnt[i]; j++) {
                    d = (d * i) % 10;
                }
            }
            while ((int)q.size() < n) {
                while (true) {
                    int x = rnd.next(1, mx);
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

}