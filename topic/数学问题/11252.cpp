#include <cstdio>
typedef unsigned long long ull;
#define SIZE 10000001
#define MOD 1000000007

int P[SIZE];
int PCnt = 0;
bool isComp[SIZE] = {false};

//筛法
void sieve(){
	for(int i=2;i<SIZE;++i){
		if ( isComp[i] ) continue;

		P[PCnt++] = i;
		for(ull j=(ull)i*(ull)i;j<SIZE;j+=i)
			isComp[j] = true;
	}
}


ull A[SIZE];

int main(){
	sieve();

	//保存i之前所有合数的积
	A[0] = A[1] = 1;
	for(int i=2;i<SIZE;++i){
		A[i] = A[i-1];
		if ( isComp[i] ) A[i] = ( A[i] * i ) % MOD;
	}

	int n;
	while( scanf("%d",&n) && n ){
		if ( 0 == n ) return 0;
		ull ans = A[n];
		for(int i=0;i<PCnt&&P[i]<=(n>>1);++i){
			int cnt = 0;
			int tn = n;
			do{
				tn /= P[i];
				cnt += tn;
			}while(tn >= P[i]);
			if ( 0 == ( cnt & 1 ) )
				ans = ( ans * P[i] ) % MOD;
		}
		printf("%I64u\n",ans);
	}
	return 0;
}