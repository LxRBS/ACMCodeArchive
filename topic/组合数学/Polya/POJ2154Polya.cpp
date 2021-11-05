#include <iostream>
using namespace std;

//10�ڵ�ƽ������31622.xx
#define SIZE 31623

//����x��y�η�ģm
int mypow(int x,int y,int m){
	int ans = 1;
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
		int n,p;
		scanf("%d%d",&n,&p);

		int ans = 0;

		int i;
		for(i=1;i*i<n;++i){
			if ( n % i ) continue;

			//�ݴμ�1������Ϊ���Ĵ�Ҫ����n
			ans = ( ans + ( euler(i)  % p ) * mypow(n,n/i-1,p) % p ) % p;
			ans = ( ans + ( euler(n/i) % p ) * mypow(n,i-1,p) % p ) % p;
		}
		if ( i * i == n ) 
			ans = ( ans + euler(i) % p * mypow(n,i-1,p) % p ) % p;

		printf("%d\n",ans);
	}
	return 0;
}