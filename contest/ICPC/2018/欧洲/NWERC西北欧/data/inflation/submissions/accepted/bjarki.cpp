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
    vi s(n);
    rep(i,0,n) {
        cin >> s[i];
    }
    sort(s.begin(), s.end());

    double mn = 1.0;
    rep(i,1,n+1) {
        if (s[i-1] > i) {
            cout << "impossible" << endl;
            return 0;
        }
        mn = min(mn, s[i-1] * 1.0 / i);
    }
    cout << setprecision(10) << mn << endl;

    return 0;
}

