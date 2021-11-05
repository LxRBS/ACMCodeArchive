/*
    n×n的方格有50种颜色气球
    每个人有k次机会，每次机会选择一行或者一列的某种颜色的气球全部打破
    问选择哪些颜色，可以在这k次机会中把该种颜色的气球全部打破
    对每种颜色建一个图，行列相交则建边，最小点覆盖
*/
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

//just as its names
int const SIZE_OF_VERTICES = 210;
int const SIZE_OF_EDGES = 40010;
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

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,K;
int A[110][110];
vector<pair<int,int> > G[51];
bool read(){
    N = getUnsigned(); K = getUnsigned();
    if ( 0 == N && 0 == K ) return false;

    for(int i=1;i<=50;++i) G[i].clear();
    for(int i=1;i<=N;++i)for(int j=1;j<=N;++j){
        G[getUnsigned()].push_back(make_pair(i,j));
    }
    return true;
}
vector<int> Ans;
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        Ans.clear();
        for(int i=1;i<=50;++i){
            initGraph(100);
            vector<pair<int,int> >&v = G[i];
            for(vector<pair<int,int> >::iterator it=v.begin();it!=v.end();++it) mkEdge(it->first,it->second);
            if ( HopcroftKarp(100,100) > K ) Ans.push_back(i);
        }

        if ( Ans.empty() ){
            printf("-1\n");
            continue;
        }

        printf("%d",*Ans.begin());
        for(vector<int>::iterator it=++Ans.begin();it!=Ans.end();++it)printf(" %d",*it);
        printf("\n");
    }
    return 0;
}
