//利用指数型母函数推导出最后的结果是
//4^(n-1)+2^(n-1)
//由于n是一个极大的数，所以编写一个快速幂函数
#include <cstdio>
typedef unsigned long long ull;

//求x^n % mod
ull powmod(ull x,ull n,ull mod){
    ull ret = 1ULL;
	while(n){
		if ( n & 1 ) ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

int main(){
	int t;
        scanf("%d",&t);
	while( t-- ){
		ull n;
		scanf("%I64u",&n);

		ull ans = powmod(4ULL,n-1,10007ULL) + powmod(2ULL,n-1,10007ULL);
		printf("%I64u\n",ans%10007ULL);
		
	}
	return 0;
}