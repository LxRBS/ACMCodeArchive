/**
 * 给一个01串，从中最多选出3个位置，要求
 * 1 所选位置必须为0
 * 2 所选位置不能重合
 * 3 假设相邻位置差为p，定义得分为w-|k-p|*q, w,k,q为已知量
 * 求能够得到的最大分数
 * 只需枚举中间一个位置即可，然后前后各选一个收益最大的位置
 * 收益最大的位置显然是差别最接近k的，二分即可
 * 也可以尺取。
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 1000000+7;
#endif

typedef long long llt;

int N;
llt K, W, Q;
char A[SIZE];
vector<int> Pos;

template<typename T> T ABS(T a){return a>=0?a:-a;}

inline llt f(int p1, int p2){
    if(p1 == p2) return 0;
    return W - ABS(K - ABS(p1-p2)) * Q;
}    

llt proc(){
    for(int i=0;i<N;++i)if('0' == A[i]) Pos.push_back(i);

    llt ans = 0;
    for(int i=1,n=Pos.size();i<n-1;++i){
        int pos = Pos[i] - K;
        if(pos < Pos[0]) pos = Pos[0];
        llt lans = 0;
        auto it = lower_bound(Pos.begin(), Pos.begin()+i, pos);
        lans = max(lans, f(Pos[i], *it));
        if(it!=Pos.begin()) lans = max(lans, f(Pos[i], *(it-1)));

        pos = Pos[i] + K;
        if(pos > Pos.back()) pos = Pos.back();
        llt rans = 0;
        it = lower_bound(Pos.begin()+i+1, Pos.end(), pos);
        rans = max(rans, f(Pos[i], *(it-1)));
        if(it != Pos.end()) rans = max(rans, f(Pos[i], *it));

        ans = max(ans, lans+rans);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%s%lld%lld%lld", &N, A, &K, &W, &Q);
    printf("%lld\n", proc());
    return 0;
}