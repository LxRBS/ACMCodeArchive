//最基本的欧拉函数
//216k,0ms,708B

#include <iostream>
using namespace std;

#define SIZE 33000
//筛法
bool isComp[SIZE] = {0};
int Prime[SIZE] = {0};
int PCnt = 0;
void sieve(){
	for(int i=2;i<SIZE;++i){
	    if ( isComp[i] ) continue;

		Prime[PCnt++] = i;
		for(int j=i*i;j<SIZE;j+=i)
			isComp[j] = true;
	}
}
//欧拉函数
int euler(int n){
	int ret = n;
	for(int i=0;Prime[i]*Prime[i]<=n;++i){
	    if ( n % Prime[i] ) continue;

		ret -= ret / Prime[i];   
		n /= Prime[i];
		while( n % Prime[i] == 0 )
			n /= Prime[i];

		if ( 1 == n ) break;
	}

	if ( n != 1 ) ret -= ret / n;
	return ret;
}
int main(){
	sieve();
	int n;
	while( scanf("%d",&n) && n ){
	    printf("%d\n",euler(n));
	}
    return 0;
}