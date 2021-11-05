/*
    DAG������С·��������
    ������ظ�ʹ��
    �������С·�������ǲ��������ظ�ʹ�õ�
    ���ظ�������£�����Ҫ��һ���հ����������е�uv�ɴ�u��v��һ����
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

vector<int> Graph[SIZE_OF_VERTICES];//����ͼ���󣬶�������ͨ��ͼ����

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	for(int i=1;i<=n;++i) Graph[i].clear();
}

//�����
inline void mkEdge(int a,int b){
	Graph[a].push_back(b);
}

int LinkA[SIZE_OF_VERTICES];//LinkAi is the link of Ai in B
int LinkB[SIZE_OF_VERTICES];//LinkBi is the link of Bi in A

int DA[SIZE_OF_VERTICES],DB[SIZE_OF_VERTICES];//A���ֵľ��룬B���ֵľ���
int Q[SIZE_OF_VERTICES];//��������
int _Dis;
bool bfs(int na,int nb){
    fill(DA,DA+na+1,0);
    fill(DB,DB+nb+1,0);

    int *head = Q, *tail = Q;
    for(int i=1;i<=na;++i) if ( !LinkA[i] ) *tail++ = i;//���

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

bool _Flag[SIZE_OF_VERTICES];//�����������
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

//na��A��������nb��B������
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

bool G[505][505];
void Floyd(int n){
    for(int k=1;k<=n;++k)for(int i=1;i<=n;++i)if(G[i][k])for(int j=1;j<=n;++j)G[i][j] = G[i][j] || ( G[i][k] && G[k][j] );
}

int N,M;

bool read(){
    if ( EOF == scanf("%d%d",&N,&M) || (0==N&&0==M) ) return false;

    memset(G,0,sizeof(G));

    int a,b;
    for(int i=0;i<M;++i){
        scanf("%d%d",&a,&b);
        G[a][b] = true;
    }

    //��һ���հ���Floyd
    Floyd(N);

    initGraph(N);
    for(int i=1;i<=N;++i)for(int j=1;j<=N;++j)if(G[i][j])mkEdge(i,j);

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);

    while(read()){
        printf("%d\n",N-HopcroftKarp(N,N));
    }
    return 0;
}
