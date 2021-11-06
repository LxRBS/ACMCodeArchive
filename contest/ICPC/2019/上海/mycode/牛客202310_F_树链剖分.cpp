/**
    ��Ȩ������
    1 u v w��·��uv����Ϊw
    2 u v w��·��uv����w
    3 u v w��·��uv����w
    4 u v��·��uv��������
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
*  ����Ϊ�߶���, �߶�����Ҫʵ��3���޸Ĳ�����4�ֲ�ѯ����
*  3���޸Ĳ��������á����ӡ�����
*  4�ֲ�ѯ���������ֵ���ͣ�ƽ���ͣ�������
**************************************************************/
inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

int N;//��ʾ�߶����Ľڵ�����
llt StSum[SIZE<<2];//��
llt StSum2[SIZE<<2];//ƽ����
llt StSum3[SIZE<<2];//������

llt Lazy[3][SIZE<<2];//�ֱ����ӳٱ��kbx
unsigned char SetFlag[SIZE<<2];//�����ӳٱ��

inline void _pushUp(int t){
    int ls = lson(t), rs = rson(t);
    StSum[t] = add(StSum[ls], StSum[rs]);
    StSum2[t] = add(StSum2[ls], StSum2[rs]);
    StSum3[t] = add(StSum3[ls], StSum3[rs]);
}

//��t�ڵ������kb���ֵ, len��ʾ�ڵ�����
//������ֻ��ͣ�������ֵ
void _f(int t, int len, llt k, llt b){
    llt k2 = mul(k, k);
    llt k3 = mul(k2, k);
    llt b2 = mul(b, b);
    llt b3 = mul(b2, b);
    //������
    StSum3[t] = add(mul(k3, StSum3[t]), mul(3, k2, b, StSum2[t]), mul(3, k, b2, StSum[t]), mul(len, b3));
    //ƽ����
    StSum2[t] = add(mul(k2, StSum2[t]), mul(2, k, b, StSum[t]), mul(len, b2));
    //��
    StSum[t] = add(mul(k, StSum[t]), mul(len, b));
}

void _pushDown(int t,int s,int e){
    llt &k = Lazy[0][t], &b = Lazy[1][t], &x = Lazy[2][t];
    unsigned char& flag = SetFlag[t];

    //���û�������ӳ٣�Ҳû�б��ˣ�Ҳû�����ӣ��򷵻�
    if(!flag && (1==k) && !b) return;

    int mid = ( s + e ) >> 1;
    int llen = ( mid - s + 1 ) % MOD;
    int rlen = ( e - mid ) % MOD;
    int ls = lson(t), rs = rson(t);

    if(flag){//���������ӳ�
        llt tmp = add(mul(k, x), b);
        //��
        StSum[ls] = mul(llen, tmp);
        StSum[rs] = mul(rlen, tmp);
        //ƽ����
        StSum2[ls] = mul(StSum[ls], tmp);
        StSum2[rs] = mul(StSum[rs], tmp);
        //������
        StSum3[ls] = mul(StSum2[ls], tmp);
        StSum3[rs] = mul(StSum2[rs], tmp);
        //�������ӳٱ��
        Lazy[0][ls] = Lazy[0][rs] = k;
        Lazy[1][ls] = Lazy[1][rs] = b;
        Lazy[2][ls] = Lazy[2][rs] = x;
        SetFlag[ls] = SetFlag[rs] = 1;
    }else{
        //��ֵ
        _f(ls,llen,k,b);
        _f(rs,rlen,k,b);
        //���ӵ��ӳٱ��
        Lazy[0][ls] = mul(Lazy[0][ls], k);
        Lazy[1][ls] = add(mul(Lazy[1][ls], k), b);
        Lazy[0][rs] = mul(Lazy[0][rs], k);
        Lazy[1][rs] = add(mul(Lazy[1][rs], k), b);
        //ע��˴������޸Ķ��ӵ����ñ��
    }

    k = 1; b = x = flag = 0;
}
//��ѯ[a,b]����ĺͣ�pΪ012�ֱ��ʾ�͡�ƽ���͡�������
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

//��[a,b]��������޸�,opΪ1~3���ֱ��ʾ���ӡ����ˡ�����
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
*  ����Ϊ���ı߱�ṹ
*******************************************************/
struct edge_t{
    int to;
    int next;
}Edge[SIZE<<1];
int Vertex[SIZE];
int ECnt;//

///a, b֮�佨һ����
inline void mkEdge(int a,int b){
    Edge[ECnt].to = b;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].to = a;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

/********************************************************
*  ����Ϊ�����ʷֽṹ�����
*******************************************************/

//���������ݽṹ
struct node_t{
    int parent;
    int heavy_son;
    int depth;
    int size;
    int top;
    int nid;
    int mdes;//���������һ���ڵ�
}Node[SIZE] = {{0,0,0,0,0,0}};
value_t Weight[SIZE];//Ȩֵ
int NCnt;
int NewIdx[SIZE];
int Root = 1;//�������������������ָ����������Ĭ��Ϊ1

///���ر�
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
///������
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

//·����ѯ��������x��y��·����,pȡ012�ֱ��ʾ�͡�ƽ���͡�������
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

//·���޸ģ�opȡ123�ֱ������ӡ����ˡ�����
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
*  ����Ϊ��ʼ����������Ҫ!!!
***********************************************/

//��Ϊ�߶����ĳ�ʼ����������������Ҫ����
void buildSeg(int t,int s,int e){
    SetFlag[t] = 0;
    Lazy[0][t] = 1; Lazy[1][t] = Lazy[2][t] = 0;
    if(s==e){
        //ע���߶����ı����ԭ������ǲ�һ����
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

//�������ı߱�֮ǰ��Ҫ���ô˺���
inline void initGraph(int n){
    ECnt = 1;
    fill(Vertex,Vertex+n+1,0);
}
//������������߱��Ժ����,������޸��������Կ���������һ������
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
    initGraph(N = getInt());//��ʼ���߱�
    for(int i=1;i<N;++i)mkEdge(getInt(),getInt());//����ߣ�����߿�����ô��
    for(int i=1;i<=N;++i)Weight[i]=getInt();//����Ȩֵ
    buildTreeChain(Root=1, N);//������
    buildSeg(1,1,N);//���߶���
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
            case 1:{//·������
                u = getInt();
                v = getInt();
                modifyPath(u, v, 3, w=getInt());
            }break;
            case 2:{//·������
                u = getInt();
                v = getInt();
                modifyPath(u, v, 1, w=getInt());
            }break;
            case 3:{//·������
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
