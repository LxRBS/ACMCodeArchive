//求给定素数p的原根，答案就是euler(p-1)
//420k,16ms,434B
//欧拉函数基本题
#include <iostream>
using namespace std;
#define SIZE 65536
//筛法求欧拉函数
int Euler[SIZE] = {0};
void sieve(){
    Euler[1] = 1;
	for(int i=2;i<SIZE;++i){
	    if ( Euler[i] ) continue;
	    
		for(int j=i;j<SIZE;j+=i){
		    if ( !Euler[j] ) Euler[j] = j;

			Euler[j] = Euler[j] / i * ( i - 1 );
		}
	}
}

int main(){
	sieve();
	int p;
	while( EOF != scanf("%d",&p) )
		printf("%d\n",Euler[p-1]);
    return 0;
}