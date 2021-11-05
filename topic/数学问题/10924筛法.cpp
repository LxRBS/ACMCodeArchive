//求指定范围的素数
#include <iostream>
using namespace std;

#define SIZE 31623

//筛法
bool isComp[SIZE] = {0};
int P[SIZE] = {0};
int PCnt = 0;
void sieve(){
	for(int i=2;i<SIZE;++i){
		if ( isComp[i] ) continue;

		P[PCnt++] = i;
		for(int j=i*i;j<SIZE;j+=i)
			isComp[j] = true;
	}
}

bool A[100001];
int main(){
	sieve();

	int t;
	scanf("%d",&t);
	while(t--){
		int m,n;
		scanf("%d%d",&m,&n);

		memset(A,0,sizeof(A));

		if ( 1 == m ) m = 2;

		for(int i=0;i<PCnt;++i){
			int p = P[i];
			int x = m % p ?  m / p * p + p : m;
			if ( x == p ) x += p;
            
            if ( x > n ) break;
            
			for(int j=x;j<=n;j+=p)
				A[j-m] = true;
		}

        for(int i=m;i<=n;++i)
			if ( !A[i-m] )
				printf("%d\n",i);

		if ( t ) printf("\n");
	}
	return 0;
}
