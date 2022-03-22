//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<iomanip>
#include<queue>
#include<ciso646>
#include<random>
#include<map>
#include<set>
#include<bitset>
#include<stack>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<cassert>
#include<complex>
#include<numeric>
#include<array>
using namespace std;

//#define int long long
typedef long long ll;

typedef unsigned long long ul;
typedef unsigned int ui;
constexpr ll mod = 1000000007;
const ll INF = mod * mod;
typedef pair<int, int>P;
#define stop char nyaa;cin>>nyaa;
#define rep(i,n) for(int i=0;i<n;i++)
#define per(i,n) for(int i=n-1;i>=0;i--)
#define Rep(i,sta,n) for(int i=sta;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define per1(i,n) for(int i=n;i>=1;i--)
#define Rep1(i,sta,n) for(int i=sta;i<=n;i++)
#define all(v) (v).begin(),(v).end()
typedef pair<ll, ll> LP;
typedef double ld;
typedef pair<ld, ld> LDP;
const ld eps = 0.01;
const ld pi = acosl(-1.0);

using bt = bitset<66>;
bool ban[22][3][22][3];
bt banlist[22][3];
void solve() {
	int n, m; cin >> n >> m;
	auto trans = [&](char c) {
		if (c == 'R')return 0;
		else if (c == 'G')return 1;
		else if (c == 'B')return 2;
		else return -1;
	};
	int d1 = (2 * n + 1) / 3;
	int d2 = n - d1;
	rep(i, m) {
		int a, b; char x, y; cin >> a >> x >> b >> y;
		a--; b--;
		int cx = trans(x);
		int cy = trans(y);
		banlist[a][cx][3 * b + cy] = 1;
		banlist[b][cy][3 * a + cx] = 1;
	}
	int t3 = 1;
	rep(i, d1)t3 *= 3;
	vector<int> cnt(1 << (3 * d2));
	rep(i, t3) {
		bt s = 0;
		bt bb = 0;
		int cop = i;
		rep(j, d1) {
			int r = cop % 3; cop /= 3;
			s[3 * j + r] = 1;
			bb |= banlist[j][r];
		}
		if ((s & bb).count()) {
			continue;
		}
		int z = 0;
		rep(j, 3 * d2) {
			if (!bb[3 * d1 + j])z |= 1 << j;
		}
		cnt[z]++;
	}
	rep(i, 3 * d2)rep(j, 1 << (3 * d2)) {
		if (!(j & (1 << i))) {
			cnt[j] += cnt[j | (1 << i)];
		}
	}
	t3 = 1;
	rep(i, d2)t3 *= 3;
	ll ans = 0;
	rep(i, t3) {
		bt s = 0;
		bt bb = 0;
		int cop = i;
		rep(j, d2) {
			int r = cop % 3; cop /= 3;
			s[3 * (j + d1) + r] = 1;
			bb |= banlist[j + d1][r];
		}
		if ((s & bb).count()) {
			continue;
		}
		int z = 0;
		rep(j, 3 * d2) {
			if (s[3 * d1 + j])z |= 1 << j;
		}
		ans += cnt[z];
	}
	cout << ans << "\n";
}


signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	//cout << fixed << setprecision(12);
	//init_f();
	//init();
	//expr();
	//init();
	//int t; cin >> t; rep(i, t)
	solve();
	return 0;
}