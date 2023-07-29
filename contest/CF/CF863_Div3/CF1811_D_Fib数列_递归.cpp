/**
 * 给定N，确定一个矩形，其高和宽分别为FN和F[N+1]，其中F是Fib数列
 * 再给定一个坐标，问能否将该矩形分割为N+1个正方向，满足
 * 1. 给定的坐标单独成一个边长为1的正方向
 * 2. 最多只存在两个正方向边长相等
 * 3. 每个正方向的边长均是Fib数
 * 矩形的面积显然是Fn*F[n+1]
 * 令 Sn = Fn * F[n+1] = Fn * (F[n-1] + Fn) = S[n - 1] + Fn * Fn
 * 所以， Sn = 1 + F1 * F1 + F2 * F2 + ... + Fn * Fn
 * 因此，可知划分方案是唯一的，除了给定的坐标外，其他恰好每个Fib数划分出一个正方形
 * 可以递归做，对于当前n，首先要能划分出以Fn为边长的正方形，此时要求坐标满足一定条件
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
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

llt const MOD = 1000000000 + 7;

array<llt, 45> F = {1, 1};
int N;
llt X, Y;

bool dfs(int depth, llt row, llt col){
    if(0 == depth){
        return true;
    }
    
    if(col > F[depth]){
        return dfs(depth - 1, F[depth + 1] + 1 - col, row);
    }

    if(col <= F[depth - 1]){
        return dfs(depth - 1, F[depth - 1] + 1 - col, row);
    }

    return false;
}

bool proc(){
    return dfs(N, X, Y);
} 

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for(int i=2;i<46;++i) F[i] = F[i - 1] + F[i - 2];
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> X >> Y;
        cout << (proc() ? "YES" : "NO") << endl;
    }
    return 0;
}

