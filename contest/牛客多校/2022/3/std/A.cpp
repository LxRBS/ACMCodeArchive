#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1e5 + 10;
 
int n, k;
int va[N], vb[N], x[N];
 
struct tree{
    vector<int> g[N];
    int fa[N], size[N], mson[N], top[N], deep[N];
    int pre[N], lst[N];
 
    inline void add(int x, int y) {
        g[x].push_back(y);
    }
 
    void dfs(int x) {
        size[x] = 1;
        for(int i = 0; i < g[x].size(); i++) {
            int y = g[x][i];
            fa[y] = x;
            deep[y] = deep[x] + 1;
            dfs(y);
            if(size[y] > size[mson[x]])mson[x] = y;
            size[x] += size[y];
        }
    }
 
    void dfs(int x, int y) {
        top[x] = y;
        if(mson[x])dfs(mson[x], y);
        for(int i = 0; i < g[x].size(); i++) {
            int y = g[x][i];
            if(y == mson[x])continue;
            dfs(y, y);
        }
    }
 
    int lca(int x, int y) {
        while(top[x] != top[y]) {
            if(deep[top[x]] < deep[top[y]])swap(x, y);
            x = fa[top[x]];
        }
        if(deep[x] < deep[y])return x;
        return y;
    }
 
    void do_lca() {
        dfs(1);
        dfs(1, 1);
        pre[1] = x[1];
        for(int i = 2; i <= k; i++) {
            pre[i] = lca(pre[i - 1], x[i]);
        }
        lst[k] = x[k];
        for(int i = k - 1; i; i--) {
            lst[i] = lca(lst[i + 1], x[i]);
        }
    }
 
    int get_lca(int i) {
        if(i == 1)return lst[2];
        if(i == k)return pre[k - 1];
        return lca(pre[i - 1], lst[i + 1]);
    }
 
}treea, treeb;
 
int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= k; i++)
        scanf("%d", &x[i]);
    for(int i = 1; i <= n; i++)
        scanf("%d", &va[i]);
    for(int i = 2; i <= n; i++) {
        int pa;
        scanf("%d", &pa);
        treea.add(pa, i);
    }
    for(int i = 1; i <= n; i++)
        scanf("%d", &vb[i]);
    for(int i = 2; i <= n; i++) {
        int pb;
        scanf("%d", &pb);
        treeb.add(pb, i);
    }
    treea.do_lca();
    treeb.do_lca();
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int la = treea.get_lca(i);
        int lb = treeb.get_lca(i);
        if(va[la] > vb[lb])ans++;
    }
    printf("%d\n", ans);
}