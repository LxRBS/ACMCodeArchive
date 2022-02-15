/**
 * 给定2个数组A和B，可以对任意ai和bi交换位置
 * 求SIGMA{SIGMA{(ai+aj)^2,j从i+1到N}}+SIGMA{SIGMA{(bi+bj)^2,j从i+1到N}}的最小值
 * 简单推导一下，对一个数组，所求=(N-1)*SIGMA{ai^2}+2SIGMA{SIGMA{ai*aj}}
 * 而后者=SIGMA{ai}^2-SIGMA{ai^2}
 * 所以整个所求=SIGMA{ai}^2+SIGMA{bi}^2+(N-2)*SIGMA{ai^2+bi^2}
 * 考虑到令SIGMA{ai}=A,SIGMA{bi}=B
 * 所以A+B为定值，要求A^2+B^2最小，即A和B尽可能接近。做一个稍微变形的背包DP即可
 * 对所有的Ai和Bi，只有2个策略，选A或者选B，注意初始化的时候为-1
 * 因为要恰好选到，最后最近接sum/2且不为-1的即可
 * 注意不要滚动，如果要滚动需要额外的处理，因为不能不选，A、B必选其一
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 45;
#else
int const SIZE = 110;
#endif

typedef long long llt;

int N;
int A[SIZE], B[SIZE];
int D[SIZE][SIZE*SIZE*2];



llt proc(){
    if(1 == N) return 0;
    auto square = [](llt n)->llt{return n*n;};
    llt sum = accumulate(A+1, A+N+1, 0);
    sum += accumulate(B+1, B+N+1, 0);

    for(int i=0;i<=N;++i) fill(D[i], D[i]+sum+1, -1);
    D[0][0] = 0;
    for(int i=1;i<=N;++i){
        for(int v=sum,m1=min(A[i],B[i]);v>=m1;--v){
            if(v >= A[i] && D[i-1][v-A[i]] != -1){
                D[i][v] = max(D[i][v], D[i-1][v-A[i]] + A[i]); 
            }
            if(v >= B[i] && D[i-1][v-B[i]] != -1){
                D[i][v] = max(D[i][v], D[i-1][v-B[i]] + B[i]);
            }
        }
    }
    
    
    llt x = sum/2;
    while(-1 == D[N][x]) --x;
    llt ans = square(x) + square(sum-x);  
    for(int i=1;i<=N;++i){
        ans += (N-2) * (square(A[i]) + square(B[i]));
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		for(int i=1;i<=N;++i) A[i] = getInt();
        for(int i=1;i<=N;++i) B[i] = getInt();
		printf("%lld\n", proc());
	}
    return 0;
}