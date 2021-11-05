#include <cstdio>

#define SIZE 10000000
typedef long long llt;

//筛法求质数
bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
void sieve(){
	for(llt i=2;i<SIZE;++i){
		if ( isComp[i] ) continue;

        P[PCnt++] = (int)i;
		for(llt j=i*i;j<SIZE;j+=i)
			isComp[j] = true;
    }
}

//判断是否为质数
bool isPrime(int x){
    if ( x < SIZE ) return !isComp[x];
	for(int i=0;i<PCnt&&(llt)P[i]*(llt)P[i]<=x;++i){
		if ( 0 == x % P[i] ) return false;
	}
	return true;
}
int main(){
	sieve();
	
	int n;
	while( EOF != scanf("%d",&n) ){
		int sum = 0;
		for(int i=0;i<n;++i){
            int x;
			scanf("%d",&x);
			sum += isPrime(x) ? 1 : 0;
		}
		printf("%d\n",sum);
	}
	return 0;
}