#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int N = 505;
int n, T, m1, m2, s[N];
namespace Flow
{
    struct Edge
    {
        int To, Val, Nxt;
    } Ed[10005];
    int n, S, T, Head[2005], cur[2005], dis[2005], cnt;
    void AddEdge(int x, int y, int val)
    {
        // printf("AddEdge(%d,%d,%d)\n", x, y, val);
        Ed[++cnt] = (Edge){y, val, Head[x]};
        Head[x] = cnt;
        Ed[++cnt] = (Edge){x, 0, Head[y]};
        Head[y] = cnt;
    }
    bool bfs()
    {
        for (int i = 1; i <= n; i++)
            dis[i] = 1e9;
        queue<int> Q;
        Q.push(S);
        dis[S] = 0;
        while (!Q.empty())
        {
            int Now = Q.front();
            Q.pop();
            for (int i = Head[Now]; i != -1; i = Ed[i].Nxt)
            {
                if (dis[Ed[i].To] == 1e9 && Ed[i].Val)
                {
                    Q.push(Ed[i].To);
                    dis[Ed[i].To] = dis[Now] + 1;
                }
            }
        }
        return dis[T] != 1e9;
    }
    int dfs(int x, int val)
    {
        if (x == T || val == 0)
        {
            return val;
        }
        int Out = 0;
        for (int &i = cur[x]; i != -1; i = Ed[i].Nxt)
        {
            if (dis[Ed[i].To] != dis[x] + 1 || !Ed[i].Val)
                continue;
            int tmp = dfs(Ed[i].To, min(val, Ed[i].Val));
            val -= tmp;
            Out += tmp;
            Ed[i].Val -= tmp;
            Ed[i ^ 1].Val += tmp;
            if (val == 0)
                break;
        }
        return Out;
    }
    int Dinic()
    {
        int ans = 0;
        while (bfs())
        {
            memcpy(cur, Head, sizeof(cur));
            ans += dfs(S, 1e9);
        }
        return ans;
    }
}
int main()
{
    // freopen("1001.in", "r", stdin);
    // freopen("1001.out", "w", stdout);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &m1, &m2);
        for (int i = 1; i <= n; i++)
            s[i] = 0;
        for (int i = 1; i <= m1; i++)
        {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            if (z == 1)
                s[x]++;
            else
                s[y]++;
        }

        Flow::n = n + m2 + 2;
        Flow::S = n + m2 + 1;
        Flow::T = n + m2 + 2;
        Flow::cnt = -1;
        for (int i = 1; i <= Flow::n; i++)
        {
            Flow::Head[i] = -1;
        }

        int cnt = 0;
        for (int i = 1; i <= m2; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x == 1 || y == 1)
            {
                cnt++;
                s[1]++;
                continue;
            }
            Flow::AddEdge(n + i, x, 1);
            Flow::AddEdge(n + i, y, 1);
            Flow::AddEdge(Flow::S, n + i, 1);
        }
        bool flag = true;
        for (int i = 2; i <= n; i++)
        {
            if (s[i] > s[1])
                flag = false;
            Flow::AddEdge(i, Flow::T, s[1] - s[i]);
        }
        if (!flag)
        {
            printf("NO\n");
            continue;
        }
        printf(Flow::Dinic() == m2 - cnt ? "YES\n" : "NO\n");
    }
}