//�����ʷ�SPOJ375
//��Ȩ��������£�·����ѯ��ֵ
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

#define SIZE 10005

int N,M;

struct edge_t{
	int node;//��һ���ڵ�ı��
	int w;   //��Ȩ
	int idx; //�����
	int next;//��һ���ߵĵ�ַ��ʵ�ʵ�ַΪEdge+next
}Edge[SIZE<<1];
int ECnt = 0;
int Vertex[SIZE];//�ڽӱ��ʾ���еı�
int E2V[SIZE];//�ߵ����ӳ��

//a��b֮�佨�����������
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
    int parent;   //���ڵ�
	int heavy_son;//�رߵ��ӽڵ�
	int deep;     //���
	int size;     //size��
	int top;      //���ڵ����ڵ����������ڵ�
	int nid;      //��dfs����ʱ���¶Խڵ��ţ�ȷ��ͬһ�����ϵĽڵ����ڣ��ǽ����߶���������
    int weight;   //Ȩֵ
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

//dfs�ҳ������رߣ�tΪ�ڵ㣬parentΪ�丸�ڵ㣬deepΪ���
//��dfsʵ����ȷ�������Ľṹ
void findHeavyEdge(int t,int parent,int deep){
	Node[t].deep = deep;
	Node[t].parent = parent;
	Node[t].size = 1;
	//��t�������ӽڵ�
	for(int next=Vertex[t];next;next=Edge[next].next){
		int u = Edge[next].node;
		if ( u == parent ) continue;
		E2V[Edge[next].idx] = u;
		Node[u].weight = Edge[next].w;
		findHeavyEdge(u,t,deep+1);
		Node[t].size += Node[u].size;
		//�ж��ر�
		if ( Node[u].size > Node[Node[t].heavy_son].size )
			Node[t].heavy_son = u;
	}
}

//dfs�ҳ���������,tΪ�ڵ㣬topΪ��ǰ�ڵ��������������ڵ�
//����ʵ���������䶥��ڵ�Ϊ��ʶ����ģ�����ڵ㶼�ܹ�ֱ�ӵó������������Ķ���ڵ�
void findHeavyPath(int t,int top){
	Node[t].top = top;
	Node[t].nid = TIdx++;
	NewIdx[Node[t].nid] = t;

	//tû���ض��ӣ�ʵ���Ͼ���Ҷ�ڵ�
	if ( 0 == Node[t].heavy_son ) return;
	findHeavyPath(Node[t].heavy_son,top);

	//��t�����нڵ�
	for(int next=Vertex[t];next;next=Edge[next].next){
		int u = Edge[next].node;
		if ( u == Node[t].parent
			|| u == Node[t].heavy_son ) continue;

		findHeavyPath(u,u);
	}
}


int ST[SIZE<<2];

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

void _pushUp(int t){ST[t]=max(ST[lson(t)],ST[rson(t)]);}

//����,t��ʾ�߶����ڵ㣬[s,e]��ʾ����
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

//�����޸�
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

//��ѯ[a,b]���伫��ֵ
int query(int t,int s,int e,int a,int b){
	if ( a <= s && e <= b ) return ST[t];

	int m = ( s + e ) >> 1;
    int r = INT_MIN;
    if ( a <= m ) r = max(r,query(lson(t),s,m,a,b));
    if ( m < b ) r = max(r,query(rson(t),m+1,e,a,b));
    return r;
}

//�ؼ���������ԭ����idx���ߵ�Ȩֵ��ΪnewValue
void change(int idx,int newValue){
    modify(1,1,N,Node[E2V[idx]].nid,newValue);
}

//�ؼ���������ѯԭ����x��y·���ϵĺ�
int query(int x,int y){
	int r = INT_MIN;
    //��x,y������ͬһ������
	while( Node[x].top != Node[y].top ){
		//��x�������������Ǹ���
		if ( Node[Node[x].top].deep < Node[Node[y].top].deep )
			swap(x,y);
		//��x����������������в�ѯ
		r = max(r,query(1,1,N,Node[Node[x].top].nid,Node[x].nid));
		//��x�޸�Ϊԭ�����ĸ��ף�ʵ���Ͼ�������������һ����
		x = Node[Node[x].top].parent;
	}
	//��ʱ��x/y����ͬһ��������x���Ǹ�ǳ
	if ( Node[x].deep > Node[y].deep ) swap(x,y);
	//x��y֮���·��,x��ȨֵӦ�ò�����
	if ( x != y ) r = max(r,query(1,1,N,Node[x].nid+1,Node[y].nid));
	return r;
}

void read(){
    scanf("%d",&N);
    init();
    for(int i=1;i<N;++i){
    	int a,b,w;
    	scanf("%d%d%d",&a,&b,&w);
    	mkEdge(a,b,w,i);
    }
    //�Ե�1���ڵ�Ϊ������
    findHeavyEdge(1,0,0);
    //�Ӹ��ڵ�ݹ齨����
    findHeavyPath(1,1);
    //��ST[1]Ϊ���ڵ㽨�߶���
    build(1,1,N);
}

char Cmd[10];
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	for(int kase=0;kase<nofkase;++kase){
		read();
		if ( kase ) printf("\n");

		while( scanf("%s",Cmd) && 'D' != *Cmd ){
			int a,b;
			scanf("%d%d",&a,&b);

			if ( 'Q' == *Cmd ){
                printf("%d\n",query(a,b));
			}else{
                change(a,b);
			}
		}
	}
	return 0;
}
