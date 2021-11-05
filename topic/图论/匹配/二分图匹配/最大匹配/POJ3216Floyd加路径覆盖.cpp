/*
    Q���㣬ÿ����֮��˫���·����
    M������ÿ������λ��һ���㣬ÿ�������ti��ʼ������diʱ��
    ÿ����ֻ�������һ������Ȼ����п������ŵ�·������һ�����������һ������
    ��������Ҫ������
    ����һ���˿�����ɵ�����֮�佨�ߣ��϶���DAG����һ����С·������
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_VERTICES = 210;
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
	//Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int LinkA[SIZE_OF_VERTICES];//LinkAi is the link of Ai in B
int LinkB[SIZE_OF_VERTICES];//LinkBi is the link of Bi in A

int DA[SIZE_OF_VERTICES],DB[SIZE_OF_VERTICES];//A���ֵľ��룬B���ֵľ���
int _Q[SIZE_OF_VERTICES];//��������
int _Dis;
bool bfs(int na,int nb){
    fill(DA,DA+na+1,0);
    fill(DB,DB+nb+1,0);

    int *head = _Q, *tail = _Q;
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

int Q,M;
int A[22][22];
int P[220],T[220],D[220];
void Floyd(int n){
    for(int k=1;k<=n;++k)for(int i=1;i<=n;++i)for(int j=1;j<=n;++j){
        A[i][j] = min(A[i][j],A[i][k]+A[k][j]);
    }
}
bool read(){
    scanf("%d%d",&Q,&M);
    if ( 0 == Q && 0 == M ) return false;
    for(int i=1;i<=Q;++i)for(int j=1;j<=Q;++j){
        scanf("%d",A[i]+j);
        if ( -1 == A[i][j] ) A[i][j] = INF;
    }

    Floyd(Q);

    for(int i=1;i<=M;++i)scanf("%d%d%d",P+i,T+i,D+i);

    initGraph(M);
    for(int i=1;i<=M;++i)for(int j=1;j<=M;++j)if(i!=j){
        if ( T[i] + D[i] + A[P[i]][P[j]] <= T[j] ) mkEdge(i,j);
    }
    return true;
}
int main(){
    while(read()){
        printf("%d\n",M-HopcroftKarp(M,M));
    }
    return 0;
}
