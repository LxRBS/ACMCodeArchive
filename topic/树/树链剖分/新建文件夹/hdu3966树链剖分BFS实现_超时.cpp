#pragma comment(linker, "/STACK:1024000000,1024000000") 
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
	int deep;     //深度
	int size;     //size域
	int top;      //本节点所在的重链的最顶层节点
	int nid;      //在dfs重链时重新对节点编号，确保同一条链上的节点相邻，是建立线段树的依据
    int weight;   //权值,本题中即所求的数量
}Node[SIZE];
int TIdx = 0;
int NewIdx[SIZE];
int N,M,P;

int Tmp[SIZE];
//预处理，找重边，找重链，确定新编号，BFS实现
//root为希望做根的节点编号
void preproc(int root){
	//首先确定树的结构，也就是父子结构
	Node[root].parent = 0;
	Node[root].deep = 0;

	//使用Tmp模拟一个队列
	int head = 0, tail = 0;
	Tmp[tail++] = root;
	while( head != tail ){
		int u = Tmp[head++];
		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].node;
			if ( v == Node[u].parent ) continue;
			Node[v].deep = Node[u].deep + 1;
			Node[v].parent = u;
			Tmp[tail++] = v;
		}
	}

	//确定每个节点的size
	for(int i=tail-1;i>=0;--i){
		int u = Tmp[i];
		Node[u].size += 1;
		int p = Node[u].parent;
		if ( p ) Node[p].size += Node[u].size;

		//确定重儿子
		if ( 0 == Vertex[u] ){
			Node[u].heavy_son = 0;
			continue;
		}

		int ts = -1;
		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].node;
			if ( Node[v].size > ts ) 
				Node[u].heavy_son = v, ts = Node[v].size;
		}
	}

	//确定重链，使用栈
	Node[root].top = root;
	Node[root].nid = TIdx;
	NewIdx[TIdx++] = root;
	head = 0;	
	Tmp[head++] = root;
	while( head ){
		int u = Tmp[head--];
		if ( 0 == Node[u].top ) Node[u].top = u;
		if ( 0 == Node[u].heavy_son ) continue;
		//将其他儿子入栈
		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].node;
			if ( v == Node[u].parent || v == Node[u].heavy_son ) continue;
			Tmp[head++] = v;
		}
		//最后压重儿子
		Node[Node[u].heavy_son].top = Node[u].top;
		Tmp[head++] = Node[u].heavy_son;
	}
}

//带延迟的求区间和的线段树
struct stnode_t{
	int sum;
	int delay;
}ST[SIZE<<2];

inline int lson(int t){return t<<1;}
inline int rson(int t){return (t<<1)|1;}

void calDad(int t){ST[t].sum=ST[lson(t)].sum+ST[rson(t)].sum;}
void delayUpdate(int t,int s,int e){
	if ( 0 == ST[t].delay ) return;
	
	ST[lson(t)].delay += ST[t].delay;
	ST[rson(t)].delay += ST[t].delay;
	int mid = ( s + e ) >> 1;
	ST[lson(t)].sum += ST[t].delay * ( mid - s + 1);
	ST[rson(t)].sum += ST[t].delay * ( e - mid );
	ST[t].delay = 0;
}

//建树，递归建立节点
void build(int t,int s,int e){
	ST[t].delay = 0;

	if ( s == e ){
		ST[t].sum = Node[NewIdx[s]].weight;
		return;
	}
	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
	calDad(t);
}
//[a,b]区间增加c
void update(int t,int s,int e,int a,int b,int c){
	if ( a <= s && e <= b ){
		ST[t].delay += c;
		ST[t].sum += c * ( e - s + 1 );
		return;
	}

	delayUpdate(t,s,e);
	int mid = ( s + e ) >> 1;
	if ( a <= mid ) update(lson(t),s,mid,a,b,c);
	if ( mid < b ) update(rson(t),mid+1,e,a,b,c);
	calDad(t);
}
//单点查询
int query(int t,int s,int e,int sn){
	if ( s == e ) return ST[t].sum;
	delayUpdate(t,s,e);
	int mid = ( s + e ) >> 1;
	int ret = ( sn <= mid ) 
		? query(lson(t),s,mid,sn)
		: query(rson(t),mid+1,e,sn);
	calDad(t);
	return ret;
}

//关键操作，将原树上(x,y)路径的所有节点权值增加val
void change(int x,int y,int val){
	//当x,y不处于同一条重链
	while( Node[x].top != Node[y].top ){
		//令x所处的重链总是更深
		if ( Node[Node[x].top].deep < Node[Node[y].top].deep )
			swap(x,y);
		//将x所在的链的链顶到x的区间进行修改
		update(1,1,N,Node[Node[x].top].nid,Node[x].nid,val);
		//将x修改为原链顶的父亲，实质上就是跳到了另外一条链
		x = Node[Node[x].top].parent;
	}
	//到此处时，x、y处于同一条链，令x总是更浅，此举是为了确定左右区间
	if ( Node[x].deep > Node[y].deep ) swap(x,y);
	//将x、y之间的路径更新
	update(1,1,N,Node[x].nid,Node[y].nid,val);
}
inline void init(){
	ECnt = TIdx = 1;
	fill(Vertex,Vertex+N+1,0);
	for(int i=0;i<=N;++i)Node[i].size = Node[i].top = 0;
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
    //预处理
	preproc(1);
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