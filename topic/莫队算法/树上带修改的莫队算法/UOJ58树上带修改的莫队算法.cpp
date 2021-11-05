#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//利用hash记录LCA
struct Hash{
    typedef struct __t{int a;int b;__t(int aa=0,int bb=0):a(aa),b(bb){}} key_t;
    typedef int value_t;

    enum{MOD=0x1FFFFF};

    key_t keys[MOD+1];
    value_t values[MOD+1];

    int head[MOD+1];
    int next[MOD+1];

    int toUsed;

    Hash():toUsed(0){fill(head,head+MOD+1,-1);}

    void clear(){fill(head,head+toUsed,-1);toUsed=0;}

    int getKey(key_t const&key)const{
        int ret = 17;
        ret = ret * 37 + key.a;
        ret = ret * 37 + key.b;
        return ret;
    }

    void insert(key_t const&key,value_t const&value){
        int k = getKey(key) & MOD;
        keys[toUsed] = key;
        values[toUsed] = value;
        next[toUsed] = head[k];
        head[k] = toUsed++;
    }

    value_t find(key_t const&key)const{
        int k = getKey(key) & MOD;
        for(int i=head[k];i!=-1;i=next[i]){
            if ( keys[i].a == key.a && keys[i].b == key.b ) return values[i];
        }
        return 0;
    }

    void disp(FILE*fp)const{
        for(int i=1;i<toUsed;++i){
            fprintf(fp,"(%d %d): %d\n",keys[i].a,keys[i].b,values[i]);
        }
    }
}Lca;

typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 100010;
int const SIZE_OF_EDGES = 200010;

struct edge_t{
	int from,to;
	//weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 1;
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b){
	//Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	//Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

//生成DFS序
int InIdx[SIZE_OF_VERTICES],OutIdx[SIZE_OF_VERTICES];
int NewIdx[SIZE_OF_VERTICES<<1];
int NCnt = 1;
void dfs(int node,int parent){
    NewIdx[NCnt] = node;
    InIdx[node] = NCnt++;
    for(int next=Vertex[node];next;next=Edge[next].next){
        int to = Edge[next].to;
        if ( to != parent ) dfs(to,node);
    }
    NewIdx[NCnt] = node;
    OutIdx[node] = NCnt++;
}

//Tarjan算法中用到的并查集
int Father[SIZE_OF_VERTICES];
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}

bool Flag[SIZE_OF_VERTICES] = {false};
vector<vector<int> > Questions(SIZE_OF_VERTICES,vector<int>());

//Tarjan算法一次性求出所有的LCA
void Tarjan(int u,int parent){
    Father[u] = u;
    Flag[u] = true;

    for(int next=Vertex[u];next;next=Edge[next].next){
        int to = Edge[next].to;
        if ( to == parent ) continue;
        Tarjan(to,u);
        Father[to] = u;
    }

    vector<int>&vec=Questions[u];
    for(vector<int>::iterator it=vec.begin();it!=vec.end();++it){
        int v = *it;
        if ( Flag[v] ){
            int r = find(v);
            Lca.insert(Hash::key_t(u,v),r);
            Lca.insert(Hash::key_t(v,u),r);
        }
    }
}

int const BLOCK_SIZE = 2000;

struct query_t{
    int s,e,idx;
    int changedCnt;//表示该次询问之前已经经过的修改次数
    int lca;
}Query[SIZE_OF_VERTICES];

bool operator < (query_t const&lhs,query_t const&rhs){
    int la = lhs.s / BLOCK_SIZE;
    int ra = rhs.s / BLOCK_SIZE;
    int lb = lhs.e / BLOCK_SIZE;
    int rb = rhs.e / BLOCK_SIZE;
    return la < ra || ( la == ra && lb < rb ) || ( la == ra && lb == rb && lhs.changedCnt < rhs.changedCnt );
}

struct change_t{
    int node;
    int newValue;//要修改的值
    int preValue;//此次修改之前的值
}Change[SIZE_OF_VERTICES];

typedef long long llt;
int N,M,Q;
llt V[SIZE_OF_VERTICES],W[SIZE_OF_VERTICES];
int C[SIZE_OF_VERTICES];
int QCnt,CCnt;
int PreValue[SIZE_OF_VERTICES];

