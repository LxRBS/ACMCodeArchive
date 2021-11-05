#include <cstdio>

#define SIZE 32768

//筛法求质数
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

int main(){
	sieve();

	int n;
	while( scanf("%d",&n) && n ){
		int ret = 0;
		for(int i=0;P[i]<=n>>1;++i){
			if ( isComp[n-P[i]] ) continue;
			++ret;
		}
		printf("%d\n",ret);
	}
	return 0;
}