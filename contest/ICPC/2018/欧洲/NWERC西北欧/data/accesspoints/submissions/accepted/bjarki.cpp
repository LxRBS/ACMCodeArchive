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

long double opt(vi arr) {
    stack<pair<ii,ll> > S;
    rep(i,0,size(arr)) {
        pair<ii,ll> back(ii(i,i), arr[i]);
        while (!S.empty()) {
            if (back.second * (S.top().first.second - S.top().first.first + 1) >= S.top().second * (back.first.second - back.first.first + 1)) {
                break;
            }
            assert(S.top().first.second + 1 == back.first.first);
            back = make_pair(ii(S.top().first.first, back.first.second), S.top().second + back.second);
            S.pop();
        }
        S.push(back);
    }
    long double res = 0.0;
    while (!S.empty()) {
        int l = S.top().first.first,
            r = S.top().first.second;
        ll sm = S.top().second;
        S.pop();
        long double want = 1.0L * sm / (r - l + 1);
        rep(i,l,r+1) {
            res += (want - arr[i])*(want - arr[i]);
        }
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vi a(n), b(n);
    rep(i,0,n) {
        cin >> a[i] >> b[i];
    }

    cout << setprecision(20) << opt(a) + opt(b) << endl;

    return 0;
}

