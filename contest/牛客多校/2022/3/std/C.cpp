#include<bits/stdc++.h>
 
using namespace std;
 
const int N = 2000005;
const int sigma = 5;
const int sumS = 20000005;
 
int n, cnt, tr[sumS][sigma];
int endcnt[sumS], sid[sumS];
vector<bool> is_lower[N];
string s[N];
 
int dfs_u[sumS], dfs_top, stk[sumS], stk_top;
char dfs_i[sumS];
vector<bool> vis;
int pre[sumS], suf[sumS], head, tail;
void dfs() {
    dfs_u[++dfs_top] = 0;
    dfs_i[dfs_top] = 0;
    while (dfs_top) {
        int u = dfs_u[dfs_top];
        if (dfs_i[dfs_top] == 0) {
            if (u) stk[stk_top++] = u;
 
            if (endcnt[u]) {
                vector<int> ids;
                for (int i = 0; i < stk_top; i++) if (endcnt[stk[i]] && is_lower[sid[u]][i]) {
                    vis[stk[i]] = true;
                    ids.push_back(stk[i]);
                }
                int pos = tail;
                for (int i : ids) if (!vis[pre[i]]) {
                    pos = i;
                    break;
                }
                for (int i : ids) vis[i] = false;
                int p = pre[pos];
                pre[pos] = suf[p] = u;
                pre[u] = p, suf[u] = pos;
            }
        }
        while (!tr[u][dfs_i[dfs_top]] && dfs_i[dfs_top] < sigma) {
            dfs_i[dfs_top]++;
        }
 
        if (dfs_i[dfs_top] == sigma) {
            if (u) stk_top--;
            dfs_top--;
        } else {
            int x = tr[u][dfs_i[dfs_top]];
            dfs_i[dfs_top]++;
            dfs_top++;
            dfs_u[dfs_top] = x;
            dfs_i[dfs_top] = 0;
        }
        
    }
}
int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    vis.resize(sumS);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];
 
    for (int i = 1; i <= n; i++) {
        int len = s[i].size();
        int l = 0, r = 0;
        is_lower[i].resize(len);
 
        vector<int> lcp(len + 1);
        lcp[0] = len;
        for (int j = 1; j <= len; j++) {
            lcp[j] = j > r ? 0 : min(r - j + 1, lcp[j - l]);
 
            while (j + lcp[j] < len && s[i][lcp[j]] == s[i][j + lcp[j]])
                lcp[j]++;
            
            if (j + lcp[j] - 1 > r) {
                l = j;
                r = j + lcp[j] - 1;
            }
        }
 
        for (int j = 1; j < len; j++) {
            int tmp = lcp[j];
            if (tmp == len - j) {
                tmp = lcp[len - j];
                if (tmp == j) is_lower[i][j - 1] = false;
                else {
                    int posl = tmp + len - j;
                    int posr = tmp;
                    is_lower[i][j - 1] = s[i][posr] < s[i][posl];
                }
            } else {
                int posl = tmp;
                int posr = tmp + j;
                is_lower[i][j - 1] = s[i][posr] < s[i][posl];
            }
        }
        is_lower[i][len - 1] = false;
    }
 
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        int p = 0;
        for (char c : s[i]) {
            if (!tr[p][c - '0'])
                tr[p][c - '0'] = ++cnt;
            p = tr[p][c - '0'];
        }
        sid[p] = i;
        endcnt[p]++;
    }
 
    head = cnt + 1, tail = cnt + 2;
    pre[tail] = head, suf[head] = tail;
    pre[head] = -1, suf[tail] = -1;
    
    dfs();
 
    for (int p = suf[head]; p != tail; p = suf[p]) {
        for (int tt = 0; tt < endcnt[p]; tt++) {
            cout << s[sid[p]];
        }
    }
}