/*
    平面上有若干油田
    采油时按1×2或者2×1的矩形采
    也就是说一次必须采2块油田
    问最多能采多少次

    将地图间隔染色，则黑白相间
    合法的采法必然是一黑一白
    所以黑格有油的与白格有油的连一条边
*/

#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

//just as its names
int const SIZE_OF_VERTICES = 100000;
int const SIZE_OF_EDGES = 451000;
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


int N,NA,NB;
char A[603][603];
int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};
int Id[603][603];

bool read(){
    scanf("%d",&N);
    fgets(A[0],100,stdin);
    for(int i=0;i<N;++i){
        fgets(A[i],100,stdin);
        fill(Id[i],Id[i]+N+1,0);
    }

    NA = NB = 0;
    initGraph(N*N/2);

    int a,b;
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)if(((i+j)&1)&&'#'==A[i][j]){
        for(int o=0;o<4;++o){
            int dr = i + DR[o];
            int dc = j + DC[o];

            if ( 0 <= dr && dr < N && 0 <= dc && dc < N && '#' == A[dr][dc] ){
                if ( !Id[i][j] )  Id[i][j] = ++NA;
                a = Id[i][j];

                if ( !Id[dr][dc] ) Id[dr][dc] = ++NB;
                b = Id[dr][dc];

                mkEdge(a,b);
            }
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
        printf("Case %d: %d\n",kase,HopcroftKarp(NA,NB));
    }
    return 0;
}
