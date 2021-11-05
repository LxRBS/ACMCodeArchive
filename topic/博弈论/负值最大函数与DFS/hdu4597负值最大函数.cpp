#include <cstdio>
#include <cstring>
#include <numeric>
using namespace std;

int const INF = 1000000000;

int N;
int A[23],B[23];
//Dpijkw表示A[i..j]、B[k..w]时能够取到的最大值 
int Dp[23][23][23][23];
int Sum;
void read(){
	scanf("%d",&N);
	for(int i=0;i<N;++i)scanf("%d",A+i);
	for(int i=0;i<N;++i)scanf("%d",B+i);
	Sum = accumulate(A,A+N,0);
	Sum += accumulate(B,B+N,0);
}

int negaMax(int depth,int al,int ar,int bl,int br){
	if ( depth == N + N ) return 0;
	
	if ( Dp[al][ar][bl][br] ) return Dp[al][ar][bl][br];
	
	//一共只有4种可能
	int ret = -INF;
	int v = 0;
	
	if ( al <= ar ){
		v = A[al] - negaMax(depth+1,al+1,ar,bl,br);
		if ( v > ret ) ret = v;
		
		if ( al != ar ){
		    v = A[ar] - negaMax(depth+1,al,ar-1,bl,br);
		    if ( v > ret ) ret = v;
		}		
	}
	
	if ( bl <= br ){
		v = B[bl] - negaMax(depth+1,al,ar,bl+1,br);
		if ( v > ret ) ret = v;
		
		if ( bl != br ){
		    v = B[br] - negaMax(depth+1,al,ar,bl,br-1);
		    if ( v > ret ) ret = v;
		}		
	}
	
	return Dp[al][ar][bl][br] = ret;
}
int main(){
	int kase;
	scanf("%d",&kase);
	while( kase -- ){
		read();
		memset(Dp,0,sizeof(Dp));
		printf("%d\n",( negaMax(0,0,N-1,0,N-1) + Sum ) / 2);
	}
	return 0;
}
