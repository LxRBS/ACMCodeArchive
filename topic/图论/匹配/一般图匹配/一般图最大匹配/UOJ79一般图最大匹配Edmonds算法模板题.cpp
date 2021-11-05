/*
    一般图最大匹配，模板题
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

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

int N,M;
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    initGraph(N);
    int a,b;
    for(int i=0;i<M;++i){
        scanf("%d%d",&a,&b);
        mkEdge(a,b);
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        int ans = Edmonds(N);
        printf("%d\n",ans);
        for(int i=1;i<=N;++i){
            printf("%d ",Succ[i]);
        }
        printf("\n");
    }
    return 0;
}
