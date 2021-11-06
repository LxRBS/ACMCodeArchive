// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000 + 100;
int a[MAXN][MAXN];

int predecessor_fast[MAXN];
vector<int> successors_fast[MAXN];

int dp[MAXN];

vector<vector<int> > cycles;

int minimal_cycle_cost[MAXN]; // per node, if node not in cycle -> cycle cost = 0

int maximal_successor[MAXN];
bool in_cycle[MAXN];
int mark[MAXN];

void init_cycles(int n){
    if(mark[n] == -1){
        mark[n] = -2;
        init_cycles(predecessor_fast[n]);
        mark[n] = 0;
    } else if(mark[n] == 0){
        return;
    } else if(mark[n] == -2){//cycle found
        vector<int> cycle(1,n);
        for(int c = predecessor_fast[n]; c != n; c = predecessor_fast[c]){
            cycle.push_back(c);
        }
        for(auto c: cycle)in_cycle[c] = true;
        cycles.push_back(cycle);
        mark[n] = 0;
    }
}
int calc_max_successor(int n){
    assert(mark[n] != 9);
    if(mark[n] == 10)return maximal_successor[n];
    mark[n] = 9;
    maximal_successor[n] = n;
    for(auto s: successors_fast[n])maximal_successor[n] = max(maximal_successor[n], calc_max_successor(s));
    mark[n] = 10;
    return maximal_successor[n];
}
int main(){
    int N;
    cin >> N;
    int res = 0;
    for(int i = 0; i <= N; i++){
        dp[i] = 1.1e9;
        successors_fast[i].clear();
        mark[i] = -1;
        a[0][i] = 0;
        in_cycle[i] = false;
        minimal_cycle_cost[i] = 0;
    }
    dp[0] = 0;
    predecessor_fast[0] = 0;
    successors_fast[0].push_back(0);
    for(int i = 1; i <= N; i++){
        int fast_time;
        cin >> predecessor_fast[i] >> fast_time;
        successors_fast[predecessor_fast[i]].push_back(i);
        res += fast_time;
        for(int j = 0; j <= N; j++){
            cin >> a[i][j];
            a[i][j] -= fast_time;
        }
    }
    for(int i = 0; i <= N; i++)if(mark[i] == -1){
        init_cycles(i);
    }
    for(auto cycle: cycles){
        int m = 1e9;
        for(auto n: cycle)m = min(m, a[n][N]);
        res += m;
        for(auto n: cycle)minimal_cycle_cost[n] = m;
    }
    for(int i = 0; i <= N; i++)if(!in_cycle[i]){
        calc_max_successor(i);
    }
    for(auto cycle: cycles){
        int m = 0;
        for(auto n: cycle)for(auto s: successors_fast[n])m = max(m, ((in_cycle[s])?s:maximal_successor[s]));
        for(auto n: cycle)maximal_successor[n] = m;
    }
    for(int n = 0; n < N; n++){
        if(dp[n] > 1.05e9)continue;
        for(int i = 0; i <= N; i++){
            int m = maximal_successor[i];
            if(m <= n)continue;
            dp[m] = min(dp[m], dp[n] + a[i][n] - minimal_cycle_cost[i]);
            assert(a[i][n] >= minimal_cycle_cost[i]);
        }
    }
    cout << res + dp[N] << endl;
	return 0;
}
