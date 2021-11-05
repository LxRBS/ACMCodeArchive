/*
    一般图最大匹配
    问哪些边是进不了任何最大匹配的

    一共有3种边：
    1、最大匹配必备边，没有它就没有最大匹配
    2、最大匹配可选边，某一个最大匹配会包含这种边，但没有这个边，还可以做成另外一种最大匹配
    3、任何最大匹配都不会包含这种边
    本题求第三种边

    将每一条边强制匹配，实际上就是把该边的两个端点删除
    然后看剩下的能否匹配出最大匹配减一
    如果可以，就证明该边可以包含在某个最大匹配中
    则该边必然为第1/2种边

    反过来说，如果匹配数小于最大匹配减一，则该边必然是第三种边
*/
#include <cstdio>
#include <vector>
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

bool Graph[SIZE_OF_VERTICES][SIZE_OF_VERTICES];

inline void initGraph(int n){
    for(int i=1;i<=n;++i) fill(Graph[i],Graph[i]+n+1,false);
}

//双向边
inline void mkEdge(int a, int b){
    Graph[a][b] = Graph[b][a] = true;
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
        u = *QHead++;
        for(int v=1;v<=vn;++v)if(Graph[u][v]){
            if ( 0 == SType[v] ){
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
pair<int,int> Edges[SIZE_OF_EDGES];
bool Origin[SIZE_OF_VERTICES][SIZE_OF_VERTICES];

bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    initGraph(N);
    for(int i=1;i<=N;++i)fill(Origin[i],Origin[i]+N+1,false);

    int a,b;
    for(int i=1;i<=M;++i){
        scanf("%d%d",&a,&b);
        mkEdge(a,b);
        Origin[a][b] = Origin[b][a] = true;
        Edges[i].first = a, Edges[i].second = b;
    }
    return true;
}

bool Flag[SIZE_OF_EDGES];
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        int ret = Edmonds(N);
        fill(Flag,Flag+M+1,false);

        vector<int> ans;
        for(int i=1;i<=M;++i){
            int a = Edges[i].first;
            int b = Edges[i].second;

            //删除点a点b
            for(int j=1;j<=N;++j){
                Graph[a][j] = Graph[j][a] = Graph[b][j] = Graph[j][b] = false;
            }

            if ( Edmonds(N) < ret - 1 ) ans.push_back(i);

            //还原
            for(int j=1;j<=N;++j){
                Graph[a][j] = Origin[a][j];
                Graph[j][a] = Origin[j][a];
                Graph[b][j] = Origin[b][j];
                Graph[j][b] = Origin[j][b];
            }
        }
        printf("%d\n",ans.size());
        if ( !ans.empty() ) {
            printf("%d",ans[0]);
            for(unsigned i=1;i<ans.size();++i)printf(" %d",ans[i]);            
        }
        printf("\n");
    }
    return 0;
}
