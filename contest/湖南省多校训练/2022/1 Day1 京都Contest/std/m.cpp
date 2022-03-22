#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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
constexpr ll mod = 998244353;
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
const ld eps = 1e-8;
const ld pi = acosl(-1.0);

ll mod_pow(ll x, ll n, ll m = mod) {
	if (n < 0) {
		ll res = mod_pow(x, -n, m);
		return mod_pow(res, m - 2, m);
	}
	if (abs(x) >= m)x %= m;
	if (x < 0)x += m;
	ll res = 1;
	while (n) {
		if (n & 1)res = res * x % m;
		x = x * x % m; n >>= 1;
	}
	return res;
}
struct modint {
	ll n;
	modint() :n(0) { ; }
	modint(ll m) :n(m) {
		if (n >= mod)n %= mod;
		else if (n < 0)n = (n % mod + mod) % mod;
	}
	operator int() { return n; }
};
bool operator==(modint a, modint b) { return a.n == b.n; }
modint operator+=(modint& a, modint b) { a.n += b.n; if (a.n >= mod)a.n -= mod; return a; }
modint operator-=(modint& a, modint b) { a.n -= b.n; if (a.n < 0)a.n += mod; return a; }
modint operator*=(modint& a, modint b) { a.n = ((ll)a.n * b.n) % mod; return a; }
modint operator+(modint a, modint b) { return a += b; }
modint operator-(modint a, modint b) { return a -= b; }
modint operator*(modint a, modint b) { return a *= b; }
modint operator^(modint a, ll n) {
	if (n == 0)return modint(1);
	modint res = (a * a) ^ (n / 2);
	if (n % 2)res = res * a;
	return res;
}

ll inv(ll a, ll p) {
	return (a == 1 ? 1 : (1 - p * inv(p % a, a)) / a + p);
}
modint operator/(modint a, modint b) { return a * modint(inv(b, mod)); }
modint operator/=(modint& a, modint b) { a = a / b; return a; }
const int max_n = 1 << 1;
modint fact[max_n], factinv[max_n];
void init_f() {
	fact[0] = modint(1);
	for (int i = 0; i < max_n - 1; i++) {
		fact[i + 1] = fact[i] * modint(i + 1);
	}
	factinv[max_n - 1] = modint(1) / fact[max_n - 1];
	for (int i = max_n - 2; i >= 0; i--) {
		factinv[i] = factinv[i + 1] * modint(i + 1);
	}
}
modint comb(int a, int b) {
	if (a < 0 || b < 0 || a < b)return 0;
	return fact[a] * factinv[b] * factinv[a - b];
}
modint combP(int a, int b) {
	if (a < 0 || b < 0 || a < b)return 0;
	return fact[a] * factinv[a - b];
}

void expr2() {
	/*ll sss = 0;
	for (int i = 111; i <= 999; i++) {
		bool exi = false;
		if (i % 10 == 0)exi = true;
		if ((i / 10) % 10 == 0)exi = true;
		if (!exi)sss += i;
	}
	cout << sss << "\n";
	rep1(x, 9)rep1(y, 9) {
		sss += x * y + x + y;
	}
	cout << sss << "\n";*/
	int n; cin >> n;
	modint ans = 0;
	int t = 1; rep(i, n)t *= 11;
	vector<int> v(n);
	rep(i, t) {
		int cop = i;
		rep(j, n) {
			v[j] = cop % 11; cop /= 11;
		}
		if (v[0] >= 9 || v.back() >= 9)continue;
		bool exi = false;
		rep(j, n - 1)if (v[j] >= 9 && v[j + 1] >= 9)exi = true;
		if (exi)continue;
		string s;
		rep(j, n) {
			if (v[j] < 9)s.push_back('1' + v[j]);
			else if (v[j] == 9)s.push_back('+');
			else s.push_back('*');
		}
		ll a = 0, b = 1;
		int le = 0;
		rep(j, n) {
			if (v[j] >= 9) {
				string u = s.substr(le, j - le); le = j + 1;
				ll val = stoll(u);
				if (v[j] == 9) {
					a += b * val;
					b = 1;
				}
				else {
					b *= val;
				}
			}
		}
		string u = s.substr(le, n - le);
		ll val = stoll(u);
		a += b * val;
		ans += a;
		//cout << s << " " <<i<<" "<< a << "\n";
	}
	cout << ans << "\n";
}
void expr() {
	int n;
	cin >> n;
	modint ans = 0;
	int t = 1; rep(i, n)t *= 3;
	vector<int> v(n);
	rep(i, t) {
		int cop = i;
		rep(j, n) {
			v[j] = cop % 3; cop /= 3;
		}
		if (v[0] != 0 || v.back() != 0)continue;
		bool exi = false;
		rep(j, n - 1)if (v[j] > 0 && v[j + 1] > 0)exi = true;
		if (exi)continue;
		string s;
		rep(j, n) {
			if (v[j] == 0)s.push_back('1');
			else if (v[j] == 1)s.push_back('+');
			else s.push_back('*');
		}
		/*ll a = 0, b = 1, c = 0;
		int le = 0;
		rep(j, n) {
			if (v[j]>0) {
				string u = s.substr(le, j - le);
				ll val = stoll(u);
			}
		}*/
		modint a = 0, b = 1, c = 0;
		modint t = 1;
		//cout << "?? " << s << "\n";
		rep(j, n) {
			if (v[j] == 0) {
				a *= 9;
				c = (modint)90 * c + (modint)45 * b;
				b *= 9;
				t *= 9;
			}
			else if (v[j] == 1) {
				a += c;
				b = t; c = 0;
			}
			else {
				b = c; c = 0;
			}
			//cout << a << " " << b << " " << c << "\n";
		}
		a += c;
		//cout << s << "=" << a << "\n";
		ans += a;
	}
	cout << ans << "\n";
}

typedef vector<vector<modint>> mat;
typedef vector<modint> vec;
mat mtmul(mat& A, mat& B) {
	mat C(A.size(), vec(B[0].size()));
	rep(i, (int)A.size()) {
		rep(k, (int)B.size()) {
			rep(j, (int)B[0].size()) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}
mat mtpow(mat A, ll n) {
	mat B(A.size(), vec(A.size()));
	rep(i, (int)A.size()) {
		B[i][i] = 1;
	}
	while (n > 0) {
		if (n & (ll)1)B = mtmul(B, A);
		A = mtmul(A, A);
		n >>= 1;
	}
	return B;
}
void solve() {
	ll n; cin >> n;
	mat A(8, vec(8));
	A[0][0] += 9;
	A[1][1] += 9;
	A[2][1] += 45;
	A[2][2] += 90;
	A[3][3] += 9;

	A[0][4] += 9;
	A[1][5] += 9;
	A[2][5] += 45;
	A[2][6] += 90;
	A[3][7] += 9;


	//+
	A[4][0] += 1;
	A[4][2] += 1;
	A[5][3] += 1;
	A[7][3] += 1;
	//*
	A[4][0] += 1;
	A[5][2] += 1;
	A[7][3] += 1;

	A = mtpow(A, n);
	modint ans = A[0][5] + A[0][7] + A[2][5] + A[2][7];
	cout << ans << "\n";
}


signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	//cout << fixed << setprecision(10);
	//init_f();
	//init();
	//expr2();
	//expr();
	//int t; cin >> t; rep(i, t)
	solve();
	return 0;
}

