#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <random>
#include <iomanip>
#include <cmath>
#include <queue>
using namespace std;
 
int N;
double X, Y;
vector<vector<int>> mem;
 
double getMas(int h) { return h + 0.5; }
double getAvg(int h) { return h * h * 0.5 + (h + 1.0 / 3) * 0.5; }
 
double getAvg(int h, int x, int t) {
    return x * getMas(h) + 0.5 * h + (t * 1.0 / 3) * 0.5;
}
 
const double EPS = 1e-8;
 
void gen(double masT, double avgT, int numT, vector<int> &v, int h) {
    if (numT == N) {
//        cout << avgT << " " << masT << " " << avgT / masT << " ";
//        for (int x : v) cout << x << " ";
//        cout << "\n";
        if (fabsl(avgT / masT - Y) < EPS)
            mem.push_back(v);
        return;
    }
     
    int fn = ((int)v.size() == 1 ? N : v.back());
    v.push_back(-1);
    for (int num = 1; num <= fn && numT + num <= N; num++) {
        double mas = getMas(h - 1);
        double avg = getAvg(h - 1);
        v.back() = num;
        gen(masT + mas * num, avgT + avg * num, numT + num, v, h + 1);
    }
    v.pop_back();
}
 
void solve(vector<int> &num, string &ans, int h, double avgT, double masT) {
    if ((int)ans.length() + h > 2 * N) return;
    
    //for (int x : num) cout << x << " ";
    //cout << "h" << h << " " << ans << " " << avgT << " " << masT << " " << (masT == 0 ? -1 : avgT / masT) << endl;
    //cout << "kek" << "\n";
    
    if ((int)ans.length() == 2 * N) {
        if (fabsl(avgT / masT - X) < EPS) {
            cout << ans << "\n";
            exit(0);
        }
        return;
    }
     
    int x = (int)ans.size();
    ans.push_back('_');
    if (num[h + 1] > 0) {
        ans.back() = '(';
        solve(num, ans, h + 1, avgT + getAvg(h, x, 2), masT + getMas(h));
    }
    if (num[h] > num[h + 1]) {
        ans.back() = ')';
        num[h]--;
        solve(num, ans, h - 1, avgT + getAvg(h - 1, x, 1), masT + getMas(h - 1));
        num[h]++;
    }
    ans.pop_back();
}
 
void solve() {
    cin >> N >> X >> Y;
    N /= 2;
    mem.clear();
     
    vector<int> v = {0};
    gen(0, 0, 0, v, 1);
     
    string ans;
    for (auto &num : mem) {
        num.push_back(0);
        ans.clear();
        solve(num, ans, 0, 0, 0);
    }
    exit(11);
    //cout << mem.size() << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
#ifdef SERT
    cout.precision(2);
    cout << fixed;
    t += 0;
    freopen("/Users/sert/code/timus/tests.txt", "r", stdin);
#endif
    while (t--) solve();
}
