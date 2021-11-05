//点权，单点查询，路径更新
//#pragma comment(linker, "/STACK:1024000000,1024000000") 
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define SIZE 50010

struct edge_t{
	int node;//另一个节点的编号
	int next;//下一条边的地址，实际地址为Edge+next
}Edge[SIZE<<1];
int ECnt = 0;
int Vertex[SIZE];//邻接表表示所有的边

//a、b之间建立两条无向边
void mkEdge(int a,int b){
	Edge[ECnt].node = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].node = a;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

struct node_t{
    int parent;   //父节点
	int heavy_son;//重边的子节点
	int depth;     //深度
	int size;     //size域
	int top;      //本节点所在的重链的最顶层节点
	int nid;      //在dfs重链时重新对节点编号，确保同一条链上的节点相邻，是建立线段树的依据
    int weight;   //权值,本题中即所求的数量
}Node[SIZE];
int TIdx = 0;
int NewIdx[SIZE];
int N,M,P;

//dfs找出所有重边，t为节点，parent为其父节点，depth为深度
//该dfs实际上确立了树的结构
void dfsHeavyEdge(int t,int parent,int depth){
	Node[t].depth = depth;
	Node[t].parent = parent;
	Node[t].size = 1;
	//对t的所有子节点
	for(int next=Vertex[t];next;next=Edge[next].next){
		int u = Edge[next].node;
		if ( u == parent ) continue;
		dfsHeavyEdge(u,t,depth+1);
		Node[t].size += Node[u].size;
		//判断重边
		if ( Node[u].size > Node[Node[t].heavy_son].size )
			Node[t].heavy_son = u;
	}
}

//dfs找出所有重链,t为节点，top为当前节点所在重链的最顶层节点
//重链实际上是以其顶层节点为标识保存的，任意节点都能够直接得出其所在重链的顶层节点
void dfsHeavyPath(int t,int top){
	Node[t].top = top;
	Node[t].nid = TIdx++;
	NewIdx[Node[t].nid] = t;

	//t没有重儿子，实际上就是叶节点
	if ( 0 == Node[t].heavy_son ) return;
	dfsHeavyPath(Node[t].heavy_son,top);

	//对t的所有节点
	for(int next=Vertex[t];next;next=Edge[next].next){
		int u = Edge[next].node;
		if ( u == Node[t].parent 
			|| u == Node[t].heavy_son ) continue;
		
		dfsHeavyPath(u,u);
	}
}

//带延迟的求区间和的线段树
struct stnode_t{
	int peak;
	int delay;
}ST[SIZE<<2];

inline int lson(int t){return t<<1;}
inline int rson(int t){return (t<<1)|1;}

void _pushUp(int t){ST[t].peak=ST[lson(t)].peak+ST[rson(t)].peak;}
void _pushDown(int t){
	if ( 0 == ST[t].delay ) return;
	
	ST[lson(t)].delay += ST[t].delay;
	ST[lson(t)].peak += ST[t].delay;
	ST[rson(t)].delay += ST[t].delay;
	ST[rson(t)].peak += ST[t].delay;
	ST[t].delay = 0;
}

//建树，递归建立节点
void build(int t,int s,int e){
	ST[t].delay = 0;

	if ( s == e ){
		ST[t].peak = Node[NewIdx[s]].weight;
		return;
	}
	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
	_pushUp(t);
}
//[a,b]区间增加delta
void modify(int t,int s,int e,int a,int b,int delta){
	if ( a <= s && e <= b ){
		ST[t].delay += delta;
		ST[t].peak += delta;
		return;
	}

	_pushDown(t);
	int mid = ( s + e ) >> 1;
	if ( a <= mid ) modify(lson(t),s,mid,a,b,delta);
	if ( mid < b ) modify(rson(t),mid+1,e,a,b,delta);
	_pushUp(t);
}
//单点查询
int query(int t,int s,int e,int idx){
	if ( s == e ) return ST[t].peak;
	_pushDown(t);
	int mid = ( s + e ) >> 1;
	int ret = ( idx <= mid ) 
		? query(lson(t),s,mid,idx)
		: query(rson(t),mid+1,e,idx);
	_pushUp(t);
	return ret;
}

//关键操作，将原树上(x,y)路径的所有节点权值增加val
void change(int x,int y,int val){
	//当x,y不处于同一条重链
	while( Node[x].top != Node[y].top ){
		//令x所处的重链总是更深
		if ( Node[Node[x].top].depth < Node[Node[y].top].depth )
			swap(x,y);
		//将x所在的链的链顶到x的区间进行修改
		modify(1,1,N,Node[Node[x].top].nid,Node[x].nid,val);
		//将x修改为原链顶的父亲，实质上就是跳到了另外一条链
		x = Node[Node[x].top].parent;
	}
	//到此处时，x、y处于同一条链，令x总是更浅，此举是为了确定左右区间
	if ( Node[x].depth > Node[y].depth ) swap(x,y);
	//将x、y之间的路径更新
	modify(1,1,N,Node[x].nid,Node[y].nid,val);
}
inline void init(){
	ECnt = TIdx = 1;
	fill(Vertex,Vertex+N+1,0);
	for(int i=0;i<=N;++i)Node[i].heavy_son = 0;
}
bool read(){
	if ( EOF == scanf("%d%d%d",&N,&M,&P) )
		return false;

	init();
	for(int i=1;i<=N;++i)scanf("%d",&Node[i].weight);
	for(int i=0;i<M;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		mkEdge(a,b);
	}
	//以第1个节点为根建树
	dfsHeavyEdge(1,0,0);
	//从根节点开始递归建重链
	dfsHeavyPath(1,1);
	//以ST[1]为根节点区间[1,N]建线段树
	build(1,1,N);
	return true;
}
char Cmd[5];
int main(){
	while( read() ){
		while(P--){
			scanf("%s",Cmd);
			if ( 'Q' == *Cmd ){
				int x;
				scanf("%d",&x);
				printf("%d\n",query(1,1,N,Node[x].nid));
			}else{
				int x,y,v;
				scanf("%d%d%d",&x,&y,&v);
				if ( 'D' == *Cmd ) v = -v;
				change(x,y,v);
			}
		}
	}
	return 0;
}
