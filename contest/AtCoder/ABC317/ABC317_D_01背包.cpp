/**
 * 有N个选区，对第i个选区，
 * A能够得到Xi张原始投票，B能够得到Yi张原始投票，得票多者获得这个选区的Zi个选举人票
 * 最后获得选举人票数多者获胜。保证没有任何平局。
 * 问最少要改变多少原始投票，可以令A获胜
 * 首先计算一下A、B获得的选举人票，若A>B，直接输出0。
 * 否则，令 target = (B - A) / 2 + 1，即要额外获得这么多选举人票才能令A获胜
 * 再对每一个A输了的选区，有 w=(Yi-Xi)/2+1, v=Zi，即要付出v的代价，可以得到w的收益
 * 于是题目变为代价不小于target的情况下，最小收益是多少
 * 01背包，令Di为恰好付出i代价所能获得的最小收益，最后答案为 min{D[target...]}
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
vi X, Y, Z;

llt proc(){
    int a = 0, b = 0;
    for(int i=0;i<N;++i){
        if(X[i] > Y[i]) a += Z[i];
        else b += Z[i];
    }
    if(a > b) return 0;

    vi cost, gain;
    cost.reserve(N);
    gain.reserve(N);
    for(int i=0;i<N;++i){
        if(X[i] < Y[i]){
            cost.push_back((Y[i] - X[i]) / 2 + 1);
            gain.push_back(Z[i]);
        }
    }

    int total = accumulate(Z.begin(), Z.end(), 0);
    int target = (b - a) / 2 + 1;
    vector<llt> d(total + 1, -1LL);
    d[0] = 0;
    for(int i=0,n=cost.size();i<n;++i){
        for(int v=total;v>=gain[i];--v){
            if(-1 != d[v - gain[i]]){
                if(-1 != d[v]){
                    d[v] = min(d[v], d[v - gain[i]] + cost[i]);
                }else{
                    d[v] = d[v - gain[i]] + cost[i];
                }
            }            
        }
    }

    // for(int i=1;i<=total;++i){
    //     if(d[i] != -1){
    //         printf("%d: %d\n", i, d[i]);
    //     }
    // }
    
    llt ans = accumulate(cost.begin(), cost.end(), 0LL);
    for(int i=target;i<=total;++i){
        if(-1 != d[i]){
            ans = min(ans, d[i]);
        }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    X.assign(N, 0);
    Y.assign(N, 0);
    Z.assign(N, 0);
    for(int i=0;i<N;++i) cin >> X[i] >> Y[i] >> Z[i];
    cout << proc() << endl;
    return 0;
}