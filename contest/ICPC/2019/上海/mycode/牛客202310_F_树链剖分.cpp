/**
    点权树操作
    1 u v w：路径uv设置为w
    2 u v w：路径uv增加w
    3 u v w：路径uv乘以w
    4 u v：路径uv的立方和
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
typedef llt value_t;

llt const MOD = 1000000007LL;
int const SIZE = 111100;

inline llt add(llt x,llt y){return (x+y)%MOD;}
inline llt add(llt x,llt y,llt z){return add(x, add(y, z));}
inline llt add(llt x,llt y,llt z,llt w){return add(x, add(y, z, w));}

inline llt mul(llt x,llt y){return (x*y)%MOD;}
inline llt mul(llt x,llt y,llt z){return mul(x, mul(y, z));}
inline llt mul(llt x,llt y,llt z,llt w){return mul(x, mul(y, z, w));}

inline void addAss(llt&x, llt y){x=add(x, y);}
inline void mulAss(llt&x, llt y){x=mul(x, y);}

/*************************************************************
*  以下为线段树, 线段树需要实现3种修改操作与4种查询操作
*  3种修改操作：设置、增加、倍乘
*  4种查询操作：最大值，和，平方和，立方和
**************************************************************/
inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

int N;//表示线段树的节点总数
llt StSum[SIZE<<2];//和
llt StSum2[SIZE<<2];//平方和
llt StSum3[SIZE<<2];//立方和

llt Lazy[3][SIZE<<2];//分别是延迟标记kbx
unsigned char SetFlag[SIZE<<2];//设置延迟标记

inline void _pushUp(int t){
    int ls = lson(t), rs = rson(t);
    StSum[t] = add(StSum[ls], StSum[rs]);
    StSum2[t] = add(StSum2[ls], StSum2[rs]);
    StSum3[t] = add(StSum3[ls], StSum3[rs]);
}

//对t节点求更新kb后的值, len表示节点数量
//本函数只求和，不管最值
void _f(int t, int len, llt k, llt b){
    llt k2 = mul(k, k);
    llt k3 = mul(k2, k);
    llt b2 = mul(b, b);
    llt b3 = mul(b2, b);
    //立方和
    StSum3[t] = add(mul(k3, StSum3[t]), mul(3, k2, b, StSum2[t]), mul(3, k, b2, StSum[t]), mul(len, b3));
    //平方和
    StSum2[t] = add(mul(k2, StSum2[t]), mul(2, k, b, StSum[t]), mul(len, b2));
    //和
    StSum[t] = add(mul(k, StSum[t]), mul(len, b));
}

void _pushDown(int t,int s,int e){
    llt &k = Lazy[0][t], &b = Lazy[1][t], &x = Lazy[2][t];
    unsigned char& flag = SetFlag[t];

    //如果没有设置延迟，也没有倍乘，也没有增加，则返回
    if(!flag && (1==k) && !b) return;

    int mid = ( s + e ) >> 1;
    int llen = ( mid - s + 1 ) % MOD;
    int rlen = ( e - mid ) % MOD;
    int ls = lson(t), rs = rson(t);

    if(flag){//处理设置延迟
        llt tmp = add(mul(k, x), b);
        //和
        StSum[ls] = mul(llen, tmp);
        StSum[rs] = mul(rlen, tmp);
        //平方和
        StSum2[ls] = mul(StSum[ls], tmp);
        StSum2[rs] = mul(StSum[rs], tmp);
        //立方和
        StSum3[ls] = mul(StSum2[ls], tmp);
        StSum3[rs] = mul(StSum2[rs], tmp);
        //子树的延迟标记
        Lazy[0][ls] = Lazy[0][rs] = k;
        Lazy[1][ls] = Lazy[1][rs] = b;
        Lazy[2][ls] = Lazy[2][rs] = x;
        SetFlag[ls] = SetFlag[rs] = 1;
    }else{
        //和值
        _f(ls,llen,k,b);
        _f(rs,rlen,k,b);
        //儿子的延迟标记
        Lazy[0][ls] = mul(Lazy[0][ls], k);
        Lazy[1][ls] = add(mul(Lazy[1][ls], k), b);
        Lazy[0][rs] = mul(Lazy[0][rs], k);
        Lazy[1][rs] = add(mul(Lazy[1][rs], k), b);
        //注意此处不能修改儿子的设置标记
    }

    k = 1; b = x = flag = 0;
}
//查询[a,b]区间的和，p为012分别表示和、平方和、立方和
llt querySum(int t,int s,int e,int a,int b,int p){
    if(a<=s&&e<=b){
        switch(p){
        case 0:return StSum[t];
        case 1:return StSum2[t];
        case 2:return StSum3[t];
        default:throw runtime_error("wrong p");
        }
    }

    _pushDown(t,s,e);
    int mid = ( s + e ) >> 1;
    llt ans = 0;
    if ( a <= mid ) addAss(ans, querySum(lson(t),s,mid,a,b,p));
    if ( mid < b ) addAss(ans, querySum(rson(t),mid+1,e,a,b,p));
    return ans;
}