//将原树上的路径问题转化为DFS序中的区间问题
inline void mkQuestion(int a,int b,int idx){
    int lca = Lca.find(Hash::key_t(a,b));
    if ( lca == a || lca == b ){
        int t = lca == a ? b : a;
        int t1 = InIdx[t] - InIdx[lca];
        int t2 = OutIdx[lca] - OutIdx[t];
        if ( t1 < t2 ){
            Query[idx].s = InIdx[lca];
            Query[idx].e = InIdx[t];
        }else{
            Query[idx].s = OutIdx[t];
            Query[idx].e = OutIdx[lca];
        }
        Query[idx].lca = 0;
    }else{
        Query[idx].lca = lca;
        if ( OutIdx[a] < InIdx[b] ) Query[idx].s = OutIdx[a], Query[idx].e = InIdx[b];
        else Query[idx].s = OutIdx[b], Query[idx].e = InIdx[a];
    }
}

void read(){
    N = getUnsigned();
    M = getUnsigned();
    Q = getUnsigned();

    initGraph(N);

    for(int i=1;i<=M;++i) V[i] = getUnsigned();
    for(int i=1;i<=N;++i) W[i] = getUnsigned();
    for(int i=1;i<N;++i) mkEdge(getUnsigned(),getUnsigned());//双向边才能这样操作
    for(int i=1;i<=N;++i) C[i] = PreValue[i] = getUnsigned();

    dfs(1,0);

    QCnt = CCnt = 0;
    int t,x,y;
    for(int i=0;i<Q;++i){
        t = getUnsigned();
        x = getUnsigned();
        y = getUnsigned();

        if ( 0 == t ){//修改
            Change[CCnt].preValue = PreValue[x], Change[CCnt].node = x, Change[CCnt++].newValue = PreValue[x] = y;
        }else{//查询
            Questions[x].push_back(y);
            Questions[y].push_back(x);
            Query[QCnt].s = x, Query[QCnt].e = y, Query[QCnt].idx = QCnt, Query[QCnt++].changedCnt = CCnt;
        }
    }

    Tarjan(1,0);
    for(int i=0;i<QCnt;++i) mkQuestion(Query[i].s,Query[i].e,i);
}


int CurCnt[SIZE_OF_VERTICES];//用于记录当前区间中的第i种糖果有多少个
int curLeft,curRight,curChangedCnt;
llt MoAns;
llt Ans[SIZE_OF_VERTICES];

//n代表糖果种类
inline void insert(int n){
    MoAns += V[n] * W[++CurCnt[n]];
}

inline void remove(int n){
    MoAns -= V[n] * W[CurCnt[n]--];
}

void MoOp(int node){
    if ( Flag[node] ) remove(C[node]);
    else insert(C[node]);
    Flag[node] ^= 1;
}

inline void change(int node,int newValue){
    if ( Flag[node] ) MoOp(node), C[node] = newValue, MoOp(node);
    else C[node] = newValue;
}

void Mo(){
    sort(Query,Query+QCnt);
    fill(Flag,Flag+N+1,false);

    curLeft = 1, curRight = curChangedCnt = 0;
    MoAns = 0;
    int lca;

    for(int i=0;i<QCnt;++i){
        //当前修改次数未达到，执行修改
        while( curChangedCnt < Query[i].changedCnt ) change(Change[curChangedCnt].node,Change[curChangedCnt].newValue),++curChangedCnt;
        //当前修改次数已超过，撤销修改
        while( curChangedCnt > Query[i].changedCnt ) --curChangedCnt,change(Change[curChangedCnt].node,Change[curChangedCnt].preValue);
        //基本莫队操作
        while( curRight < Query[i].e ) MoOp(NewIdx[++curRight]);
        while( curLeft > Query[i].s ) MoOp(NewIdx[--curLeft]);
        while( curRight > Query[i].e ) MoOp(NewIdx[curRight--]);
        while( curLeft < Query[i].s ) MoOp(NewIdx[curLeft++]);
        Ans[Query[i].idx] = MoAns;
        if ( lca = Query[i].lca ) Ans[Query[i].idx] += V[C[lca]] * W[CurCnt[C[lca]]+1];
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    read();
    Mo();
    for(int i=0;i<QCnt;++i) printf("%lld\n",Ans[i]);
    return 0;
}
