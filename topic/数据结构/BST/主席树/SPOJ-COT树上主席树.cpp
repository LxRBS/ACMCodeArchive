/*
    树上路径查询第k大
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

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
}Lca;

int const SIZE = 100003;
struct node_t{
    int left; //左儿子
    int right;//右儿子
    int cnt;  //当前节点对应区间内不同数的个数
}Node[SIZE*50];
int toUsed = 0;
int Root[SIZE];//根节点

inline int _newNode(){
    Node[toUsed].left = Node[toUsed].right = Node[toUsed].cnt = 0;
    return toUsed++;
}

//t为本节点的指针,[s,e]为区间
//建树的时候cnt全为0
void _build(int&t,int s,int e){
    t = _newNode();
    if ( s == e ) return;

    int mid = ( s + e ) >> 1;
    _build(Node[t].left,s,mid);
    _build(Node[t].right,mid+1,e);
}

inline void build(int&t,int s,int e){
    toUsed = 0;
    _newNode();
    _build(t,s,e);
}

void modify(int old,int&t,int s,int e,int pos,int delta){
    Node[t=_newNode()] = Node[old];
    Node[t].cnt += delta;
    if ( s == e ) return;

    int mid = ( s + e ) >> 1;
    if ( pos <= mid ) modify(Node[old].left,Node[t].left,s,mid,pos,delta);
    else modify(Node[old].right,Node[t].right,mid+1,e,pos,delta);
}

//u和v为节点，lca为uv的lca，fa为lca的父节点
//表示4棵线段树的运算
int query(int u,int v,int lca,int fa,int s,int e,int k){
    if ( s == e ) return s;

    int x = Node[Node[u].left].cnt + Node[Node[v].left].cnt - Node[Node[lca].left].cnt - Node[Node[fa].left].cnt;
    int mid = ( s + e ) >> 1;
    return x >= k ? query(Node[u].left,Node[v].left,Node[lca].left,Node[fa].left,s,mid,k) : query(Node[u].right,Node[v].right,Node[lca].right,Node[fa].right,mid+1,e,k-x);
}

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

//just as its names
int const SIZE_OF_VERTICES = SIZE;
int const SIZE_OF_EDGES = SIZE<<1;

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
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int N,M,NN;
int A[SIZE],B[SIZE];

//用于Tarjan算法求LCA
struct ufs_t{
    enum{UF_SIZE=SIZE};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

bool Flag[SIZE];
struct question_t{
    int s,e,k;
}Q[SIZE];
vector<vector<int> > Questions;
int Father[SIZE];

//顺便做一个Tarjan算法
void dfs(int t,int p){
    Father[t] = p;
    int pos = lower_bound(B+1,B+NN+1,A[t]) - B;
    modify(Root[p],Root[t],1,NN,pos,1);

    UF.father[t] = t;
    Flag[t] = true;

    int v;
    for(int next=Vertex[t];next;next=Edge[next].next)if((v=Edge[next].to)!=p){
        dfs(v,t);
        UF.father[v] = t;
    }

    //对每一个根t有关的问题
    vector<int>&vec = Questions[t];
    for(vector<int>::iterator it=vec.begin();it!=vec.end();++it){
        if( Flag[v=*it] ){
            int r = UF.find(v);
            int a = t, b = v;
            if (a>b)swap(a,b);
            Lca.insert(Hash::key_t(a,b),r);
        }
    }
}

bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;
    for(int i=1;i<=N;++i) A[i]=B[i]=getInt();

    fill(Flag,Flag+N+1,false);
    Questions.assign(N+1,vector<int>());
    Lca.clear();
    initGraph(N);
    for(int i=1;i<N;++i){
        mkEdge(getInt(),getInt());//反正是双向边
    }

    //读入问题
    for(int i=0;i<M;++i){
        Q[i].s = getInt();Q[i].e = getInt();Q[i].k = getInt();
        if(Q[i].s>Q[i].e)swap(Q[i].s,Q[i].e);
        Questions[Q[i].s].push_back(Q[i].e);
        Questions[Q[i].e].push_back(Q[i].s);
    }

    //离散化
    sort(B+1,B+N+1);
    NN = unique(B+1,B+N+1) - B - 1;

    //建树
    build(Root[0],1,NN);

    //对树上的每个节点依次更新
    dfs(1,0);

    return true;
}

int main(){
    int a,b,lca;
    while( read() )for(int q=0;q<M;++q){
        lca = Lca.find(Hash::key_t(a=Q[q].s,b=Q[q].e));
        printf("%d\n",B[query(Root[a],Root[b],Root[lca],Root[Father[lca]],1,NN,Q[q].k)]);
    }
    return 0;
}
