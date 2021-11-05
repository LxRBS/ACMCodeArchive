#pragma comment(linker, "/STACK:1024000000,1024000000") 
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
	int deep;     //���
	int size;     //size��
	int top;      //���ڵ����ڵ����������ڵ�
	int nid;      //��dfs����ʱ���¶Խڵ��ţ�ȷ��ͬһ�����ϵĽڵ����ڣ��ǽ����߶���������
    int weight;   //Ȩֵ,�����м����������
}Node[SIZE];
int TIdx = 0;
int NewIdx[SIZE];
int N,M,P;

int Tmp[SIZE];
//Ԥ�������رߣ���������ȷ���±�ţ�BFSʵ��
//rootΪϣ�������Ľڵ���
void preproc(int root){
	//����ȷ�����Ľṹ��Ҳ���Ǹ��ӽṹ
	Node[root].parent = 0;
	Node[root].deep = 0;

	//ʹ��Tmpģ��һ������
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

	//ȷ��ÿ���ڵ��size
	for(int i=tail-1;i>=0;--i){
		int u = Tmp[i];
		Node[u].size += 1;
		int p = Node[u].parent;
		if ( p ) Node[p].size += Node[u].size;

		//ȷ���ض���
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

	//ȷ��������ʹ��ջ
	Node[root].top = root;
	Node[root].nid = TIdx;
	NewIdx[TIdx++] = root;
	head = 0;	
	Tmp[head++] = root;
	while( head ){
		int u = Tmp[head--];
		if ( 0 == Node[u].top ) Node[u].top = u;
		if ( 0 == Node[u].heavy_son ) continue;
		//������������ջ
		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].node;
			if ( v == Node[u].parent || v == Node[u].heavy_son ) continue;
			Tmp[head++] = v;
		}
		//���ѹ�ض���
		Node[Node[u].heavy_son].top = Node[u].top;
		Tmp[head++] = Node[u].heavy_son;
	}
}

//���ӳٵ�������͵��߶���
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

//�������ݹ齨���ڵ�
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
//[a,b]��������c
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
//�����ѯ
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

//�ؼ���������ԭ����(x,y)·�������нڵ�Ȩֵ����val
void change(int x,int y,int val){
	//��x,y������ͬһ������
	while( Node[x].top != Node[y].top ){
		//��x�������������Ǹ���
		if ( Node[Node[x].top].deep < Node[Node[y].top].deep )
			swap(x,y);
		//��x���ڵ�����������x����������޸�
		update(1,1,N,Node[Node[x].top].nid,Node[x].nid,val);
		//��x�޸�Ϊԭ�����ĸ��ף�ʵ���Ͼ�������������һ����
		x = Node[Node[x].top].parent;
	}
	//���˴�ʱ��x��y����ͬһ��������x���Ǹ�ǳ���˾���Ϊ��ȷ����������
	if ( Node[x].deep > Node[y].deep ) swap(x,y);
	//��x��y֮���·������
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
    //Ԥ����
	preproc(1);
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