//����ָ����ĸ�����Ƶ������Ľ����
//4^(n-1)+2^(n-1)
//����n��һ��������������Ա�дһ�������ݺ���
#include <cstdio>
typedef unsigned long long ull;

//��x^n % mod
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
	while( scanf("%d",&t) && t ){
		for(int kase=1;kase<=t;++kase){
            ull n;
			scanf("%I64u",&n);

			ull ans = powmod(4ULL,n-1,100ULL) + powmod(2ULL,n-1,100ULL);
			printf("Case %d: %I64u\n",kase,ans%100ULL);
		}
		printf("\n");
	}
	return 0;
}