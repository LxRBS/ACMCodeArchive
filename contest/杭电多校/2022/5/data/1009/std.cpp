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

int tmp[10];

struct dat{
	int m[10];    
	dat() {memset(m, 0, sizeof(m));}
	bool operator == (const dat &B)
	{
		rep(i, 1, 6) if (m[i] != B.m[i]) return 0;
		return 1;
	}
	inline void rotate(int d) 
	{
		if (d == 1)
		{
			tmp[3] = m[3]; tmp[4] = m[4];
			tmp[1] = m[5]; tmp[5] = m[2]; tmp[2] = m[6]; tmp[6] = m[1];
		}

		if (d == 2)
		{
			tmp[3] = m[3]; tmp[4] = m[4];
			tmp[1] = m[6]; tmp[5] = m[1]; tmp[2] = m[5]; tmp[6] = m[2];
		} 
		
		if (d == 3)
		{
			tmp[1] = m[1]; tmp[2] = m[2];
			tmp[3] = m[5]; tmp[5] = m[4]; tmp[4] = m[6]; tmp[6] = m[3];
		}

		if (d == 4)
		{
			tmp[1] = m[1]; tmp[2] = m[2];
			tmp[3] = m[6]; tmp[5] = m[3]; tmp[4] = m[5]; tmp[6] = m[4];
		}

		rep(i, 1, 6) m[i] = tmp[i];
	}
}S[100], st, ed;



const int maxs = 2e6 + 10;
const int maxn = 2e5 + 10;

int inv[1010];
int n, m, pos, tag, d[maxn];
int tot, stid, edid, nex[50][10];

int snex[maxn][50], rsnex[maxn][50], mul[maxn][50], rmul[maxn][50], last[maxn], rlast[maxn];
pii tab[maxs]; int N;
ll Ans;

inline int getid0(dat &now)
{
	rep(i, 1, tot)
		if (now == S[i]) return i;
	return 0;
}

inline int getid(dat &now)
{
	int tmp = getid0(now);

	if (tmp) return tmp;
	S[++tot] = now;
	
	int id = tot;
	rep(i, 1, 4)
	{
		dat tmp = now; now.rotate(i); 

		nex[id][i] = getid(now);

		now = tmp;
	}
	return id;
}

inline void dfs2(int now, int dep, int ans)
{
	if (dep <= pos) return tab[++N] = mp(now, ans), void();

	if (d[dep])
	{
		ans = (ll)ans * rmul[dep][now] % crz;
		dfs2(rsnex[dep][now], rlast[dep], ans);
	}
	else
	{
		ans = (ll)ans * inv[S[now].m[1]] % crz;
		rep(d, 1, 4)
			dfs2(nex[now][d], dep - 1, ans);
	}
}

inline void dfs1(int now, int dep, int ans)
{
	if (dep > pos)
	{
		if (dep == n)
			Ans += now == edid && ans == tag;
		else
		{
			int l = lower_bound(tab + 1, tab + N + 1, mp(now, ans)) - tab;
			int r = upper_bound(tab + 1, tab + N + 1, mp(now, ans)) - tab;
			Ans += r - l;
		}
		
		return;
	}

	if (d[dep])
		dfs1(snex[dep][now], last[dep], (ll)ans * mul[dep][now] % crz);
	else
	{
		rep(d, 1, 4)
		{
			int tmp = nex[now][d];
			dfs1(tmp, dep + 1, (ll)ans * S[tmp].m[1] % crz);
		}
	}
}

int rev[10];

inline void build()
{
	rep(i, 1, n)
		if (d[i])
		{
			int pos;
			rep(c, 1, tot)
			{
				int u = c, tmp = 1;
				rep(j, i, n + 1)
				{
					if (!d[j]) {pos = j; break;}
					u = nex[u][d[j]];
					tmp = (ll)tmp * S[u].m[1] % crz;
				}
				
				mul[i][c] = tmp;
				snex[i][c] = u;
				last[i] = pos;
			}
			i = pos;
		}
	
	rev[1] = 2; rev[2] = 1; rev[3] = 4; rev[4] = 3;
	per(i, n, 1)
		if (d[i])
		{
			int pos;
			rep(c, 1, tot)
			{
				int u = c, tmp = 1;
				per(j, i, 0)
				{
					if (!d[j]) {pos = j; break;}
					tmp = (ll)tmp * inv[S[u].m[1]] % crz;
					u = nex[u][rev[d[j]]];
				}
				
				rmul[i][c] = tmp;
				rsnex[i][c] = u;
				rlast[i] = pos;
			}
			i = pos;
		}
}

inline void solve()
{
	cin>>n;
	rep(i, 1, n)
	{
		cin>>d[i];
		m += !(d[i]);
	}

	rep(i, 1, 6) cin>>st.m[i];
	rep(i, 1, 6) cin>>ed.m[i];

	cin>>tag;


	stid = getid(st); edid = getid(ed);

	build();

	pos = 0; int cnt = 0;
	rep(i, 1, n)
	{
		cnt += !d[i];
		if (cnt == (m + 1 >> 1) && !d[i + 1]) 
			pos = i;
	}

	N = Ans = 0;
	dfs2(edid, n, tag);
	sort(tab + 1, tab + N + 1);
	dfs1(stid, 1, 1);
	printf("%lld\n", Ans);
}

int main()
{
	ios::sync_with_stdio(0);
	inv[0] = inv[1] = 1;
	rep(i, 2, 1000) inv[i] = (ll)(crz - crz / i) * inv[crz % i] % crz;

	int t;
	cin>>t;
	while (t--) solve();
	return 0;
}
