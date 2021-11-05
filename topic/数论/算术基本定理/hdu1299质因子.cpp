#include <cstdio>

#define SIZE 41624

bool isComp[SIZE] = {false};
int P[SIZE] = {2};
int PCnt = 1;
void sieve(){
	for(int i=4;i<SIZE;i+=2) isComp[i] = true;
	for(int i=3;i<SIZE;++i){
		if ( isComp[i] ) continue;

		P[PCnt++] = i;
		for(int j=i*i;j<SIZE;j+=i<<1)
			isComp[j] = true;
	}
}

//求n的平方的因子个数
int solve(int n){
    if ( n < SIZE && !isComp[n] ) return 2;

	int ret = 1;
	for(int i=0;P[i]*P[i]<=n;++i){
        if ( n % P[i] ) continue;

		int k = 1;
		n /= P[i];
		while( 0 == n % P[i] ) n /= P[i], ++k;
		ret *= (k<<1) + 1;

		if ( 1 == n ) break;
	}
	if ( n > 1 ) ret *= 3;
	return (ret>>1)+1;
}

int main(){
	sieve();
	int nofkase;
	scanf("%d",&nofkase);
	for(int kase=1;kase<=nofkase;++kase){
		int n;
		scanf("%d",&n);
		printf("Scenario #%d:\n%d\n",kase,solve(n));
		if ( kase != nofkase ) printf("\n");
	}
}