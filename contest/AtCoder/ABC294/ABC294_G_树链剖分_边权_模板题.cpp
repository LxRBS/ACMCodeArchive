/**
 * 真模板题，把SPOJ的题目改一下输入输出即可。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;


char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}


#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;
// using i128 = __int128_t;

int N,M;

struct edge_t{
	int node;//另一个节点的编号
	int w;   //边权
	int idx; //边序号
	int next;//下一条边的地址，实际地址为Edge+next
}Edge[SIZE<<1];
int ECnt = 0;
int Vertex[SIZE];//邻接表表示所有的边
int E2V[SIZE];//边到点的映射

//a、b之间建立两条无向边
void mkEdge(int a,int b,int w,int idx){
	Edge[ECnt].node = b;
	Edge[ECnt].w = w;
	Edge[ECnt].idx = idx;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].node = a;
	Edge[ECnt].w = w;
	Edge[ECnt].idx = idx;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

struct node_t{
    int parent;   //父节点
	int heavy_son;//重边的子节点
	int deep;     //深度
	int size;     //size域
	int top;      //本节点所在的重链的最顶层节点
	int nid;      //在dfs重链时重新对节点编号，确保同一条链上的节点相邻，是建立线段树的依据
    int weight;   //权值
}Node[SIZE];
int TIdx = 0;
int NewIdx[SIZE];

void dispArray(int const a[],int n){
	for(int i=0;i<=n;++i)printf("%d ",a[i]);
	printf("\n");
}
void dispNode(int i){
	printf("Node %d: w=%d\n",i,Node[i].weight);
}
void dispNodes(){
	for(int i=1;i<=N;++i)dispNode(i);
}

inline void init(){
	ECnt = TIdx = 1;
	fill(Vertex,Vertex+N+1,0);
	for(int i=0;i<=N;++i)Node[i].heavy_son=0;
}

//dfs找出所有重边，t为节点，parent为其父节点，deep为深度
//该dfs实际上确立了树的结构
void findHeavyEdge(int t,int parent,int deep){
	Node[t].deep = deep;
	Node[t].parent = parent;
	Node[t].size = 1;
	//对t的所有子节点
	for(int next=Vertex[t];next;next=Edge[next].next){
		int u = Edge[next].node;
		if ( u == parent ) continue;
		E2V[Edge[next].idx] = u;
		Node[u].weight = Edge[next].w;
		findHeavyEdge(u,t,deep+1);
		Node[t].size += Node[u].size;
		//判断重边
		if ( Node[u].size > Node[Node[t].heavy_son].size )
			Node[t].heavy_son = u;
	}
}

//dfs找出所有重链,t为节点，top为当前节点所在重链的最顶层节点
//重链实际上是以其顶层节点为标识保存的，任意节点都能够直接得出其所在重链的顶层节点
void findHeavyPath(int t,int top){
	Node[t].top = top;
	Node[t].nid = TIdx++;
	NewIdx[Node[t].nid] = t;

	//t没有重儿子，实际上就是叶节点
	if ( 0 == Node[t].heavy_son ) return;
	findHeavyPath(Node[t].heavy_son,top);

	//对t的所有节点
	for(int next=Vertex[t];next;next=Edge[next].next){
		int u = Edge[next].node;
		if ( u == Node[t].parent
			|| u == Node[t].heavy_son ) continue;

		findHeavyPath(u,u);
	}
}


llt ST[SIZE<<2];

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

void _pushUp(int t){ST[t]=(ST[lson(t)] + ST[rson(t)]);}

//建树,t表示线段树节点，[s,e]表示区间
void build(int t,int s,int e){
    if ( s == e ){
    	ST[t] = Node[NewIdx[s]].weight;
    	return;
    }

    int m = ( s + e ) >> 1;
    build(lson(t),s,m);
    build(rson(t),m+1,e);
    _pushUp(t);
}

//单点修改
void modify(int t,int s,int e,int idx,int newValue){
	if ( s == e ){
		ST[t] = newValue;
		return;
	}

	int m = ( s + e ) >> 1;
	if ( idx <= m ) modify(lson(t),s,m,idx,newValue);
	if ( m < idx ) modify(rson(t),m+1,e,idx,newValue);
	_pushUp(t);
}

//查询[a,b]区间极大值
llt query(int t,int s,int e,int a,int b){
	if ( a <= s && e <= b ) return ST[t];

	int m = ( s + e ) >> 1;
    llt r = 0;
    if ( a <= m ) r += query(lson(t),s,m,a,b);
    if ( m < b ) r += query(rson(t),m+1,e,a,b);
    return r;
}

//关键操作，将原树第idx条边的权值改为newValue
void change(int idx,int newValue){
    modify(1,1,N,Node[E2V[idx]].nid,newValue);
}

//关键操作，查询原树上x、y路径上的和
llt query(int x,int y){
	llt r = 0;
    //当x,y不处于同一条重链
	while( Node[x].top != Node[y].top ){
		//令x所处的重链总是更深
		if ( Node[Node[x].top].deep < Node[Node[y].top].deep )
			swap(x,y);
		//将x到其链顶的区间进行查询
		r = (r + query(1,1,N,Node[Node[x].top].nid,Node[x].nid));
		//将x修改为原链顶的父亲，实质上就是跳到了另外一条链
		x = Node[Node[x].top].parent;
	}
	//此时，x/y处于同一条链，令x总是更浅
	if ( Node[x].deep > Node[y].deep ) swap(x,y);
	//x、y之间的路径,x的权值应该不计算
	if ( x != y ) r = r + query(1,1,N,Node[x].nid+1,Node[y].nid);
	return r;
}

void read(){
    N = getInt();
    init();
    for(int i=1;i<N;++i){
    	int a = getInt();
		int b = getInt();
		int w = getInt();
    	mkEdge(a,b,w,i);
    }
    //以第1个节点为根建树
    findHeavyEdge(1,0,0);
    //从根节点递归建重链
    findHeavyPath(1,1);
    //以ST[1]为根节点建线段树
    build(1,1,N);
}

int Q;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    read();
	Q = getInt();
    for(int cmd,u,v,q=1;q<=Q;++q){
        cmd = getInt();
		u = getInt(); v = getInt();
		if(1 == cmd){
			change(u, v);
		}else{
			auto ans = query(u, v);
			printf("%lld\n", ans);
		}
	}
    return 0; 
}


