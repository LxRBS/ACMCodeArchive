#include <bits/stdc++.h>
 
using namespace std;
 
const int MAX_N = 10;
int n;
 
vector<int> gr[1 << MAX_N];
bool is[1 << MAX_N];
bool used[1 << MAX_N];
bool is_end[1 << MAX_N];
 
int mt[1 << MAX_N];
bool kuhn(int v) {
    used[v] = true;
    if (is_end[v])
        return false;
 
    for (int u : gr[v])
        if (mt[u] == -1 || (!used[mt[u]] && kuhn(mt[u]))) {
            mt[u] = v;
            return true;
        }
    return false;
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int k;
    cin >> n >> k;
    
    while (k --> 0) {
        string s;
        cin >> s;
        int u = 0;
        for (int i = 0; i < n; i++)
            if (s[i] == '1')
                u |= (1 << i);
        is[u] = true;
    }
    
    for (int i = 0; i < (1 << n); i++) {
        for (int j = i; j < (1 << n); j = (j + 1) | i)
            if (i != j && is[i] && is[j])
                gr[i].push_back(j);
    }
    
    int mt_cnt = 0;
    int ans_cnt = 0;
    int ans = 0;
    fill(mt, mt + (1 << n), -1);
    int V = 0;
    
    vector<int> ind(1 << n);
    iota(ind.begin(), ind.end(), 0);
    sort(ind.begin(), ind.end(), [](int i, int j) {
        int cnt1 = __builtin_popcount(i);
        int cnt2 = __builtin_popcount(j);
        if (cnt1 < cnt2) return false;
        if (cnt2 < cnt1) return true;
        return i < j;
    });
    
    for (int i: ind) {
        if (is[i]) {
            memset(used, false, sizeof(used));
            if (kuhn(i))
                mt_cnt++;
            V++;
            
            //cout << i << " " << V << " " << mt_cnt << " " << ans_cnt << endl;
            if (V - mt_cnt > ans_cnt) {
                ans_cnt++;
                is_end[i] = true;
                ans += __builtin_popcount(i);
            }
        }
    }
    
    memset(used, false, sizeof(used));
    fill(mt, mt + (1 << n), -1);
    for (int i = 0; i < (1 << n); i++)
        if (is[i] and not is_end[i]) {
            memset(used, false, sizeof(used));
            assert(kuhn(i));
        }
    
    vector<vector<int>> paths;
    for (int i = 0; i < (1 << n); i++)
        if (is_end[i]) {
            paths.push_back(vector<int>());
            int v = i;
            paths.back().push_back(v);
            while (mt[v] != -1) {
                paths.back().push_back(mt[v]);
                v = mt[v];
            }
            reverse(paths.back().begin(), paths.back().end());
        }

    int printed = 0;
    cout << ans + ans_cnt - 1 << endl;
    for (int i = 0; i < paths.size(); i++) {
        if (i != 0)
            cout << "R ", ++printed;
        
        int prev = 0;
        for (int v : paths[i]) {
            //cerr << v << " ";
            int cnt_here = 0;
            for (int i = 0; i < n; i++)
                if ((v & (1 << i)) != (prev & (1 << i)))
                    cout << i << " ", ++printed, ++cnt_here;

            assert(cnt_here >= 1);
            prev = v;
        }
        //cerr << endl;
    }

    assert(printed == ans + ans_cnt - 1);
}
 
/*
2 2
10
11
 
3 4
001
111
101
011
*/
