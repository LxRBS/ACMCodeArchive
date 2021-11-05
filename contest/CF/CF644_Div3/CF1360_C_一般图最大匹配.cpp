/**
 * 有N（偶数）个数，任意两个数如果同奇同偶可以配对，相差为1也可以配对。
 * 问是否能够恰好把这N个数两两配对。
 * 一般图最大匹配，可以证明不是二分图，因为有奇数环。
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

typedef long long llt;

llt getULL(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}

llt const MOD = 998244353LL;

#ifndef ONLINE_JUDGE
int const SIZE =12;
#else 
int const SIZE = 155;
#endif

//并查集
struct ufs_t{
    enum {SIZE=510};
    int father[SIZE];
    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

int const SIZE_OF_VERTICES = 510;
int const SIZE_OF_EDGES = 250000;

struct edge_t{
    int from,to;
    int next;
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

inline void initGraph(int n){
    ECnt = 2;
    fill(Vertex,Vertex+n+1,0);
}

//双向边
inline void mkEdge(int a, int b){
    Edge[ECnt].to = b;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt ++;

	Edge[ECnt].to = a;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt ++;
}

int SType[SIZE_OF_VERTICES];
int Prec[SIZE_OF_VERTICES];//前驱
int Succ[SIZE_OF_VERTICES];//后继

int _Vis[SIZE_OF_VERTICES];
int getLca(int x,int y){
    static int tim = 0;
    ++tim;

    for(x=UF.find(x),y=UF.find(y);;swap(x,y)){
        if ( x ){
            if ( _Vis[x] == tim ) return x;
            _Vis[x] = tim;
            x = UF.find(Prec[Succ[x]]);
        }
    }
}

//辅助队列
int Queue[SIZE_OF_VERTICES];
int *QHead, *QTail;

void blossom(int x,int y,int lca){
    while( UF.find(x) != lca ){
        Prec[x] = y;
        y = Succ[x];
        if ( 2 == SType[y] ) SType[*QTail++ = y] = 1;
        UF.father[x] = UF.father[y] = lca;
        x = Prec[y];
    }
}

int bfs(int node,int vn){
    //初始化
    UF.init(vn);
    fill(SType,SType+vn+1,0);

    QHead = QTail = Queue;
    SType[*QTail++ = node] = 1;

    int u,v;
    while( QHead < QTail ){
        for(int p=Vertex[u=*QHead++];p;p=Edge[p].next){
            if ( 0 == SType[v=Edge[p].to] ){
                Prec[v] = u;
                SType[v] = 2;
                if ( !Succ[v] ){
                    for(int uu=v,vv=u,last;vv;uu=last,vv=Prec[uu])
						last=Succ[vv],Succ[vv]=uu,Succ[uu]=vv;
					return 1;
                }
                SType[*QTail++ = Succ[v]] = 1;
            }else if ( 1 == SType[v] && UF.find(v) != UF.find(u) ){//奇环，且不在同一个环
                int lca = getLca(v,u);
                blossom(u,v,lca);
                blossom(v,u,lca);
            }
        }
    }
    return 0;
}

int Edmonds(int vn){
    fill(Prec,Prec+vn+1,0);
    fill(Succ,Succ+vn+1,0);

    int ret = 0;
    for(int i=1;i<=vn;++i){
        if ( !Succ[i] ) ret += bfs(i,vn);
    }
    return ret;
}

int N, A[SIZE];


int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getUnsigned();
	while(nofkase--){
		initGraph(N = getUnsigned());
		for(int i=1;i<=N;++i){
			A[i] = getUnsigned();
            for(int j=1;j<i;++j){
				if((A[j]&1) == (A[i]&1)){
					mkEdge(i, j);
				}else if(A[i]+1==A[j] || A[j]+1==A[i]){
					mkEdge(i, j);
				}
			}
		}
        puts((Edmonds(N)<<1) == N ? "YES" : "NO");
	}
	return 0;
}