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
 
const double EPS = 1e-7;
string ANS;
 
void gen(double masT, double avgT, int numT, vector<int> &v, int h) {
    if (avgT / masT > Y + EPS) return;
    if (numT == N) {
        if (fabsl(avgT / masT - Y) < EPS)
            mem.push_back(v);
        return;
    }
     
    v.push_back(-1);
    for (int num = 1; numT + num <= N; num++) {
        double mas = getMas(h - 1);
        double avg = getAvg(h - 1);
        v.back() = num;
        gen(masT + mas * num, avgT + avg * num, numT + num, v, h + 1);
    }
    v.pop_back();
}
 
void solve(vector<int> &num, string &ans, int h, double avgT, double masT) {
    if (avgT / masT > X + EPS) return;
    if ((int)ans.length() + h > 2 * N || !ANS.empty()) return;
    
    //for (int x : num) cout << x << " ";
    //cout << "h" << h << " " << ans << " " << avgT << " " << masT << " " << (masT == 0 ? -1 : avgT / masT) << endl;
    //cout << "kek" << "\n";
    
    if ((int)ans.length() == 2 * N) {
        if (fabsl(avgT / masT - X) < EPS) {
            ANS = ans;
            //cout << ans << "\n";
        }
        return;
    }
     
    int x = (int)ans.size();
    ans.push_back('_');
    if (num[h + 1] > 0) {
        ans.back() = '(';
        solve(num, ans, h + 1, avgT + getAvg(h, x, 2), masT + getMas(h));
    }
    if (num[h] > 1 || num[h + 1] == 0) {
        ans.back() = ')';
        num[h]--;
        solve(num, ans, h - 1, avgT + getAvg(h - 1, x, 1), masT + getMas(h - 1));
        num[h]++;
    }
    ans.pop_back();
}

void solve(int nn = -1, double xx = 0, double yy = 0) {
    auto t0 = clock();
    if (nn == -1)
        cin >> N >> X >> Y;
    else {
        N = nn; X = xx; Y = yy;
        cout << N << " " << X << " " << Y << endl;
    }
    N /= 2;
    mem.clear();
     
    vector<int> v = {0};
    gen(0, 0, 0, v, 1);
    
#ifdef SERT
    cout << "time: " << static_cast<double>(clock() - t0) / CLOCKS_PER_SEC << endl;
#endif
    
    //cout << mem.size() << "\n";
     
    string ans;
    for (auto &num : mem) {
        num.push_back(0);
        ans.clear();
        solve(num, ans, 0, 0, 0);
    }
#ifdef SERT
    cout << "time: " << static_cast<double>(clock() - t0) / CLOCKS_PER_SEC << endl;
#endif
    if (ANS.empty()) exit(11);
    cout << ANS << "\n";
}

void test(mt19937 &rnd, int n) {
    vector<int> h = {0};
    string res = "(";
    int bal = 1;
    for (int i = 1; i + bal < n; i++) {
        int t = (bal == 0 ? 1 : (rnd() % 2 ? 1 : -1));
        bal += t;
        res.push_back(t == 1 ? '(' : ')');
    }
    while (bal > 0) { res.push_back(')'); bal--; }
    
    //res = "()(()())";
    
    for (int i = 1; i < (int)res.length(); i++) {
        h.push_back(h.back());
        if (res[i] == '(' && res[i] == res[i - 1]) h.back()++;
        if (res[i] == ')' && res[i] == res[i - 1]) h.back()--;
    }
    
    //for (int x : h) cout << x << " ";
    //cout << "\n";
    
    double x = 0, y = 0, m = 0;
    for (int i = 0; i < (int)h.size(); i++) {
        int t = (res[i] == '(' ? 2 : 1);
        x += getAvg(h[i], i, t);
        y += getAvg(h[i]);
        m += getMas(h[i]);
    }
    cout << res << "->" << flush;
    ANS.clear();
    solve((int)h.size(), x / m, y / m);
    
    //cout << ANS << "\n";
}
 
 
int main() {
    mt19937 rnd(3431);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
#ifdef SERT
    cout.precision(4);
    cout << fixed;
    t += 0;
    freopen("/Users/sert/code/timus/tests.txt", "r", stdin);
    for (int i = 0; i < 10; i++) test(rnd, 60);
    return 0;
#endif
    while (t--) solve();
}
