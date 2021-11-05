//基本欧拉函数求法
//484k,0ms,837B
#include <iostream>
using namespace std;
#define SIZE 65536
//筛法求质数
bool isComp[SIZE] = {0};
int P[SIZE] = {0};
int PCnt = 0;
void sieve(){
	for(int i=2;i<SIZE;++i){
		if ( isComp[i] ) continue;

		P[PCnt++] = i;
		for(unsigned int j=i*i;j<SIZE;j+=i)
			isComp[j] = true;
	}     
} 
//利用质数求欧拉函数 
int Euler[SIZE] = {0};
void euler(){
	Euler[1] = 1;

	for(int i=0;i<PCnt;++i)
		Euler[P[i]] = P[i] - 1; 

	for(int i=4;i<SIZE;++i){
		if ( Euler[i] ) continue;

		for(int j=0;j<PCnt;++j){
			if ( i % P[j] ) continue;

			if ( i / P[j] % P[j] )
				Euler[i] = Euler[i/P[j]] * ( P[j] - 1 );
			else
				Euler[i] = Euler[i/P[j]] * P[j];    
			break;    
		}        
	}        
}

int main(){
	sieve();
	euler();

	int p;
	while( EOF != scanf("%d",&p) )
		printf("%d\n",Euler[p-1]);
	return 0;
}
