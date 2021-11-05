/*
     一棵树，两种操作
     C x：查询x
     T x y：将x子树赋值为y

     子树更新，单点查询

     可以使用树链剖分或者DFS序将树拍平
     然后使用线段树
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef int weight_t;
int const SIZE = 50010;

//边
struct edge_t{
    int to;
    int next;
}Edge[SIZE<<1];
int Vertex[SIZE];
int ECnt;
weight_t W[SIZE];//权值

inline void initGraph(int n){
    ECnt = 1;
    fill(Vertex,Vertex+n+1,0);
}

inline void mkEdge(int a,int b){
    Edge[ECnt].to = b;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;
}

int InIdx[SIZE],OutIdx[SIZE];
int InOut[SIZE<<1];
int NewIdx[SIZE<<1];
int NCnt;

void dfs(int node,int parent){
    NewIdx[++NCnt] = node;
    InOut[NCnt] = 1;
    InIdx[node] = NCnt;
    for(int next=Vertex[node];next;next=Edge[next].next){
        int son = Edge[next].to;
        if ( son != parent ) dfs(son,node);
    }
    NewIdx[++NCnt] = node;
    InOut[NCnt] = -1;
    OutIdx[node] = NCnt;
}

weight_t ST[SIZE<<3];  //线段树保持区间最大值
weight_t Lazy[SIZE<<3];//延迟标记

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

inline void _pushUp(int t){ST[t]=max(ST[lson(t)],ST[rson(t)]);}

inline void _pushDown(int t){
    if ( Lazy[t] ){
        ST[lson(t)] = ST[rson(t)] = Lazy[lson(t)] = Lazy[rson(t)] = Lazy[t];
        Lazy[t] = 0;
    }
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

void modify(int t,int s,int e,int a,int b,weight_t newValue){
    if ( a <= s && e <= b ){
        ST[t] = Lazy[t] = newValue;
        return;
    }

    _pushDown(t);
    int mid = ( s + e ) >> 1;
    if ( a <= mid ) modify(lson(t),s,mid,a,b,newValue);
    if ( mid < b ) modify(rson(t),mid+1,e,a,b,newValue);
    _pushUp(t);
}

weight_t query(int t,int s,int e,int pos){
    if ( s == e ){
        return ST[t];
    }

    _pushDown(t);
    int mid = ( s + e ) >> 1;
    if ( pos <= mid ) return query(lson(t),s,mid,pos);
    return query(rson(t),mid+1,e,pos);
}

int N,Root;
int Flag[SIZE];
void read(){
    N = getUnsigned();

    initGraph(N);

    fill(Flag,Flag+N+1,0);
    int a,b;
    for(int i=1;i<N;++i){
        b = getUnsigned();
        a = getUnsigned();
        mkEdge(a,b);
        if ( 0 == Flag[a] ) Flag[a] = 1;
        Flag[b] = 2;
    }

    for(int i=1;i<=N;++i)if(1==Flag[i]){Root=i;break;}
    NCnt = 0;
    dfs(Root,0);
    fill(Lazy,Lazy+N*8+1,0);
    fill(ST,ST+N*8+1,0);
}
int main(){
    //freopen("1.txt","r",stdin);

    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        read();

        printf("Case #%d:\n",kase);

        int x,y,m = getUnsigned();
        char cmd[3];
        while(m--){
            scanf("%s",&cmd);
            x = getUnsigned();
            if ( 'T' == *cmd ){
                y = getUnsigned();
                modify(1,1,N<<1,InIdx[x],OutIdx[x],y);
            }else{
                int ans = query(1,1,N<<1,InIdx[x]);
                printf("%d\n",ans?ans:-1);
            }
        }
    }
    return 0;
}
