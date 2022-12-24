/**
 * 给定数组A，再给定数组X，其中Xi=max(0, A1...A[i-1])
 * 再给定数组B，令Bi=Ai-Xi
 * 现在已知数组B，要求反推出数组A
 * 
 * 很明显令x为当前A数组的最大值（初始为0）
 * 再令Ai=Bi+x即可
*/
#include <bits/stdc++.h>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

int const SIZE = 220000;
int B[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    int mmax = 0;
    for(int i=0;i<n;++i){
        int b = getInt();
        int a = b + mmax;
        printf("%d ", a);
        if(a>mmax) mmax = a;
    }
    printf("\n");
    return 0;
}
