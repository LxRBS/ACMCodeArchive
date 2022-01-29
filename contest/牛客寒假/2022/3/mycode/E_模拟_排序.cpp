/**
 * 给定一个序列，每格有数字(数字为0-9之间)、有颜色
 * 相邻格子，如果颜色相同，可以交换次序，交换次数不限
 * 再给定K个修改(K不超过10)，每次把old颜色改为new颜色
 * 问每次能够得到的最大数是多少
 * 因为K不大，手动改一下，然后排序即可
*/
#include<bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 18;
#else
int const SIZE = 100010;
#endif

typedef long long llt;
llt const MOD = 1000000000+7;

int N, M, K;

struct _t{
    int val;
    int col;
}A[SIZE];

bool cmp(const _t&a, const _t&b){
    assert(a.col == b.col);
    return a.val > b.val;
}

char T[SIZE];

void proc(){
    for(int k, i=0;i<N;){
        k = 0;
        while(i+k < N && A[i].col == A[i+k].col) ++k;

        sort(A+i, A+i+k, cmp);
        if((i+=k) >= N) break;
    }

    llt ans = 0;
    for(int i=0;i<N;++i){
        ans = (ans * 10 + A[i].val) % MOD;
    }
    printf("%lld\n", ans);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%d%d%s", &N, &M, &K, T);
    for(int i=0;i<N;++i){
        scanf("%d", &A[i].col);
        A[i].val = T[i] - '0';
    }
    proc();
    for(int old,nn, q=1;q<=K;++q){
        scanf("%d%d", &old, &nn);
        for(int i=0;i<N;++i){
            if(A[i].col == old){
                A[i].col = nn;
            }
        }
        proc();
    }
    return 0;
}