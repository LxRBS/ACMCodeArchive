//双重状态DP，两个状态互相导出
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = -1;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret * sgn;
}

int const SIZE = 1000010;
int N,M;
int A[SIZE];

int S[SIZE] = {0};
bool read(){
    if ( EOF == scanf("%d",&M) ) return false;
    N = getInt();
    for(int i=1;i<=N;++i) A[i] = getInt(), S[i] = S[i-1] + A[i];
    return true;
}

/*
Dmi表示m个子段取到第i项的最大值
Dmi = max{Dm,i-1+max{Dm-1,k | m-1<=k<=i-1}} + A[i]
max{Dmk|m<=k<=i}就表示前i个数取m个子段的最大值，记作Wmi
Wmi = max{Wm,i-1, Dmi}
so,
Dmi = max{Dm,i-1 , Wm-1,i-1} + A[i]
Wmi = max{Wm,i-1 , Dmi}
*/


int D[SIZE];
int W[2][SIZE];
int Cur = 0;
void dp(){
    fill(W[Cur],W[Cur]+N+1,0);

    for(int m=1;m<=M;++m){
        Cur ^= 1;
        W[Cur][m] = D[m] = S[m];
        for(int i=m+1;i<=N-M+m;++i){
            D[i] = max(D[i-1],W[Cur^1][i-1]) + A[i];
            W[Cur][i] =  max(W[Cur][i-1],D[i]);
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    while ( read() ){
        dp();
        printf("%d\n",W[Cur][N]);
    }
    return 0;
}
