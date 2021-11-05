/**
   n×m的棋盘上有k个棋子，给定这k个棋子的初始位置。
   然后每个棋子再给定一个目标位置。棋子位置可以重复
   每一次操作，所有棋子统一移动一格（四邻域，除非动不了）
   目标是每个棋子均到达过其目标位置，在2nm个操作之内。
   可以首先将所有棋子都移动到(1, 1)，最多只要n+m-2步即可
   然后一格一格移动即可，最多需要nm-1步，显然可以在2nm步中完成目标
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

char A[110000];
vector<int> V[210];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    int m = getInt();
    int k = getInt();
    int right=0,bottom=0;
    for(int i=0;i<k;++i){
        int x = getInt();
        int y = getInt();
        right = max(right,y);
        bottom = max(bottom,x);
    }
    --right;--bottom;
    fill(A,A+right,'L');
    fill(A+right,A+right+bottom,'U');
    int tt = right+bottom;
    bottom = 0;
    for(int i=0;i<k;++i){
        int x = getInt();
        int y = getInt();
        V[x].push_back(y);
        bottom = max(bottom,x);
    }
    k = bottom;
    sort(V[k].begin(),V[k].end());
    for(int i=0,nn=k&1?k-1:k-2;i<nn;i+=2){
        fill(A+tt,A+tt+m-1,'R');
        A[tt+=m-1] = 'D';
        ++tt;
        fill(A+tt,A+tt+m-1,'L');
        A[tt+=m-1] = 'D';
        ++tt;
    }
    if(k&1){
        fill(A+tt,A+tt+V[k].back()-1,'R');
        tt += V[k].back()-1;
    }else{
        fill(A+tt,A+tt+m-1,'R');
        A[tt+=m-1] = 'D';
        ++tt;
        fill(A+tt,A+tt+m-*V[k].begin(),'L');
        tt += m-*V[k].begin();
    }
    printf("%d\n",tt);
    puts(A);
    return 0;
}
