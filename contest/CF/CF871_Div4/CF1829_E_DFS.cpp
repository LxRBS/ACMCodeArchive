/**
 * 给定二维数组以0为边界，求权值和最大的连通块的权值和
 * 深搜或者并查集带秩合并
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 34;
#else
int const SZ = 200000 + 12;
#endif

int const DR[] = {-1, 1, 0, 0};
int const DC[] = {0, 0, -1, 1};

int N, M;
vvi A;
vvi Flag;

llt dfs(int r, int c){
    Flag[r][c] = 1;
    llt ans = A[r][c];
    for(int nx,ny,i=0;i<4;++i){
        nx = r + DR[i];
        ny = c + DC[i];
        if(0 <= nx and nx < N and 0 <= ny and ny < M and 0 == Flag[nx][ny] and A[nx][ny] > 0){
            ans += dfs(nx, ny);
        }
    }
    return ans;
}

llt proc(){
    Flag.assign(N, vi(M, 0));
    llt ans = 0;
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        if(0 == Flag[i][j] and A[i][j] > 0){
            ans = max(ans, dfs(i, j));
        }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> M;
        A.assign(N, vi(M, 0));
        for(auto & v : A)for(auto & i : v) cin >> i;
        cout << proc() << endl;
    }
    return 0;
}

