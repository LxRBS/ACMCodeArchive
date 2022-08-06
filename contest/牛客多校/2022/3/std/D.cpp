#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int fac[1010101], inv_fac[1010101];

int qpow(int x, int k)
{
    int ret = 1;
    while(k)
    {
        if(k & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        k /= 2;
    }
    return ret;
}

int inv(int x)
{
    return qpow(x, mod - 2);
}

int C(int n, int m)
{
    if(n < 0)
        return 0;
    if(0 > m || m > n)
        return 0;
    return 1ll * fac[n] * inv_fac[m] % mod * inv_fac[n - m] % mod;
}

int fa[1010101];

int depth[1010101], sz[1010101], un[1010101];
int cnt[1010101];

struct Edge{
    int to, nxt;
}e[2020202];

int head[1010101], edge_cnt = 0;

void dfs(int u)
{
    sz[u] = 1;
    for(int i = head[u]; i > 0; i = e[i].nxt)
    {
        int v = e[i].to;
        if(v == fa[u])
            continue;
        fa[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v);
        sz[u] += sz[v];
    }
}

void add(int u, int v)
{
    edge_cnt++;
    e[edge_cnt].to = v;
    e[edge_cnt].nxt = head[u];
    head[u] = edge_cnt;
}


int get_un(int u)
{
    if(un[u] == -1)
        un[u] = get_un(fa[u]);
    return un[u];
}

int main()
{
    const int MAX_NUM = 1e6;
    fac[0] = 1;
    for(int i = 1; i <= MAX_NUM; i++)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    inv_fac[MAX_NUM] = inv(fac[MAX_NUM]);
    for(int i = MAX_NUM; i >= 1; i--)
        inv_fac[i - 1] = 1ll * inv_fac[i] * i % mod;
    int N, K, s;
    scanf("%d%d%d", &N, &K, &s);

    for(int i = 1; i < N; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    fa[1] = 0;
    depth[1] = 0;
    dfs(1);

    for(int i = 1; i <= N; i++)
        un[i] = -1;

    int ans = 0;
    while(s != 1)
    {
        ans += 2 * sz[s] - 1;
        ans %= mod;
        un[s] = depth[s];
        s = fa[s];
    }
    un[1] = 0;

    for(int i = 2; i <= N; i++)
    {
        cnt[depth[i]] -= sz[i];
        if(cnt[depth[i]] < 0)
            cnt[depth[i]] += mod;

        int un_i = get_un(i);
        if(depth[i] > un_i)
        {
            cnt[depth[i] - un_i] += sz[i];
            if(cnt[depth[i] - un_i] >= mod)
                cnt[depth[i] - un_i] -= mod;
        }
        else if(depth[i] == un_i)
        {
            cnt[1] += sz[i];
            if(cnt[1] >= mod)
                cnt[1] %= mod;
        }
    }
    for(int i = 1; i <= N; i++)
    {
        cnt[i] += cnt[i - 1];
        if(cnt[i] >= mod)
            cnt[i] -= mod;
    }
    assert(cnt[0] == 0);
    assert(cnt[N] == 0);

    int sum = 0;
    for(int i = 1; i <= N; i++)
    {
        sum += 1ll * cnt[i] * C(N - 1 - i, K - 1) % mod;
        if(sum >= mod)
            sum -= mod;
    }
    ans = ans - 2ll * sum * inv(C(N - 1, K)) % mod;
    if(ans < 0)
        ans += mod;
    printf("%d\n", ans);
    return 0;
}