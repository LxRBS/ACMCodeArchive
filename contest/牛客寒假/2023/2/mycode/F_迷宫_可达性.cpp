/**
 * N*3的迷宫，首先有K个操作，将某一格在通路与障碍物之间进行切换。
 * 左上为起点，右下为终点。
 * 然后做如下走法：如果起点和终点想通，从起点走到终点，再直接从终点跳回起点。
 * 如此反复，不限次数。
 * 问，最多能经过多少个格子。
 * 实际上就是问起点可达且可到终点的格子有多少个。
 * 深搜或者广搜均可。
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 23;
#else
int const SIZE = 110;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

llt const MOD = 998244353LL;
inline llt add(llt a, llt b){return (a+b)%MOD;}

int N, K;
vvi A;
vvi D;
vvi U;

void dfs(int x, int y){
    if(1 == D[x][y]) return;
    D[x][y] = 1;
    if(x + 1 < N && 0 == A[x+1][y]){
        dfs(x + 1, y);
    }
    if(y < 2 && 0 == A[x][y+1]){
        dfs(x, y + 1);
    }
}

void dfsZhongdian(int x, int y){
    if(1 == U[x][y]) return;
    U[x][y] = 1;
    if(x - 1 >= 0 && 0 == A[x-1][y]){
        dfsZhongdian(x - 1, y);
    }
    if(y > 0 && 0 == A[x][y - 1]){
        dfsZhongdian(x, y - 1);
    }
}

int proc(){
    D.assign(N, vi(3, 0));
    dfs(0, 0);  

    U.assign(N, vi(3, 0));
    dfsZhongdian(N-1, 2); 

    int ans = 0;
    for(int i=0;i<N;++i){
        for(int j=0;j<3;++j){
            if(1 == D[i][j] && 1 == U[i][j]){
                ++ans;
            }
        }
    }
    return ans ? ans - 1 : 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        K = getInt();
        A.assign(N, vi(3, 0));
        for(int x,y,i=0;i<K;++i){
            x = getInt() - 1;
            y = getInt() - 1;
            A[x][y] ^= 1; 
        }
        printf("%d\n", proc());
    }

    return 0;
}


