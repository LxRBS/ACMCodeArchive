#include<bits/stdc++.h>
using namespace std;

int e[15], c[101010][15];

priority_queue<pair<int, int> > edge[15][15]; 

int belong[101010];
int dis[15], frm[15], inq[15];

int spfa(int s)
{
    queue<int> Q;
    Q.push(s);
    for(int i = 0; i < 10; i++)
    {
        dis[i] = 1e9;
        inq[i] = 0;
        frm[i] = 0;
    }
    dis[s] = 0;
    inq[s] = 1;
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        inq[u] = 0;
        for(int v = s - 1; v >= 0; v--)
        {
            if(edge[u][v].empty())
                continue;
            int d = -edge[u][v].top().first;
            if(dis[v] > dis[u] + d)
            {
                dis[v] = dis[u] + d;
                frm[v] = u;
                if(!inq[v])
                {
                    inq[v] = 1;
                    Q.push(v);
                }
            }
        }
    }
    
    vector<int> moved;
    int t = 0;
    while(t != s)
    {
        moved.push_back(edge[frm[t]][t].top().second);
        belong[edge[frm[t]][t].top().second] = frm[t];
        t = frm[t];
    }

    for(int u: moved)
    {
        for(int i = 0; i <= s; i++)
        if(i != u)
            edge[i][belong[u]].push(make_pair(-c[u][i] + c[u][belong[u]], u));
    }

    return dis[0];
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < k; i++)
        scanf("%d", &e[i]);
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < k; j++)
            scanf("%d", &c[i][j]);
    
    long long ans = 0;

    for(int i = 0; i < n; i++)
    {
        ans += c[i][0];
        belong[i] = 0;
    }
    
    for(int j = 1; j < k; j++)
    {
        for(int i = 0; i < n; i++)
            edge[j][belong[i]].push(make_pair(-c[i][j] + c[i][belong[i]], i));
        for(int i = 0; i < e[j]; i++)
        {
            for(int u = 0; u <= j; u++)
                for(int v = 0; v <= j; v++)
                    while(!edge[u][v].empty() && belong[edge[u][v].top().second] != v)
                        edge[u][v].pop();
            ans += spfa(j);
        }
    }
    printf("%lld\n", ans);
    return 0;
}