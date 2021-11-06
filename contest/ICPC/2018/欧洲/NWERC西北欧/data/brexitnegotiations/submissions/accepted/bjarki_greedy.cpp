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
    vi len(n), left(n);
    vector<vi> prev(n);
    rep(i,0,n) {
        int cnt;
        cin >> len[i] >> cnt;
        rep(j,0,cnt) {
            int x;
            cin >> x;
            x--;
            prev[i].push_back(x);
            left[x]++;
        }
    }

    set<ii> ready;
    rep(i,0,n) {
        if (left[i] == 0) {
            ready.insert(ii(len[i], i));
        }
    }

    int mx = 0;
    for (int i = n-1; i >= 0; i--) {
        assert(!ready.empty());
        ii cur = *ready.begin();
        ready.erase(cur);
        mx = max(mx, cur.first + i);
        iter(it,prev[cur.second]) {
            if (--left[*it] == 0) {
                ready.insert(ii(len[*it], *it));
            }
        }
    }
    cout << mx << endl;

    return 0;
}