//对[a,b]区间进行修改,op为1~3，分别表示增加、倍乘、设置
void modify(int t,int s,int e,int a,int b,int op,value_t para){
    if ( a <= s && e <= b ){
        int len = ( e - s + 1 ) % MOD;

        if ( 1 == op ){//+para
            _f(t,len,1,para);
            addAss(Lazy[1][t], para);
        }else if ( 2 == op ){//*para
            _f(t,len,para,0);
            mulAss(Lazy[0][t], para);
            mulAss(Lazy[1][t], para);
        }else{
            StSum[t] = mul(len, para);
            StSum2[t] = mul(StSum[t], para);
            StSum3[t] = mul(StSum2[t], para);
            SetFlag[t] = 1;
            Lazy[0][t] = 1;
            Lazy[1][t] = 0;
            Lazy[2][t] = para;
        }

        return;
    }

    _pushDown(t,s,e);
    int mid = ( s + e ) >> 1;
    if ( a <= mid ) modify(lson(t),s,mid,a,b,op,para);
    if ( mid < b ) modify(rson(t),mid+1,e,a,b,op,para);
    _pushUp(t);
}

/********************************************************
*  以下为树的边表结构
*******************************************************/
struct edge_t{
    int to;
    int next;
}Edge[SIZE<<1];
int Vertex[SIZE];
int ECnt;//

///a, b之间建一条边
inline void mkEdge(int a,int b){
    Edge[ECnt].to = b;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].to = a;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

/********************************************************
*  以下为树链剖分结构与操作
*******************************************************/

//树链的数据结构
struct node_t{
    int parent;
    int heavy_son;
    int depth;
    int size;
    int top;
    int nid;
    int mdes;//子树的最后一个节点
}Node[SIZE] = {{0,0,0,0,0,0}};
value_t Weight[SIZE];//权值
int NCnt;
int NewIdx[SIZE];
int Root = 1;//根，如果有子树操作需指定根，否则默认为1

///找重边
void dfsHeavyEdge(int node,int parent,int depth){
    Node[node].depth = depth;
    Node[node].parent = parent;
    Node[node].size = 1;

    for(int next=Vertex[node];next;next=Edge[next].next){
        int to = Edge[next].to;
        if ( to == parent ) continue;
        dfsHeavyEdge(to,node,depth+1);
        Node[node].size += Node[to].size;

        if ( Node[to].size > Node[Node[node].heavy_son].size ) Node[node].heavy_son = to;
    }
}
///找重链
void dfsHeavyPath(int node,int top){
    Node[node].top = top;
    Node[node].mdes = Node[node].nid = NCnt++;
    NewIdx[Node[node].nid] = node;

    if ( 0 == Node[node].heavy_son ) return;
    dfsHeavyPath(Node[node].heavy_son,top);
    Node[node].mdes = max(Node[node].mdes,Node[Node[node].heavy_son].mdes);

    for(int next=Vertex[node];next;next=Edge[next].next){
        int to = Edge[next].to;
        if ( to != Node[node].parent && to != Node[node].heavy_son ){
            dfsHeavyPath(to,to);
            Node[node].mdes = max(Node[node].mdes,Node[to].mdes);
        }
    }
}

