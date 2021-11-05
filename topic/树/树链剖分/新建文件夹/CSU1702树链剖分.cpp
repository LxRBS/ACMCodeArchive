//��Ȩ��������£�·����ѯ��
#include <cstdio>
#include <algorithm>
using namespace std;

int const SIZE = 500005;
int const MOD = 1000000007;
int N;

//������
void dispNode(int);
void dispTree(int);
void dispEdge(int);
void dispST(int,int,int);
/////////////////////////////////

//�߽ṹ
struct edge_t{
    int node;//���ӽڵ�ı�ţ���Ч��ΧΪ1~N
    int next;//��һ���ߵĵ�ַ��ʵ�ʵ�ַΪEdge+next
}Edge[SIZE];
int ECnt = 0;
int Vertex[SIZE];//�����¼ÿ���ڵ�Ķ���

//a��b����һ���ߣ���ֵС���Ǹ��ڵ�
void mkEdge(int a,int b){
    if ( a > b ) swap(a,b);

    Edge[ECnt].node = b;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt ++;
}

struct node_t{
    int parent;   //���ڵ�
	int heavy_son;//�رߵ��ӽڵ�
	int depth;     //���
	int size;     //size��
	int top;      //���ڵ����ڵ����������ڵ�
	int nid;      //��dfs����ʱ���¶Խڵ��ţ�ȷ��ͬһ�����ϵĽڵ����ڣ��ǽ����߶���������
    int weight;   //Ȩֵ
}Node[SIZE];
int TIdx = 0;
int NewIdx[SIZE];//�±�ŵ��ϱ�ŵ�ӳ��

//���ر�
void findHeavyEdge(int t,int parent,int depth){
    Node[t].depth = depth;
    Node[t].parent = parent;
    Node[t].size = 1;
    //��t�������ӽڵ�
    for(int next=Vertex[t];next;next=Edge[next].next){
        int u = Edge[next].node;
        findHeavyEdge(u,t,depth+1);
        Node[t].size += Node[u].size;
        //find heavy edge
        if (Node[u].size > Node[Node[t].heavy_son].size){
            Node[t].heavy_son = u;
        }
    }
}

//������
void findHeavyPath(int t,int top){
    Node[t].top = top;
    Node[t].nid = TIdx ++;
    NewIdx[Node[t].nid] = t;

    if ( 0 == Node[t].heavy_son ) return;
    findHeavyPath(Node[t].heavy_son,top);

    for(int next=Vertex[t];next;next=Edge[next].next){
        int u = Edge[next].node;
        if ( u == Node[t].heavy_son ) continue;
        findHeavyPath(u,u);
    }
}

//��������߶���
int ST[SIZE<<2];

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

void _pushUp(int t){
    ST[t] = ( ST[lson(t)] + ST[rson(t)] ) % MOD;
}

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

//�������
void modify(int t,int s,int e,int idx,int delta){
    if ( s == e ){
        ST[t] += delta;
        ST[t] %= MOD;
        return;
    }

    int m = ( s + e ) >> 1;
    if (idx <= m) modify(lson(t),s,m,idx,delta);
    else modify(rson(t),m+1,e,idx,delta);
    _pushUp(t);
}

int query(int t,int s,int e,int a,int b){
    if (a <= s && e <= b){
        return ST[t];
    }
    int m = ( s + e ) >> 1;

    int r = 0;
    if (a <= m){
        r += query(lson(t),s,m,a,b);
        r %= MOD;
    }
    if (m < b){
        r += query(rson(t),m+1,e,a,b);
        r %= MOD;
    }
    return r;
}

//���ϲ���
inline void change(int x,int delta){
    modify(1,1,N,Node[x].nid,delta);
}

//���ϲ���
int query(int x,int y){
    int r = 0;
    while(Node[x].top != Node[y].top){
        if (Node[Node[x].top].depth < Node[Node[y].top].depth){
            swap(x,y);
        }

        r += query(1,1,N,Node[Node[x].top].nid,Node[x].nid);
        r %= MOD;

        x = Node[Node[x].top].parent;
    }

    if (Node[x].depth > Node[y].depth) swap(x,y);

    r += query(1,1,N,Node[x].nid,Node[y].nid);
    return r %= MOD;
}

void init(){
    ECnt = TIdx = 1;
    fill(Vertex,Vertex+N+1,0);
    for(int i=0;i<=N;++i)Node[i].heavy_son = 0;
}

bool read(){
    if (EOF == scanf("%d",&N)) return false;

    init();
    for(int i=0;i<N-1;++i){
        int a,b;
        scanf("%d%d",&a,&b);
        mkEdge(a+1,b+1);
    }

    for(int i=1;i<=N;++i){
        scanf("%d",&Node[i].weight);
    }

    findHeavyEdge(1,0,0);
    findHeavyPath(1,1);
    build(1,1,N);

    return true;
}

void proc(){
    int q;
    scanf("%d",&q);
    while(q--){
        int k,x,y,a,b,c,d,u,v;
        scanf("%d%d%d%d%d%d%d%d%d",&k,&x,&y,&a,&b,&c,&d,&u,&v);
        change(x+1,y);

        while(--k){
            x = ( a * x + b ) % N;
            y = ( c * y + d ) % MOD;
            change(x+1,y);
        }

        printf("%d\n",query(u+1,v+1));
    }
}

int main()
{
    while(read()) proc();
    return 0;
}

void dispNode(int u){
    node_t const& t = Node[u];
    printf("(Node %d)(parent %d)(depth %d)(top %d)(weight %d)(nid %d)\n",u,t.parent,t.depth,t.top,t.weight,t.nid);
    printf("    son:");
    for(int next=Vertex[u];next;next=Edge[next].next){
        printf(" %d",Edge[next].node);
    }
    printf("\n");
}

void dispTree(int root){
    dispNode(root);
    for(int next=Vertex[root];next;next=Edge[next].next){
        dispTree(Edge[next].node);
    }
}

void dispEdge(int node){
    printf("(Node %d)",node);
    for(int next=Vertex[node];next;next=Edge[next].next){
        printf(" %d",Edge[next].node);
    }
    printf("\n");
}

void dispST(int t,int s,int e){
    printf("(Node %d)[%d %d]{%d}\n",t,s,e,ST[t]);
    if (s == e) return;
    int m = ( s + e ) >> 1;
    dispST(lson(t),s,m);
    dispST(rson(t),m+1,e);
}
