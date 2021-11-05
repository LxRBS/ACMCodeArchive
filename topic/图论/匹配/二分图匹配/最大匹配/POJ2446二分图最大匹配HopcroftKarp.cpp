/*
    M��N�������ϣ���Щ���Ӵ��˶������ܷ���
    �����Ϸ���1��2�Ķ���ŵ
    ���ܷ�ǡ�÷���

    ������ģ�ͣ����̸�����ż�Էֳɺڰ�2����ɫ
    ����ŵ��Ȼ����һ��һ��
    �ܹ����ö���ŵ�ĺڰ׸���һ����
    ���Ƿ�������ƥ��
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

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

int N,M,K;
int A[50][50];
int NA,NB;

bool read(){
    if ( 3 != scanf("%d%d%d",&N,&M,&K) ) return false;

    memset(A,0,sizeof(A));
    int a,b;
    for(int i=0;i<K;++i){
        scanf("%d%d",&a,&b);
        A[b][a] = -1;
    }

    //����ͼ
    initGraph(N*M);
    NA = NB = 0;
    for(int i=1;i<=N;++i)for(int j=1;j<=M;++j)if(0==(i+j)%2&&-1!=A[i][j]){
        A[i][j] = ++NA;

        for(int d=0;d<4;++d){
            int di = i + DR[d];
            int dj = j + DC[d];
            if ( 1 <= di && di <= N && 1 <= dj && dj <= M && -1 != A[di][dj] ){
                //if ( 0 == A[i][j] ) A[i][j] = ++NA;
                if ( 0 == A[di][dj] ) A[di][dj] = ++NB;
                mkEdge(A[i][j],A[di][dj]);
            }
        }
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);

    while( read() ){
        printf(NA==NB&&HopcroftKarp(NA,NB)==NA?"YES\n":"NO\n");
    }
    return 0;
}
