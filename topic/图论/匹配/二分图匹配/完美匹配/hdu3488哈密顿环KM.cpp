/*
    有向带权图，
    要求走出一个包括所有节点的Hamilton环的最小费用
    题目保证有环
    KM算法求最大值，稍作变化即可求最小值
*/

#include <stdio.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long int weight_t;

int const SIZE = 410;
weight_t const INF = 1LL<<62;

weight_t Graph[SIZE][SIZE];//图的邻接矩阵
//LinkAi表示与Ai相连的点，LinkBi表示与Bi相连的点
int LinkA[SIZE],  LinkB[SIZE];
//辅助标记数组
bool FlagA[SIZE], FlagB[SIZE];
int Pre[SIZE];

weight_t LabelA[SIZE], LabelB[SIZE];
weight_t Slack[SIZE];

int Q[SIZE<<1];//辅助队列
inline void bfs(int u,int n) {
    weight_t tmp;
    int v, head=0, tail = 0;
	FlagA[Q[tail++] = u] = true;

DEAD_LOOP:
	while(head < tail) {

		for(u = Q[head++],v=1;v<=n;++v)if(!FlagB[v]){
			if ( (tmp = LabelA[u]+LabelB[v]-Graph[u][v]) > Slack[v] ) continue;

            Pre[v] = u;
			if(!tmp) {
				FlagB[v] = true;
				if(!LinkB[v]) {
					while(v) LinkB[v] = Pre[v], swap(LinkA[Pre[v]], v);
		            return;
				}
				FlagA[ Q[tail++]=LinkB[v] ] = true;
			}else{
			    Slack[v] = tmp;
			}
		}
	}

	tmp = INF;
	for(int i=1;i<=n;++i) if(!FlagB[i]&&Slack[i]<tmp) tmp = Slack[i];
	for(int i=1;i<=n;++i) {
		if(FlagA[i]) LabelA[i] -= tmp;
		if(FlagB[i]) LabelB[i] += tmp;
		else Slack[i] -= tmp;
	}

	for(v = 1; v <= n; ++v) {
		if(!FlagB[v] && !Slack[v]) {
			FlagB[v] = true;
			if(!LinkB[v]) {
				while(v) LinkB[v] = Pre[v], swap(LinkA[Pre[v]], v);
				return;
			}
			FlagA[ Q[tail++] = LinkB[v] ] = true;
		}
	}
	goto DEAD_LOOP;
}

weight_t KM(int n){
    fill(LinkA,LinkA+n+1,0);
    fill(LinkB,LinkB+n+1,0);
    fill(LabelB,LabelB+n+1,0);
    fill(Pre,Pre+n+1,0);
    for(int i=1;i<=n;++i) LabelA[i] = *max_element(Graph[i]+1,Graph[i]+n+1);

    for(int i=1;i<=n;++i){
        fill(Slack,Slack+n+1,INF);
        fill(FlagA,FlagA+n+1,false);
        fill(FlagB,FlagB+n+1,false);
        bfs(i,n);
    }

    weight_t ret = 0;
    for(int i=1;i<=n;++i) ret += LabelA[i] + LabelB[i];
    return ret;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,M;
weight_t UPER = 20000LL;
bool read(){
    N = getUnsigned();
    M = getUnsigned();

    for(int i=1;i<=N;++i) fill(Graph[i],Graph[i]+N+1,0);

    int a,b,w;
    for(int i=0;i<M;++i){
        a = getUnsigned();
        b = getUnsigned();
        w = UPER - getUnsigned();
        //注意重边
        if ( Graph[a][b] < w ) Graph[a][b] = w;
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while( nofkase-- ){
        read();
        printf("%I64d\n", UPER * N - KM(N));
    }
    return 0;
}
