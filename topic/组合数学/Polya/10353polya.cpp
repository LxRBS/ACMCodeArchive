#include <bits/stdc++.h>
using namespace std;

//10�ڵ�ƽ������31622.xx
#define SIZE 31623

typedef unsigned long long ull;

//����x��y�η�ģm
ull mypow(ull x,ull y,ull m){
	ull ans = 1ULL;
	x = x % m;
	do{
		if ( y & 1 ) ans = ans * x % m;
		x = x * x % m;
	}while( y = y >> 1 );
	return ans;
}

//����ɸ��
bool isComp[SIZE] = {false};
int Prime[SIZE] = {0};
int PrimeCnt = 0;
void sieve(){
	for(int i=2;i<SIZE;++i){
		if ( isComp[i] ) continue;

		Prime[PrimeCnt++] = i;
		for(int j=i*i;j<SIZE;j+=i)
			isComp[j] = true;
	}
	return;
}

//��ŷ������
int euler(int n){
	int ret = n;
	for(int i=0;Prime[i]*Prime[i]<=n;++i){
		if ( n % Prime[i] == 0 ){
			ret -= ret / Prime[i];
			n /= Prime[i];
			while ( n % Prime[i] == 0 )
				n /= Prime[i];
			if ( 1 == n ) break;
		}
	}
	if ( n != 1 ) ret -= ret / n;
	return ret;
}

int main(){
	sieve();

	int t;
	scanf("%d",&t);
	while(t--){
		int n,p = 20090531;
		scanf("%d",&n);
        
		ull ans = 0;

		//��ת�任
		int i;
		for(i=1;i*i<n;++i){
			if ( n % i ) continue;
            //�ݴζ���1�����Ͳ��ó�n
			ans = ( ans + (ull)( euler(i)  % p ) * mypow(n,n/i-1,p) % p ) % p;
			ans = ( ans + (ull)( euler(n/i) % p ) * mypow(n,i-1,p) % p ) % p;
		}
		if ( i * i == n ) 
			ans = ( ans + (ull)(euler(i) % p) * mypow(n,i-1,p) % p ) % p;

		//��ת�ȼ���ĸ������ݴζ���1�����Ͳ��ó�n
		if ( n & 1 ) ans = ( ans + (ull)n * mypow(n,(n>>1),p) % p ) % p;
		else         ans = ( ans + mypow(n,(n>>1),p) * (ull)((n>>1) % p) + mypow(n,(n>>1)-1,p) * (ull)((n>>1) % p) ) % p;

		if ( ans & 1 ) ans = ( ans * 10045266ULL ) % p;//2����Ԫ
		else         ans >>= 1;
		printf("%llu\n",ans);
	}
	return 0;
}
