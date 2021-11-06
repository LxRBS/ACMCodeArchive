/**
    树，2种操作
    1 x y: 将x节点的颜色改成y
    2 a b c d:问路径ab的颜色总数是否比路径cd上的多
    
    N个节点，M次操作，在线，N在50万，M在1万，颜色总数为N
    如果是均匀分布的话，对于大小为K的集合，每次生成一个均匀分布
    则K越大，最大值的期望越大
    首先为每个节点随机赋权值，一共Sample_Cnt组
    然后求路径最大值
    如果ab路径的最大值期望比cd路径的最大值要大，
    说明ab路径上不同值的数量要多
    最后是一个树链剖分，单点更新，路径查询
*/
#pragma comment(linker, "/STACK:1024000000,1024000000")
//#include <bits/stdc++.h>
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

int const SIZE = 500010;
typedef int weight_t;
typedef long long llt;

//采样数量为20还是错误，30正确
int const Sample_Cnt = 30;
weight_t OriginW[SIZE][Sample_Cnt];

struct edge_t{
    int to;
    int next;
}Edge[SIZE<<1];
int Vertex[SIZE];
int ECnt;

int Col[SIZE];//Coli不是真正的颜色，而是颜色在OriginW中的编号

inline void mkEdge(int a,int b){
    Edge[ECnt].to = b;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].to = a;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

struct node_t{
    int parent;
    int heavy_son;
    int depth;
    int size;
    int top;
    int nid;
}Node[SIZE] = {{0,0,0,0,0,0}};
int NCnt;
int NewIdx[SIZE];

void dfsHeavyEdge(int node,int parent,int depth){
    Node[node].depth = depth;
    Node[node].parent = parent;
    Node[node].size = 1;
    Node[node].heavy_son = 0;

    for(int next=Vertex[node];next;next=Edge[next].next){
        int to = Edge[next].to;
        if ( to == parent ) continue;

        dfsHeavyEdge(to,node,depth+1);
        Node[node].size += Node[to].size;

        if ( Node[to].size > Node[Node[node].heavy_son].size ) Node[node].heavy_son = to;
    }
}

void dfsHeavyPath(int node,int top){
    Node[node].top = top;
    Node[node].nid = NCnt++;
    NewIdx[Node[node].nid] = node;

    if ( 0 == Node[node].heavy_son ) return;
    dfsHeavyPath(Node[node].heavy_son,top);

    for(int next=Vertex[node];next;next=Edge[next].next){
        int to = Edge[next].to;
        if ( to != Node[node].parent && to != Node[node].heavy_son ) dfsHeavyPath(to,to);
    }
}

int N,M;
weight_t StPeak[SIZE<<2][Sample_Cnt];

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

inline void _pushUp(int t){
    int left = lson(t), right = rson(t);
    for(int i=0;i<Sample_Cnt;++i){
        StPeak[t][i] = max(StPeak[left][i],StPeak[right][i]);
    }
}

void build(int t,int s,int e){
    if ( s == e ){
        weight_t o = Col[NewIdx[s]];
        for(int i=0;i<Sample_Cnt;++i){
            StPeak[t][i] = OriginW[o][i];
        }
        return;
    }

    int m = ( s + e ) >> 1;
    build(lson(t),s,m);
    build(rson(t),m+1,e);
    _pushUp(t);
}

//线段树单点更新
void modify(int t,int s,int e,int idx,weight_t newValue){
    if ( s == e ){
        for(int i=0;i<Sample_Cnt;++i){
            StPeak[t][i] = OriginW[newValue][i];
        }
        return;
    }

    int m = ( s + e ) >> 1;
    if ( idx <= m ) modify(lson(t),s,m,idx,newValue);
    else modify(rson(t),m+1,e,idx,newValue);
    _pushUp(t);
}

//线段树区间查询，[a,b]之间的最大值 
weight_t Q_Ans[SIZE];
void qPeak(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){
        for(int i=0;i<Sample_Cnt;++i){
            Q_Ans[i] = max(Q_Ans[i], StPeak[t][i]);
        }
        return;
    }

    int m = ( s + e ) >> 1;
    if ( a <= m ) qPeak(lson(t),s,m,a,b);
    if ( m < b ) qPeak(rson(t),m+1,e,a,b);
}

inline void change(int x,weight_t newValue){
    modify(1,1,N,Node[x].nid,newValue);
}

//树上操作，查询xy路径的最大值 
//返回平均值，实际上返回的是总和 
weight_t qPeak(int x,int y){
    fill(Q_Ans,Q_Ans+Sample_Cnt,0);

    while( Node[x].top != Node[y].top ){
        if ( Node[Node[x].top].depth < Node[Node[y].top].depth ) swap(x,y);

        qPeak(1,1,N,Node[Node[x].top].nid,Node[x].nid);
        x = Node[Node[x].top].parent;
    }

    if ( Node[x].depth > Node[y].depth ) swap(x,y);
    qPeak(1,1,N,Node[x].nid,Node[y].nid);

    weight_t ret = 0;
    for(int i=0;i<Sample_Cnt;++i){
        ret += Q_Ans[i];
    }
    return ret;
}

inline void initTree(int n){
    ECnt = NCnt = 1;
    fill(Vertex,Vertex+n+1,0);
}

int YesCnt = 0;
void proc(){
    int cmd,a,b,c,d;
    while(M--){
        cmd = getUnsigned();
        a = getUnsigned() ^ YesCnt;
        b = getUnsigned() ^ YesCnt;
        if(1==cmd){
            change(a,b);
        }else{
            c = getUnsigned() ^ YesCnt;
            d = getUnsigned() ^ YesCnt;
            weight_t ans_ab = qPeak(a,b);
            weight_t ans_cd = qPeak(c,d);
            if(ans_ab>ans_cd){
                ++YesCnt;
                puts("Yes");
            }else{
                puts("No");
            }

        }
    }
}

int main(){
    //freopen("2.txt","w",stdout);
    //首先随机生成均匀分布，充作权值
    for(int i=1;i<SIZE;++i)for(int j=0;j<Sample_Cnt;++j){
        OriginW[i][j] = rand();
    }

    int nofkase = getUnsigned();
    while(nofkase--){
        YesCnt = 0;

        initTree(N = getUnsigned());
        M = getUnsigned();

        //读取权值，并转换
        for(int i=1;i<=N;++i){
            Col[i] = getUnsigned();
        }
        for(int i=1;i<N;++i){
            mkEdge(getUnsigned(),getUnsigned());
        }
        //找重边
        dfsHeavyEdge(1,0,0);
        //找重链
        dfsHeavyPath(1,1);
        //建线段树
        build(1,1,N);
        //答问题
        proc();
    }
    return 0;
}
