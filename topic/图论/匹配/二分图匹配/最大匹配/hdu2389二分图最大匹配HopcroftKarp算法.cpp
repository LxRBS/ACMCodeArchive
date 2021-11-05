/*
    平面上有m个人，n把伞
    每个人有一个速度
    问在时限内最多有多少个人可以到达伞
    每把伞一个人
    显然是二分图最大匹配

    这个题目用邻接表会超时，用vector则很快
    但实际上vector在别的题目上的表现并不突出
*/

#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

//just as its names
int const SIZE_OF_VERTICES = 4000;
int const SIZE_OF_EDGES = 251000;
int const INF = 0x3F3F3F3F;

vector<int> Graph[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	for(int i=1;i<=n;++i) Graph[i].clear();
}

//单向边
inline void mkEdge(int a,int b){
	Graph[a].push_back(b);
}

int LinkA[SIZE_OF_VERTICES];//LinkAi is the link of Ai in B
int LinkB[SIZE_OF_VERTICES];//LinkBi is the link of Bi in A

int DA[SIZE_OF_VERTICES],DB[SIZE_OF_VERTICES];//A部分的距离，B部分的距离
int Q[SIZE_OF_VERTICES];//辅助队列
int _Dis;
bool bfs(int na,int nb){
    fill(DA,DA+na+1,0);
    fill(DB,DB+nb+1,0);

    int *head = Q, *tail = Q;
    for(int i=1;i<=na;++i) if ( !LinkA[i] ) *tail++ = i;//入队

    _Dis = INF;
    int u,v;
    while( head < tail ){
        if ( DA[u = *head++] > _Dis ) continue;

        for(vector<int>::iterator it=Graph[u].begin();it!=Graph[u].end();++it){
            if ( 0 == DB[ v = *it ] ){
                DB[v] = DA[u] + 1;
                if ( LinkB[v] ) DA[ *tail++ = LinkB[v] ] = DB[v] + 1;
                else _Dis = DB[v];
            }
        }
    }
    return _Dis < INF;
}

bool _Flag[SIZE_OF_VERTICES];//辅助标记数组
bool dfs(int u){
    int v;
    for(vector<int>::iterator it=Graph[u].begin();it!=Graph[u].end();++it){
        if ( !_Flag[v=*it] && DB[v] == DA[u] + 1 ){
            _Flag[v] = true;
            if ( !LinkB[v] || ( DB[v] != _Dis && dfs(LinkB[v]) ) ){
                LinkA[ LinkB[v] = u ] = v;
                return true;
            }
        }
    }
    return false;
}

//na是A的数量，nb是B的数量
int HopcroftKarp(int na,int nb){
	fill(LinkA,LinkA+na+1,0);
	fill(LinkB,LinkB+nb+1,0);

    int ret = 0;
    while( bfs(na,nb) ){
        fill(_Flag,_Flag+nb+1,false);
        for(int i=1;i<=na;++i){
            if ( !LinkA[i] ) ret += dfs(i);
        }
    }
    return ret;
}

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

int M,N,T,Ans;
int X[SIZE_OF_VERTICES],Y[SIZE_OF_VERTICES],Speed[SIZE_OF_VERTICES];
int XB[SIZE_OF_VERTICES],YB[SIZE_OF_VERTICES];
bool read(){
    T = getInt();T *= T;
    M = getInt();

    int s;
    for(int i=1;i<=M;++i){
        X[i] = getInt();
        Y[i] = getInt();
        s = getInt();
        Speed[i] = s * s;
    }

    N = getInt();
    int *x = XB, *y = YB;
    for(int i=1;i<=N;++i){
        x[i] = getInt();
        y[i] = getInt();
    }

    initGraph(M);

    for(int i=1;i<=M;++i)for(int j=1;j<=N;++j){
        int x = X[i] - XB[j];
        int y = Y[i] - YB[j];

        if ( x*x + y*y <= T*Speed[i] ){
            mkEdge(i,j);
        }
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Scenario #%d:\n%d\n\n",kase,Ans+HopcroftKarp(M,N));
    }
    return 0;
}
