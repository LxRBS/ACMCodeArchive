//����ͼ���ƥ��
//����2������A/B��Ҫ���A��B��ɾ�����ɸ�����ʹ��B���κ���������A���κ����ı�����Ҫ��ɾ��������������
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

//just as its names
int const SIZE_OF_VERTICES = 210;
int const SIZE_OF_EDGES = 20100;

struct edge_t{
	int from,to;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

int L[SIZE_OF_VERTICES];//Li���i����ƥ��ĵ㣬ע�����������ȫͼ�ı�Ŷ����Ƕ���ͼ��ţ��ر��Ƕ�B���ֵĵ�

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
	fill(L,L+n+1,0);
}

//�����
inline void mkEdge(int a,int b){
	//Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int D[SIZE_OF_VERTICES];
int Q[SIZE_OF_VERTICES];//��������
bool bfs(int na,int nb,int n){
    bool ret = false;
    fill(D,D+n+1,0);

    int head,tail = 0;
    for(int i=1;i<=na;++i) if ( !L[i] ) Q[tail++] = i;//���

    int u,v;
    for(head=0;head<tail;++head){
        //��ÿһ�����ÿһ����
        for(int p=Vertex[u=Q[head]];p;p=Edge[p].next){
            if ( !D[v=Edge[p].to] ){
                D[v] = D[u] + 1;
                if ( !L[v] ) ret = true;
                else D[L[v]] = D[v] + 1, Q[tail++] = L[v];
            }
        }
    }
    return ret;
}

bool dfs(int u){
    int v;
    for(int p=Vertex[u];p;p=Edge[p].next){
        if ( D[v=Edge[p].to] == D[u] + 1 ){
            D[v] = 0;
            if ( !L[v] || dfs(L[v]) ){
                L[ L[v] = u ] = v;
                return true;
            }
        }
    }
    return false;
}

//na��A��������nb��B��������n��������
int HopcroftKarp(int na,int nb,int n){
    int ret = 0;
    while( bfs(na,nb,n) ){
        for(int i=1;i<=na;++i){
            if ( !L[i] && dfs(i) ) ++ret;
        }
    }
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
int A[SIZE_OF_VERTICES];
bool read(){
    N = getUnsigned();
    for(int i=1;i<=N;++i)A[i]=getUnsigned();
    M = getUnsigned();

    initGraph(N+M);
    int b;
    for(int i=1;i<=M;++i){
        b = getUnsigned();
        for(int j=1;j<=N;++j)if(0==b%A[j])mkEdge(j,i+N);
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case %d: %d\n",kase,HopcroftKarp(N,M,N+M));
    }
    return 0;
}
