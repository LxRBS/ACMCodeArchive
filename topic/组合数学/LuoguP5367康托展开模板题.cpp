/**
    康托展开模板题
    小N可以用平方复杂度
    大N需要用NlogN复杂度
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long llt;

llt const MOD = 998244353LL;
int const SIZE = 1000100;

//阶乘数组
llt Fac[SIZE] = {1,1};
void initFac(int n){
    for(int i=2;i<=n;++i)Fac[i] = Fac[i-1]*i%MOD;
}

//康托展开,n比较大,a[1:n]保存数据,c用来充当树状数组
//需要事先求出阶乘数组
llt Cantor(llt const a[],int n,int c[]){
    fill(c,c+n+1,0);
    llt ans = 1;
    for(int i=1;i<=n;++i){
        //对ai，求已出现的数有多少比它小的
        int r = 0;
        for(int j=a[i];j;j-=(j&-j))r+=c[j];
        //累加答案
        ans += (a[i]-r-1) * Fac[n-i] % MOD;
        //将ai加入树状数组
        for(int j=a[i];j<=n;j+=(j&-j))c[j]+=1;
    }
    return ans % MOD;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

llt A[SIZE];
int C[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    initFac(n);
    for(int i=1;i<=n;++i)A[i]=getUnsigned();
    printf("%lld\n",Cantor(A,n,C));
    return 0;
}
