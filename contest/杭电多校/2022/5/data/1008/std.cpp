#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define mid (l + r >> 1)
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int crz = 998244353;
const int maxn = 4e5 + 10;
const int T = 4000;

inline int mod(int x)
{
	return x >= crz ? x - crz : x;
}

struct dat{
	int x, y;
	bool operator == (const dat &B) const {return x == B.x && y == B.y;}
	dat operator + (const dat &B) const {return (dat){mod(x + B.x), mod(y + B.y)};}
	dat operator - (const dat &B) const {return (dat){mod(x - B.x + crz), mod(y - B.y + crz)};}
	dat operator * (const dat &B) const {return (dat){(ll)x * B.x % crz, (ll)y * B.y % crz};}
}ha[maxn], hat[maxn], pw[maxn], sd;

char s[maxn], t[maxn];
vector<int> E[maxn];
int l, r, nl, nr;
int ch[maxn][30], fa[maxn], Max[maxn], cnt[maxn], tot, last;

inline void insert(int c)
{
	int v = last;
	Max[last = ++tot] = Max[v] + 1; fa[last] = 1;
	while (v && !ch[v][c]) ch[v][c] = last, v = fa[v];

	if (!v) return;
	int p = ch[v][c];
	if (Max[p] != Max[v] + 1)
	{
		int np = ++tot;
		Max[np] = Max[v] + 1; fa[np] = fa[p];
		fa[p] = fa[last] = np;
		while (v && ch[v][c] == p) ch[v][c] = np, v = fa[v];
		rep(i, 0, 25) ch[np][i] = ch[p][i];
	}
	else fa[last] = p;
}

inline void dfs(int u)
{
	for (auto v : E[u])
		dfs(v), cnt[u] += cnt[v];
}

inline void build()
{
	rep(i, 1, tot) fa[i] = Max[i] = cnt[i] = 0, E[i].clear();
	rep(i, 1, tot) memset(ch[i], 0, sizeof(ch[i]));

	tot = last = 1;

	l = nl; r = nr;
	rep(i, l, r) insert(s[i] - 'a'), cnt[last] = 1;

	rep(i, 2, tot) E[fa[i]].pb(i);

	dfs(1);
}

inline int cmp(int a, int b, int c, int d)
{
	if (a < c) return (hat[b] - hat[a - 1]) * pw[c - a] == ha[d] - ha[c - 1];
	else return (ha[d] - ha[c - 1]) * pw[a - c] == hat[b] - hat[a - 1];
}

inline int calc()
{
	int len = strlen(t + 1);
	if (len > nr - nl + 1) return 0;

	int u = 1;

	rep(i, 1, len) u = ch[u][t[i] - 'a'];

	int ret = cnt[u];
	rep(i, 1, len) hat[i] = hat[i - 1] + pw[i - 1] * (dat){t[i] - 'a' + 1, t[i] - 'a' + 1};

	rep(i, max(r + 1, l + len - 1), nr) ret += cmp(1, len, i - len + 1, i);
	rep(i, l, min(nl - 1, nr - len + 1)) ret -= cmp(1, len, i, i + len - 1);
	return ret;
}

inline void solve()
{
	scanf("%s", s + 1);

	int m; scanf("%d", &m);

	nl = 1; nr = strlen(s + 1);
	pw[0] = (dat){1, 1}; sd = (dat){29, 31};
	rep(i, 1, nr) pw[i] = pw[i - 1] * sd;
	rep(i, 1, nr) ha[i] = ha[i - 1] + pw[i - 1] * (dat){s[i] - 'a' + 1, s[i] - 'a' + 1};

	build();
	
	int last = 0;
	rep(i, 1, m)
	{
		int typ; scanf("%d", &typ);
		if (typ == 1)
		{
			getchar();
			char c = (getchar() - 'a' ^ last) % 26 + 'a'; s[++nr] = c;
			
			pw[nr] = pw[nr - 1] * sd;
			ha[nr] = ha[nr - 1] + pw[nr - 1] * (dat){c - 'a' + 1, c - 'a' + 1};
		}

		if (typ == 2) nl++;
		
		if (typ == 3)
		{
			scanf("%s", t + 1);
			int len = strlen(t + 1);

			rep(i, 1, len) t[i] = (t[i] - 'a' ^ last) % 26 + 'a';

			printf("%d\n", last = calc());
		}
		
		if (nr - r + nl - l == T) build();
	}

}

int main()
{
	int t = getint();
	while (t--) solve();
	return 0;
}