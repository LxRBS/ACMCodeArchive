#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define mid (l + r >> 1)
#define lc (o << 1)
#define rc (o << 1 | 1)

typedef pair<int, int> pii;
typedef long long ll;
typedef double db;

inline ll getint()
{
    char c = getchar();
    ll ret = 0, f = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        ret = ret * 10 + c - '0', c = getchar();
    return ret * f;
}

const int maxn = 1e5 + 10;
const int segn = maxn << 2;

vector<int> E[maxn];
int n, m;
int Fa[maxn], top[maxn], son[maxn], Siz[maxn], dep[maxn], dfn[maxn], tme;
int rt[maxn], ch[maxn][2], pfa[maxn], fa[maxn], siz[maxn];
ll sum[segn], at[segn], Ans;


inline void up(int o)
{
    sum[o] = sum[lc] + sum[rc];
}

inline void addtag(int o, int l, int r, ll x)
{
    at[o] += x; sum[o] += (r - l + 1) * x;
}

inline void down(int o, int l, int r)
{
    if (at[o])
    {
        addtag(lc, l, mid, at[o]);
        addtag(rc, mid + 1, r, at[o]);
        at[o] = 0;
    }
}

inline void modify(int o, int l, int r, int al, int ar, ll x)
{
    if (al > ar) return;
    if (al <= l && r <= ar) return addtag(o, l, r, x), void();
    down(o, l, r);
    if (al <= mid) modify(lc, l, mid, al, ar, x);
    if (mid < ar) modify(rc, mid + 1, r, al, ar, x);
    up(o);
}

inline ll query(int o, int l, int r, int al, int ar)
{
    if (al > ar) return 0;
    if (al <= l && r <= ar) return sum[o];
    down(o, l, r);
    ll ret = 0;
    if (al <= mid) ret += query(lc, l, mid, al, ar);
    if (mid < ar) ret += query(rc, mid + 1, r, al, ar);
    return ret;
}

inline void clear(int o, int l, int r)
{
    if (l > r) return;
    sum[o] = at[o] = 0;
    if (l == r) return;
    clear(lc, l, mid); 
    clear(rc, mid + 1, r);
}

inline void maintain(int o)
{
    siz[o] = siz[ch[o][0]] + siz[ch[o][1]] + 1;
    rt[o] = ch[o][0] ? rt[ch[o][0]] : o;
}

inline void rotate(int x)
{
    int o = fa[x], y = fa[o];
    pfa[x] = pfa[o]; pfa[o] = 0;
    int d = ch[o][1] == x ? 0 : 1;
    ch[o][d ^ 1] = ch[x][d]; maintain(o);
    if (ch[x][d]) fa[ch[x][d]] = o;
    ch[x][d] = o; maintain(x);
    fa[o] = x; fa[x] = y;
    if (y) ch[y][ch[y][1] == o] = x, maintain(y);
}

inline void splay(int x)
{
    for (int y = fa[x]; y; rotate(x), y = fa[x])
        if (fa[y]) rotate((ch[y][1] == x) ^ (ch[fa[y]][1] == y) ? x : y);
}

inline void access(int x)
{
    for (int u = x, v = 0; u; v = u, u = pfa[u])
    {
        splay(u);
        
        if (ch[u][1])
        {
            int p = ch[u][1];
            modify(1, 1, n, dfn[rt[p]], dfn[rt[p]] + Siz[rt[p]] - 1, 1);
            Ans -= 1ll * siz[p] * (siz[u] - siz[p]);
            fa[p] = 0, pfa[p] = u;
        }

        ch[u][1] = v; maintain(u);

        if (v) 
        {
            Ans += 1ll * siz[v] * (siz[u] - siz[v]);
            modify(1, 1, n, dfn[rt[v]], dfn[rt[v]] + Siz[rt[v]] - 1, -1);
            fa[v] = u, pfa[v] = 0;
        }
    }
}

inline void dfs(int u)
{
    dfn[u] = ++tme; son[u] = 0;
    dep[u] = dep[Fa[u]] + 1; Siz[u] = 1;
    for (auto v : E[u])
    {
        if (v == Fa[u]) continue;
        Fa[v] = u; dfs(v); Siz[u] += Siz[v];
        if (Siz[v] > Siz[son[u]]) son[u] = v;
    }
}

inline void cut(int u)
{
    if (son[u]) top[son[u]] = top[u], cut(son[u]);
    for (auto v : E[u])
        if (v != Fa[u] && v != son[u]) top[v] = v, cut(v);
}

inline int getlca(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = Fa[top[u]];
    }
    return dep[u] > dep[v] ? v : u;
}

inline void solve()
{
    Ans = tme = 0; clear(1, 1, n);
    rep(i, 1, n) E[i].clear(), ch[i][0] = ch[i][1] = 0, fa[i] = 0;

    n = getint(); m = getint();
    rep(i, 1, n - 1)
    {
        int u = getint(), v = getint();
        E[u].pb(v); E[v].pb(u);
    }

    dfs(1); top[1] = 1; cut(1);

    rep(i, 2, n) pfa[i] = Fa[i];
    rep(i, 1, n) siz[i] = 1, rt[i] = i;
    
    rep(i, 2, n) 
        modify(1, 1, n, dfn[i], dfn[i] + Siz[i] - 1, 1);

    while (m--)
    {
        int typ = getint();
        if (typ == 1) 
        {
            access(getint());
            int tmp = getint();
        }
        if (typ == 2)
        {
            int u = getint(), v = getint(), lca = getlca(u, v);
            ll ans = query(1, 1, n, dfn[u], dfn[u]) + query(1, 1, n, dfn[v], dfn[v]);
            ans -= query(1, 1, n, dfn[lca], dfn[lca]) << 1;
            printf("%lld\n", ans);
        }
        if (typ == 3)
        {
            int u = getint();
            ll ans = query(1, 1, n, dfn[u], dfn[u] + Siz[u] - 1);
            ans -= query(1, 1, n, dfn[u], dfn[u]) * Siz[u];
            printf("%lld\n", ans);
        }
        if (typ == 4) printf("%lld\n", Ans);
    }
}

int main()
{
    int t = getint();
    while (t--) solve();
    return 0;
}
 