//路径查询操作，从x到y的路径和,p取012分别表示和、平方和、立方和
llt queryPathSum(int x,int y,int p){
    llt ret = 0LL;
    while( Node[x].top != Node[y].top ){
        if ( Node[Node[x].top].depth < Node[Node[y].top].depth ) swap(x,y);

        addAss(ret, querySum(1,1,N,Node[Node[x].top].nid,Node[x].nid,p));
        x = Node[Node[x].top].parent;
    }

    if ( Node[x].depth > Node[y].depth ) swap(x,y);
    addAss(ret, querySum(1,1,N,Node[x].nid,Node[y].nid,p));
    return ret;
}

//路径修改，op取123分别是增加、倍乘、设置
void modifyPath(int x,int y,int op,value_t para){
    while( Node[x].top != Node[y].top ){
        if ( Node[Node[x].top].depth < Node[Node[y].top].depth ) swap(x,y);
        modify(1,1,N,Node[Node[x].top].nid,Node[x].nid,op,para);
        x = Node[Node[x].top].parent;
    }
    if ( Node[x].depth > Node[y].depth ) swap(x,y);
    modify(1,1,N,Node[x].nid,Node[y].nid,op,para);
}

/**********************************************
*  以下为初始化操作，重要!!!
***********************************************/

//此为线段树的初始操作，建完树链需要调用
void buildSeg(int t,int s,int e){
    SetFlag[t] = 0;
    Lazy[0][t] = 1; Lazy[1][t] = Lazy[2][t] = 0;
    if(s==e){
        //注意线段树的编号与原树编号是不一样的
        StSum[t] = Weight[NewIdx[s]];
        StSum2[t] = mul(StSum[t], StSum[t]);
        StSum3[t] = mul(StSum[t], StSum2[t]);
        return;
    }

    int m = (s+e)>>1;
    buildSeg(lson(t),s,m);
    buildSeg(rson(t),m+1,e);
    _pushUp(t);
}

//读入树的边表之前需要调用此函数
inline void initGraph(int n){
    ECnt = 1;
    fill(Vertex,Vertex+n+1,0);
}
//建树链，读完边表以后调用,如果是无根树，可以考虑首先求一个重心
inline void buildTreeChain(int root, int n){
    NCnt = 1;
    for(int i=1;i<=n;++i) Node[i].heavy_son = 0;

    dfsHeavyEdge(root,0,0);
    dfsHeavyPath(root,root);
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

void readAndInit(){
    initGraph(N = getInt());//初始化边表
    for(int i=1;i<N;++i)mkEdge(getInt(),getInt());//读入边，无向边可以这么毒
    for(int i=1;i<=N;++i)Weight[i]=getInt();//读入权值
    buildTreeChain(Root=1, N);//建树链
    buildSeg(1,1,N);//建线段树
}
int Q;
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        readAndInit();
        Q = getInt();
        printf("Case #%d:\n",kase);

        int cmd,u,v;
        llt w;
        for(int q=1;q<=Q;++q){
            switch(cmd=getInt()){
            case 1:{//路径设置
                u = getInt();
                v = getInt();
                modifyPath(u, v, 3, w=getInt());
            }break;
            case 2:{//路径增加
                u = getInt();
                v = getInt();
                modifyPath(u, v, 1, w=getInt());
            }break;
            case 3:{//路径倍乘
                u = getInt();
                v = getInt();
                modifyPath(u, v, 2, w=getInt());
            }break;
            case 4:{
                u = getInt();
                v = getInt();
                printf("%lld\n", queryPathSum(u, v, 2));
            }break;
            default:{
                printf("%d\n", cmd);
                throw runtime_error("wrong cmd");
            }

            }
        }
    }
    return 0;
}
