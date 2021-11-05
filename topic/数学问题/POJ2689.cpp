#include <cstdio>
#include <algorithm>
using namespace std;

int const SIZE = 46345;

bool isComp[SIZE] = {false};
int P[SIZE];
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

void dispPrime(int n){
	for(int i=0;i<n;++i)printf("%d ",P[i]);
	printf("\n");
}

int L,U;
bool F[1000005] = {false};
void disp(){
	for(int i=L;i<=U;++i)printf("%2d",F[i-L]);
	printf("\n");
}
void f(){
	fill(F,F+(U-L+1),false);
	for(int i=0;i<PCnt;++i){	
	    if ( U / P[i] < 2 ) break;
		long long int s = L % P[i] ? L / P[i] + 1 : L / P[i];
		s = 1LL == s ? P[i] + P[i] : s * P[i];
		for(long long int j=s;j<=U;j+=P[i])
		    F[j-L] = true;
	}
}
void proc(){
	int valley = 10000000, peak = -1;
	//找到第一个质数
	int k = 0;
	int const n = U - L + 1;
	while( k < n && F[k] ) ++k;
	if ( n == k ){
		printf("There are no adjacent primes.\n");
		return;
	}
	
	int a[2] = {k,-1};
	int b[2] = {k,-1};
	for(int i=k+1;i<n;++i){
		if ( F[i] ) continue;
		
		int t = i - k;
		if ( t < valley ){
			valley = t;
			a[0] = k;
			a[1] = i;
		} 
		if ( t > peak ){
			peak = t;
			b[0] = k;
			b[1] = i;
		} 
		k = i;
	}
	
	if ( -1 == a[1] ){
		printf("There are no adjacent primes.\n");
	}else{
		printf("%d,%d are closest, %d,%d are most distant.\n",a[0]+L,a[1]+L,b[0]+L,b[1]+L);
	}
}
int main(){
	sieve();
	while( EOF != scanf("%d%d",&L,&U) ){
		if ( 1 == L ) L = 2;
		//求出[L,U]的所有合数
		f(); 
		//求质数对 
		proc();
	}
	return 0;
}
