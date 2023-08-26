/**
 * 有N个怪物，每个怪物需要si个魔力值消灭。
 * 有水火两种魔法，每秒各增长W和F个
 * 问最小需要多少时间打死所有怪物。
 * 打怪不需要时间，即只要魔力值到位，即可秒杀，无论几只怪物
 * 由于可以秒杀群体，因此不需要一秒一秒的计算
 * 只需要等到足够时间，再把怪物分两堆，一堆用水、一堆用火即可
 * 再考虑到数据范围，很明显01背包
 * N在100， si在1E4， 因此total在1E6， 01背包在1E8，给了4s
 * 首先做一个01背包，D[0...total]，Di为1表示某些怪物的组合能够等于i。
 * 于是这些怪物用F魔法打死，total-i的怪物用W魔法打死，可以计算出一个时间。
 * for i if Di为1: 计算出时间求最小
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

int N;
int W, F;
vi S;

/// ax >= b, a,b both positive
inline int fGe(int a, int b){
    if(b % a == 0) return b / a;
    return b / a + 1;
}

llt proc(){
    int total = accumulate(S.begin(), S.end(), 0);
    vi d(total + 1, 0);
    d[0] = 1;
    for(int i=0;i<N;++i){
        const auto wi = S[i];
        for(int v=total;v>=wi;--v){
            d[v] |= d[v - wi];
        }
    }

    int ans = total;
    for(int i=0;i<=total;++i){
        if(d[i] and d[total - i]){
            int a = fGe(F, i);
            int b = fGe(W, total - i);
            ans = min(ans, max(a, b));
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
        cin >> W >> F >> N;
        S.assign(N, 0);
        for(auto & i : S) cin >> i;
        cout << proc() << endl;
    }
    return 0;
}