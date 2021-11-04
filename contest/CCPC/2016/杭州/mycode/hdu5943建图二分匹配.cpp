/*
  ����N��S��ȷ��һ������[S+1,S+N]
  ���ܷ����N�������а��ţ�
  ������x���ڵ�y��λ����x%y=0

  ʵ�ʾ���[S+1,S+N]��[1,N]����һ��һһӳ��
  ����x��y�ı���

  ������Ȼֻ��2��λ�ÿ�����
  ����������غϣ���S<=N����
  ���[N+1,S+N]����2�������Ϳ϶��Ų�����
  ����ֻ���[N+1,S+N]�ŵ�[1,S]�м���
  ��Ȼ��S<=1��Ȼ�ǿ��е�
  ������䲻�غϣ���S>N����[S+1,S+N]��2���������Ų���

  ��7E13�ķ�Χ��������������777
  ���������777��Χ�ڣ���һ��ƥ�伴��
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//just as its names
int const SIZE_OF_VERTICES = 1010;
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

int N,S;
char Str[][12] = {"No","Yes"};

int proc(){
    if(S<=1) return 1;
    if(S<=N){
        if(S>777) return 0;

        //��ͼ,һ��(S,S)����
        initGraph(S+S);
        for(int i=1;i<=S;++i){
            for(int j=1;j<=S;++j){
                if(0==(N+i)%j){
                    mkEdge(i,j);
                }
            }
        }
        return HopcroftKarp(S,S)==S?1:0;
    }else{
        if(N>777) return 0;
        //��ͼ,һ��(N,N)����
        initGraph(N+N);
        for(int i=1;i<=N;++i){
            for(int j=1;j<=N;++j){
                if(0==(i+S)%(j)){
                    mkEdge(i,j);
                }
            }
        }
        return HopcroftKarp(N,N)==N?1:0;
    }


}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        N = getUnsigned();
        S = getUnsigned();
        printf("Case #%d: %s\n",kase,Str[proc()]);
    }
    return 0;
}
