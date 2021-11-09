//Awwawa! Dis cold yis ratten buy tEMMIE!
#include <bits/stdc++.h>
#define ll long long
#define maxn 35 /*rem*/
#define mod 10007
#define db double
#define vi vector<int>
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define fi first
#define se second

template <typename T> bool chkmax(T &x,T y){return x<y?x=y,true:false;}
template <typename T> bool chkmin(T &x,T y){return x>y?x=y,true:false;}

using namespace std;
ll ksm(ll a, ll b) {
   if (!b) return 1;
   ll ns = ksm(a, b >> 1);
   ns = ns * ns % mod;
   if (b & 1) ns = ns * a % mod;
   return ns;
}
int dp[maxn][maxn][65];
int e[maxn][maxn][65];
#define tri array<int, 3>
void upd(vector<array<int, 4> > s, int mx) {
	memset(e, 0, sizeof(e));
	for (int i = 0; i <= 2 * mx; i++)
		for (int j = 0; j <= 2 * mx; j++)
			for (int k = 0; k <= 4 * mx; k++) {
				if (!dp[i][j][k]) continue;
				for (auto v : s)
					e[i + v[0]][j + v[1]][k + v[2]] = (e[i + v[0]][j + v[1]][k + v[2]] + dp[i][j][k] * v[3]) % mod;
			}
	memcpy(dp, e, sizeof(dp));
	/*
	for (int i = 0; i < maxn; i++)
		for (int j = 0; j < maxn; j++)
			for (int k = 0; k < 65; k++)
				dp[i][j][k] = e[i][j][k] % mod;
*/
}
int c[2505][2505];

int fl[2]; // x = y, x + y = n + 1
int hv[2][maxn]; // ±ØÐëÓÐ
int n;
ll pw[maxn * maxn];
int C; 
ll cal(int df) {
	memset(dp, 0, sizeof(dp));
	dp[0][0][0] = 1;
	for (int i = 1; i <= n + 1 - i; i++) {
		vector<tri> cur;
		if (i == n + 1 - i) {
			for (int s = 0; s < 4; s++) {
				// ban
				if ((s & 1) && hv[0][i]) continue;
				if ((s & 2) && hv[1][i]) continue;
				tri nr;	
				nr[0]= nr[1] = nr[2] = 0;
				if (s & 1) nr[0] = 1;
				if (s & 2) nr[1] = 1;
				if ((s == 0) && (fl[0] || fl[1])) nr[2] = 1;
				cur.pb(nr); 
			}
		}
		else {
			for (int s = 0; s < 16; s++) {
				if ((s & 1) && hv[0][i]) continue;
				if ((s & 2) && hv[0][n + 1 - i]) continue;
				if ((s & 4) && hv[1][i]) continue;
				if ((s & 8) && hv[1][n + 1 - i]) continue;
				tri nr;
				nr[0]= nr[1] = nr[2] = 0;
				if (s & 1) nr[0]++;
				if (s & 2) nr[0]++;
				if (s & 4) nr[1]++;
				if (s & 8) nr[1]++;
				if (fl[0]) {
					if ((s & 5) == 0) nr[2]++;
					if ((s & 10) == 0) nr[2]++;
				}
				if (fl[1]) {
					if ((s & 9) == 0) nr[2]++;
					if ((s & 6) == 0) nr[2]++;
				}
				cur.pb(nr);
			}
		}
		sort(cur.begin(), cur.begin());
		vector<array<int, 4> >h;
		for (int i = 0; i < cur.size(); ) {
			int j = i;
			while (j < cur.size() && cur[j] == cur[i]) j++;
			array<int, 4> u;
			for (int s = 0; s < 3; s++) u[s] = cur[i][s];
			u[3] = j - i;
			h.pb(u);
			i = j;
		}
		upd(h, i - 1);
	}
	ll ans = 0;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			for (int k = 0; k < 65; k++) {
				if (dp[i][j][k]) {
					ll w = 1;
					if ((i + j) & 1) w = -1;
					w *= c[(n - i) * (n - j) - k - df][C - df];
					w = w * dp[i][j][k] % mod;
					ans = (ans + w) % mod;
				}
			}
	return ans;
} 
int main() {
	for (int i = 0; i < 2505; i++)
		for (int j = 0; j <= i; j++) {
			if (i == j || j == 0) c[i][j] = 1;		
			else {
				c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
			}
		}
	for (int i = 0; i < maxn * maxn; i++) pw[i] = ksm(2, i);
	int k;
	vector<pi> cr;
	cin >> n >> k >> C;
	for (int i = 0; i < k; i++) {
		int u, v;
		cin >> u >> v;
		cr.pb(mp(u, v));
	}
	ll ans = 0;
	for (fl[0] = 0; fl[0] < 2; fl[0]++)
		for (fl[1] = 0; fl[1] < 2; fl[1]++)
			for (int c = 0; c < (1 << k); c++) {
				memset(hv, 0, sizeof(hv));
				ll w = 1;
				if (fl[0]) w *= -1;
				if (fl[1]) w *= -1;
				int df = 0;
				for (int j = 0; j < k; j++)
					if (c & (1 << j)) {
						w *= -1;
						df++;
						w %= mod;
						hv[0][cr[j].fi] = 1;
						hv[1][cr[j].se] = 1;
						if (fl[0] && cr[j].fi == cr[j].se) w = 0;
						if (fl[1] && cr[j].fi + cr[j].se == n + 1) w = 0;
					}
				if (w) {
					ll res = cal(df);
					res = res * w % mod;
					ans = (ans + res) % mod;
				}
			}
	if (ans < 0) ans += mod;
	cout << ans << endl;
	return 0;
}
