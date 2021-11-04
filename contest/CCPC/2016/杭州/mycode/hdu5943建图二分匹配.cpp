/*
  给定N和S，确定一个区间[S+1,S+N]
  问能否把这N个数进行安排，
  满足数x排在第y个位置且x%y=0

  实质就是[S+1,S+N]到[1,N]建立一个一一映射
  满足x是y的倍数

  质数显然只有2个位置可以排
  如果区间有重合，即S<=N，则
  如果[N+1,S+N]中有2个质数就肯定排不下了
  而且只需把[N+1,S+N]排到[1,S]中即可
  当然，S<=1显然是可行的
  如果区间不重合，即S>N，则[S+1,S+N]有2个质数就排不了

  在7E13的范围内最大质数间隔是777
  所以如果在777范围内，做一个匹配即可
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

//单向边
inline void mkEdge(int a,int b){
	//Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int LinkA[SIZE_OF_VERTICES];//LinkAi is the link of Ai in B
int LinkB[SIZE_OF_VERTICES];//LinkBi is the link of Bi in A

int DA[SIZE_OF_VERTICES],DB[SIZE_OF_VERTICES];//A部分的距离，B部分的距离
int _Q[SIZE_OF_VERTICES];//辅助队列
int _Dis;
bool bfs(int na,int nb){
    fill(DA,DA+na+1,0);
    fill(DB,DB+nb+1,0);

    int *head = _Q, *tail = _Q;
    for(int i=1;i<=na;++i) if ( !LinkA[i] ) *tail++ = i;//入队

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

bool _Flag[SIZE_OF_VERTICES];//辅助标记数组
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

int N,S;
char Str[][12] = {"No","Yes"};

int proc(){
    if(S<=1) return 1;
    if(S<=N){
        if(S>777) return 0;

        //建图,一共(S,S)个点
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
        //建图,一共(N,N)个点
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
