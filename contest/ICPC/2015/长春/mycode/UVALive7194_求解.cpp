/*
  给定一个不同高度立方体组合成的立体，
  求立体的表面积，不包括底面积
  直接算
  对于每个单位，看看比四邻高多少
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}


int N,M,A[60][60]={0};
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();

        fill(A[N+1],A[N+1]+M+2,0);
        for(int i=1;i<=N;++i){
            for(int j=1;j<=M;++j) A[i][j] = getUnsigned();
            A[i][M+1] = 0;
        }

        int ans = 0;
        for(int i=1;i<=N;++i)for(int j=1;j<=M;++j)if(A[i][j]){
            //顶面积
            ++ans;
            //上
            if(A[i][j]>A[i-1][j]) ans+=A[i][j]-A[i-1][j];
            //下
            if(A[i][j]>A[i+1][j]) ans+=A[i][j]-A[i+1][j];
            //左右
            if(A[i][j]>A[i][j-1]) ans+=A[i][j]-A[i][j-1];
            if(A[i][j]>A[i][j+1]) ans+=A[i][j]-A[i][j+1];
        }
        printf("%d\n",ans);
    }
    return 0;
}

