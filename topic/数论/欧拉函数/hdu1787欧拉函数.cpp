#include <cstdio>
#define SIZE 10001
bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
void sieve(){
	for(int i=2;i<SIZE;++i){
		if ( !isComp[i] ) P[PCnt++] = i;

		for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
			isComp[i*P[j]] = true;
			if ( 0 == i % P[j] ) break;
		}
	}
}

//利用最小质因子求欧拉函数
int E[SIZE] = {0};
void euler(){
	for(int i=0;i<PCnt;++i) E[P[i]] = P[i] - 1;
	for(int i=4;i<SIZE;++i){
		if ( E[i] ) continue;
		for(int j=0;j<PCnt&&P[j]*P[j]<=i;++j){
			if ( i % P[j] ) continue;
			if ( i / P[j] % P[j] ) E[i] = E[i/P[j]] * ( P[j] - 1 );
			else E[i] = E[i/P[j]] * P[j];
			break;
		}
	}
}
//求单个数的欧拉函数
int euler(int n){
	if ( n < SIZE ) return E[n];

	for(int i=0;i<PCnt&&P[i]*P[i]<=n;++i){
		if ( n % P[i] ) continue;
		if ( n / P[i] % P[i] ) return euler(n/P[i]) * ( P[i] - 1 );
		else return euler(n/P[i]) * P[i];
	}

	return n - 1;
}
int main(){
	sieve();
	euler();

	int n;
	while( scanf("%d",&n) && n )
        printf("%d\n",n-1-euler(n));

	return 0;
}