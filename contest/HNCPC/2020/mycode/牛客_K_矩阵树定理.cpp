/**
  字符串，如i<j且sj=1，则ij之间有一条边，且sn=1
  考虑基尔霍夫矩阵的aii，表示第i个点的度数，
  显然第i行、第i列应该还有aii个-1，且ain=ani=-1
  令按ann展开的减一阶余子式记作D，则用令第一行加上其他所有行，
  于是第一行全都变为1，其他行维持不变。
  再考虑第i行中的ai1和aij(其中j<i)，
  当ai1为0时，表示1和i无边，说明si=0，因此aij也是0
  当ai1为-1时，说明1和i有边，说明si=1，因此aij也是-1
  于是用其他列减去第一列，从第二列开始，可以得到一个上三角行列式。
  只需要计算n-2个对角线元素之积即可
  减法操作之前，对角元素即每个点的度数。
  然后再减去ai1即可。ai1的计算如上。
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
llt const MOD = 1000000007LL;

inline llt add(llt a, llt b){return (a+b)%MOD;}
inline llt mul(llt a, llt b){return a*b%MOD;}


int N;
char A[1000010];
int B[1000010] = {0};

llt proc(){
    if(1==N||2==N) return 1LL;

    B[N-2] = 1;
    for(int i=N-3;i>=0;--i)B[i] = B[i+1] + (A[i+1]=='1'?1:0);

    llt ans = 1LL;
    for(int d, i=1,n=N-1;i<n;++i){
        d = B[i];
        if('1'==A[i]) d += i + 1;
        ans = mul(ans, d);
    }
    return ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(2==scanf("%d%s",&N,A)){
        printf("%lld\n",proc());
    }
    return 0;
}
