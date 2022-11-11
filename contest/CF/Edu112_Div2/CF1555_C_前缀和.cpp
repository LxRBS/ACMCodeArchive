/**
 * 有一个2×M的矩阵，每一格有非负整数
 * Alice先走，从最左上到最右下，只能向右或者向下，并将途径格子的整数拿走，数拿走以后就不存在了
 * Bob后走，规则一样。
 * Alice希望Bob拿走的整数和越小越好，Bob则希望越大越好
 * 问双方最优的情况下，Bob最终拿到多少
 * Alice拿到的数显然是第一行的前半段和第二行的后半段。
 * Bob拿到的要么是第一行的后半段，要么是第二行的前半段。
 * 用前缀和求一个最小最大值即可。O(N)。
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 7;
#else
int const SIZE =100010;
#endif

typedef int llt;

llt M;
llt A[2][SIZE];
llt B[2][SIZE];

llt proc(){
    B[0][0] = A[0][0];
    B[1][0] = A[1][0];
    for(int j=1;j<M;++j){
        B[0][j] = B[0][j-1] + A[0][j];
        B[1][j] = B[1][j-1] + A[1][j];
    }

    llt ans = min(B[0][M-1]-A[0][0], B[1][M-2]);
    for(int i=1;i<M-1;++i){
        ans = min(ans, max(B[0][M-1]-B[0][i], B[1][i-1]));
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d", &M);
        for(int i=0;i<2;++i)for(int j=0;j<M;++j){
            scanf("%d", A[i]+j);
        }
        printf("%d\n", proc());
    }
    return 0;
}