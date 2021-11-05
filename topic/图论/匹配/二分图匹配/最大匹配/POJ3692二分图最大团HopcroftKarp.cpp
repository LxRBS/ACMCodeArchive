/*
    G��Ů����B���к�
    Ů�����඼��ʶ���к����඼��ʶ
    ���ɶ�Ů�����к���ʶ
    ����Ҫѡ�������ˣ�ʹ����Щ�˶���ʶ

    ���඼��ʶ��ʵ���Ͼ��������Ҳ���������ȫ��ͼ
    ����ŵ���ԭͼ��ͼ����������
    ������ͼ�������������ڶ�������ȥ���ƥ��
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <algorithm>
using namespace std;

//just as its names
int const SIZE_OF_VERTICES = 2010;
int const SIZE_OF_EDGES = 251000;
int const INF = 0x3F3F3F3F;

struct edge_t{
	int from,to;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}

//�����
inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
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

        for(int p=Vertex[u];p;p=Edge[p].next){
            if ( 0 == DB[ v = Edge[p].to ] ){
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
    for(int p=Vertex[u];p;p=Edge[p].next){
        if ( !_Flag[v=Edge[p].to] && DB[v] == DA[u] + 1 ){
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


int G,B,M;
bool A[210][210];
bool read(){
    if ( 3 != scanf("%d%d%d",&G,&B,&M) ) return false;
    if ( 0 == G && 0 == B && 0 == M ) return false;

    initGraph(G);

    memset(A,0,sizeof(A));
    int a,b;
    for(int i=0;i<M;++i){
        scanf("%d%d",&a,&b);
        A[a][b] = true;
    }

    for(int i=1;i<=G;++i)for(int j=1;j<=B;++j)if(!A[i][j])mkEdge(i,j);

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);

    for(int kase=1;read();++kase){
        printf("Case %d: %d\n",kase,G+B-HopcroftKarp(G,B));
    }
    return 0;
}
