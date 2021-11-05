#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long llt;

#define SIZE 2001
llt const MOD = 1000000007;

llt S[SIZE][SIZE];//第一类Stirling
llt C[SIZE][SIZE];//组合数

void calc(){
    for(int i=0;i<SIZE;++i){
    	C[i][0] = C[i][i] = S[i][i] = 1LL;
    	S[i][0] = 0LL;
    	for(int j=1;j<i;++j){
    		C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % MOD;
    		S[i][j] = ( (llt)( i - 1 ) * S[i-1][j] % MOD + S[i-1][j-1] ) % MOD;
    	}
    }
}

int main(){
	calc();

    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        int n,f,b;
        scanf("%d%d%d",&n,&f,&b);
        if ( f + b - 1 > n ) printf("0\n");
        else printf("%I64d\n",C[f+b-2][f-1]*S[n-1][f+b-2]%MOD);
    }
    return 0;
}
