/**
 * 给定N个区间，再给定Q个询问，对每个询问x，问x的所有倍数是否均不在区间内
 * 最大取值是100w，因此用比较数组将[1, MaxValue]标记，然后对每个x，检查每个倍数是否打标记
 * 这里预处理实际上应该用线段树，可以做到O(NlogN)，或者用差分数组，可以做到O(N)，这里直接用了暴力，数据不强
 * 查询可以做到(sqrt(MaxValue))，但是这里也没有分情况处理，极端数据也可以卡到平方
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 120;
#else
int const SIZE = 1E6+10;
#endif

int N, Q;
vector<int> F;

bool proc(int x){
    for(int i=x;i<SIZE;i+=x){
        if(F[i]) return true;
    }
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    F.assign(SIZE, 0);
    for(int a,b,i=0;i<N;++i){
        cin >> a >> b;
        for(int j=a;j<=b;++j){
            F[j] = 1;
        }
    } 
    for(int x,q=1;q<=Q;++q){
        cin >> x;
        puts(proc(x)?"NO":"YES");
    }
    return 0;
}