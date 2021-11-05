/*
    在一个树上，选择最少的节点使得所有边都被覆盖
    最小点覆盖等于最大匹配
    输入保证边只出现一次
    但树上不好区分二分图，所以把树重复一次做成二分图
    则边相当于做成双向边
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

vector<int> Graph[SIZE_OF_VERTICES];//二分图矩阵，而不是普通的图矩阵

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


int N;

bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    initGraph(N);
    int n,a,b;
    for(int i=0;i<N;++i){
        scanf("%d:(%d)",&a,&n);
        ++a;
        for(int j=0;j<n;++j){
            scanf("%d",&b);
            mkEdge(a,++b);
            mkEdge(b,a);
        }
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(read()){
        printf("%d\n",HopcroftKarp(N,N)>>1);
    }
    return 0;
}
