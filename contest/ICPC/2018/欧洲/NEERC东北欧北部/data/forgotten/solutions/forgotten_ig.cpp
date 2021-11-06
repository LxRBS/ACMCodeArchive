#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <math.h>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <chrono>
 
using namespace std;
 
typedef long long ll;
 
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
 
const int N = 5000 + 7;
const int LIM = (1 << 10);
const int M = 998244353;
 
inline int add(int a, int b)
{
    a += b;
    if (a < 0) a += M;
    if (a >= M) a -= M;
    return a;
}
 
inline int mul(int a, int b)
{
    return (a * (ll) b) % M;
}
 
int a[N];
vector <int> g[N];
 
int dp[N][LIM];
int c[N][N];
int b[N];
bool u[N];
 
int cnt = 0;
 
void dfs(int v, int mask, int pr = -1)
{
    if (!((mask >> a[v]) & 1))
    {
        return;
    }
    u[v] = true;
    cnt++;
    for (int to : g[v])
    {
        if (to != pr)
        {
            dfs(to, mask, v);
        }
    }
}
 
int main()
{
#ifdef ONPC
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    c[0][0] = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i)
            {
                c[i][j] = add(c[i][j], c[i - 1][j]);
            }
            if (i && j)
            {
                c[i][j] = add(c[i][j], c[i - 1][j - 1]);
            }
        }
    }
    b[0] = 1;
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            b[i] = add(b[i], mul(b[j], c[i - 1][j]));
        }
    }
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        a[i]--;
    }
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int lim = (1 << k);
    int ans = 0;
    for (int mask = 0; mask < lim; mask++)
    {
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            u[i] = 0;
        }
        for (int i = 0; i < n; i++)
        {
            if (u[i]) continue;
            cnt = 0;
            dfs(i, mask, -1);
            for (int j = 1; j <= cnt; j++)
            {
                dp[j][mask] = add(dp[j][mask], c[cnt][j]);
            }
            sum += cnt;
        }
        int cnt = k;
        int cost = 0;
        for (int i = 0; i < k; i++)
        {
            if ((mask >> i) & 1)
            {
                cost += (1 << cnt);
                cnt--;
            }
        }
        int _ans = 0;
        for (int i = 1; i <= sum; i++)
        {
            for (int sm = mask; sm > 0; sm = (sm - 1) & mask)
            {
                if (sm != mask)
                {
                    dp[i][mask] = add(dp[i][mask], -dp[i][sm]);
                }
            }
            _ans = add(_ans, mul(dp[i][mask], b[n - i]));
        }
        ans = add(ans, mul(_ans, cost));
    }
    cout << ans << '\n';
}
