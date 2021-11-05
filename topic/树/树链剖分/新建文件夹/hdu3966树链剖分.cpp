//��Ȩ�������ѯ��·������
//#pragma comment(linker, "/STACK:1024000000,1024000000") 
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define SIZE 50010

struct edge_t{
	int node;//��һ���ڵ�ı��
	int next;//��һ���ߵĵ�ַ��ʵ�ʵ�ַΪEdge+next
}Edge[SIZE<<1];
int ECnt = 0;
int Vertex[SIZE];//�ڽӱ��ʾ���еı�

//a��b֮�佨�����������
void mkEdge(int a,int b){
	Edge[ECnt].node = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].node = a;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

struct node_t{
    int parent;   //���ڵ�
	int heavy_son;//�رߵ��ӽڵ�
	int depth;     //���
	int size;     //size��
	int top;      //���ڵ����ڵ����������ڵ�
	int nid;      //��dfs����ʱ���¶Խڵ��ţ�ȷ��ͬһ�����ϵĽڵ����ڣ��ǽ����߶���������
    int weight;   //Ȩֵ,�����м����������
}Node[SIZE];
int TIdx = 0;
int NewIdx[SIZE];
int N,M,P;

//dfs�ҳ������رߣ�tΪ�ڵ㣬parentΪ�丸�ڵ㣬depthΪ���
//��dfsʵ����ȷ�������Ľṹ
void dfsHeavyEdge(int t,int parent,int depth){
	Node[t].depth = depth;
	Node[t].parent = parent;
	Node[t].size = 1;
	//��t�������ӽڵ�
	for(int next=Vertex[t];next;next=Edge[next].next){
		int u = Edge[next].node;
		if ( u == parent ) continue;
		dfsHeavyEdge(u,t,depth+1);
		Node[t].size += Node[u].size;
		//�ж��ر�
		if ( Node[u].size > Node[Node[t].heavy_son].size )
			Node[t].heavy_son = u;
	}
}

//dfs�ҳ���������,tΪ�ڵ㣬topΪ��ǰ�ڵ��������������ڵ�
//����ʵ���������䶥��ڵ�Ϊ��ʶ����ģ�����ڵ㶼�ܹ�ֱ�ӵó������������Ķ���ڵ�
void dfsHeavyPath(int t,int top){
	Node[t].top = top;
	Node[t].nid = TIdx++;
	NewIdx[Node[t].nid] = t;

	//tû���ض��ӣ�ʵ���Ͼ���Ҷ�ڵ�
	if ( 0 == Node[t].heavy_son ) return;
	dfsHeavyPath(Node[t].heavy_son,top);

	//��t�����нڵ�
	for(int next=Vertex[t];next;next=Edge[next].next){
		int u = Edge[next].node;
		if ( u == Node[t].parent 
			|| u == Node[t].heavy_son ) continue;
		
		dfsHeavyPath(u,u);
	}
}

//���ӳٵ�������͵��߶���
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

//�������ݹ齨���ڵ�
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
//[a,b]��������delta
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
//�����ѯ
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

//�ؼ���������ԭ����(x,y)·�������нڵ�Ȩֵ����val
void change(int x,int y,int val){
	//��x,y������ͬһ������
	while( Node[x].top != Node[y].top ){
		//��x�������������Ǹ���
		if ( Node[Node[x].top].depth < Node[Node[y].top].depth )
			swap(x,y);
		//��x���ڵ�����������x����������޸�
		modify(1,1,N,Node[Node[x].top].nid,Node[x].nid,val);
		//��x�޸�Ϊԭ�����ĸ��ף�ʵ���Ͼ�������������һ����
		x = Node[Node[x].top].parent;
	}
	//���˴�ʱ��x��y����ͬһ��������x���Ǹ�ǳ���˾���Ϊ��ȷ����������
	if ( Node[x].depth > Node[y].depth ) swap(x,y);
	//��x��y֮���·������
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
	//�Ե�1���ڵ�Ϊ������
	dfsHeavyEdge(1,0,0);
	//�Ӹ��ڵ㿪ʼ�ݹ齨����
	dfsHeavyPath(1,1);
	//��ST[1]Ϊ���ڵ�����[1,N]���߶���
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
