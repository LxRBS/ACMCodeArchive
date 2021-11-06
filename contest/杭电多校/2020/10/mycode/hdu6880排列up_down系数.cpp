/**
    给定一个1~n的排列a，令k是一个二进制数，如下：
    ki = 1 if ai<a[i+1] else 0
    令{n, k}是所有满足k的n排列总数，称之为up-down系数
    {n, x+2^(m-1)} = C(n,m){m, x} - {n, x}，当n>m时
    可以使用递归加记忆化搜索在O(n^2)完成
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
//#include <bits/stdc++.h>
using namespace std;
typedef long long llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef long long llt;
int const SIZE = 5001;
llt const MOD = 1000000007LL;
llt C[SIZE][SIZE];
int A[SIZE];
int Pos[SIZE];
int Cnt;

int D[SIZE][SIZE];

int f(int n, int cnt){
    if(D[n][cnt]!=-1) return D[n][cnt];
    if(1==cnt){
        return D[n][cnt] = ( C[n][Pos[0]] - 1 ) % MOD;
    }
    return  D[n][cnt] = ( ( C[n][Pos[cnt-1]] * f(Pos[cnt-1], cnt-1) - f(n, cnt-1) ) % MOD + MOD ) % MOD;
}

int f(int n){
    if(0==Cnt) return 1;
    return f(n, Cnt);
}

int main(){
    //freopen("1.txt","r",stdin);
    C[0][0] = 1;
	for(int i=1;i<SIZE;++i){
        C[i][0] = C[i][i] = 1;
        for(int j=1;j<i;++j) C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % MOD;
	}
	
    int nofkase = getUnsigned();
    while(nofkase--){
        int n = getUnsigned();

        Cnt = 0;
        for(int i=1;i<n;++i){
            if(A[i] = getUnsigned()){
                ++Cnt;
            }
        }
        if(Cnt<=n-1-Cnt){
            Cnt = 0;
            for(int i=1;i<n;++i)if(A[i])Pos[Cnt++]=i;
        }else{
            Cnt = 0;
            for(int i=1;i<n;++i)if(!A[i])Pos[Cnt++]=i;
        }        
        
        memset(D,0xFF,sizeof(D));
        printf("%d\n",f(n));
    }
    return 0;
}
