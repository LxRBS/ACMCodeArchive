#include <bits/stdc++.h>
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 2147483647;

int main() {
    int n;
    cin >> n;
    vector<vi> succ(n), prec(n);
    vi len(n);
    int lo = 0,
        hi = 0,
        res = -1;
    rep(i,0,n) {
        int cnt;
        cin >> len[i] >> cnt;
        lo = max(lo, len[i]);
        hi = max(hi, len[i]+n);
        rep(j,0,cnt) {
            int x;
            cin >> x;
            x--;
            succ[i].push_back(x);
            prec[x].push_back(i);
        }
    }

    while (lo <= hi) {
        int mx = (lo+hi)/2;
        vector<vi> pos(n);
        vi left(n);
        rep(i,0,n) {
            left[i] = size(prec[i]);
            pos[min(n-1, mx - len[i])].push_back(i);
        }
        set<int> waiting, ready;
        bool ok = true;
        for (int i = n-1; i >= 0; i--) {
            iter(it,pos[i]) {
                if (left[*it] == 0) {
                    ready.insert(*it);
                } else {
                    waiting.insert(*it);
                }
            }
            if (ready.empty()) {
                ok = false;
                break;
            }
            int cur = *ready.begin();
            ready.erase(cur);
            iter(it,succ[cur]) {
                if (--left[*it] == 0 && waiting.find(*it) != waiting.end()) {
                    waiting.erase(*it);
                    ready.insert(*it);
                }
            }
        }
        if (ok) {
            res = mx;
            hi = mx-1;
        } else {
            lo = mx+1;
        }
    }

    cout << res << endl;

    return 0;
}

