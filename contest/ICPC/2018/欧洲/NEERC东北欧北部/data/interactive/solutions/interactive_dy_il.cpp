#include <bits/stdc++.h>
 
using namespace std;
 
 
vector<vector<int>> solve(int l, int r) {
    if (r == l) {
        return {};
    }
    cout << "? " << (r - l) * 2;
    for (int i = l; i < r; ++i) {
        cout << ' ' << i + 1 << ' ' << i + 1;
    }
    cout << endl;
     
    int cnt;
    cin >> cnt;
     
    vector<vector<int>> arrays;
    vector<int> curr;
    for (int i = 0; i < cnt; ++i) {
        int x;
        cin >> x;
        if (find(curr.begin(), curr.end(), x) == curr.end()) {
            curr.push_back(x);
        } else {
            int len = curr.size();
            for (int j = 0; j < len - 1; ++j) {
                cin >> x;
                i += 1;
            }
            arrays.push_back(curr);
            curr.clear();
        }
    }
     
    assert(curr.empty());
    assert((int)arrays.size() == r - l);
    return arrays;
}
 
 
int main() {
    int n;
    cin >> n;
     
    if (n == 1) {
        cout << "? 1" << endl;
        int cnt;
        cin >> cnt;
        vector<int> a(cnt);
        for (int &x : a) {
            cin >> x;
        }
        cout << "! " << a.size();
        for (int x : a) {
            cout << ' ' << x;
        }
        cout << endl;
        return 0;
    }
     
    int fcount = n / 3;
    int scount = (n + 1) / 3;
    int tcount = (n + 2) / 3;
    assert(fcount + scount + tcount == n);
    assert(tcount * 2 <= n);
     
    auto a = solve(0, fcount);
    auto b = solve(fcount, fcount + scount);
    auto c = solve(fcount + scount, n);
     
    cout << '!';
    for (auto arrs : {a, b, c}) {
        for (auto arr : arrs) {
            cout << ' ' << arr.size();
            for (int x : arr) {
                cout << ' ' << x;
            }
        }
    }
    cout << endl;
}
