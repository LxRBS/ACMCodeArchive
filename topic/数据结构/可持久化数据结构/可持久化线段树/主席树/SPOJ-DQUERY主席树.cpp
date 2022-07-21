/*
    给定数组A，问[a,b]区间内不同元素的数量
    标准的莫队算法，也可用主席树
    对每一个区间[1,i]建立一个线段树，为第i个线段树
    如果元素Ai在之前的某个位置j出现过，则将Aj删除，然后在将Ai插入
    查询时，只需要看第b棵线段树在位置[a,n]之间的数量即可
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE = 30103;
struct node_t{
    int left; //左儿子
    int right;//右儿子
    int cnt;  //当前节点对应区间内不同数的个数
}Node[SIZE*20];
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

//某棵线段树上[a,b]区间值
int query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ) return Node[t].cnt;

    int mid = ( s + e ) >> 1;
    int ans = 0;
    if ( a <= mid ) ans += query(Node[t].left,s,mid,a,b);
    if ( mid < b ) ans += query(Node[t].right,mid+1,e,a,b);
    return ans;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,M,NN;
int A[SIZE],B[SIZE];
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;
    for(int i=1;i<=N;++i) A[i] = B[i] = getUnsigned();

    //离散化
    sort(B+1,B+N+1);
    NN = unique(B+1,B+N+1) - B - 1;

    //建树
    build(Root[0],1,N);
    return true;
}

int LastPos[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    int a,b,v,t;
    while( read() ){
        fill(LastPos,LastPos+NN+1,0);

        //对源数组的每个数依次更新
        for(int i=1;i<=N;++i){
            v = lower_bound(B+1,B+NN+1,A[i]) - B;

            if ( LastPos[v] ){//需要一棵临时的新树
                modify(Root[i-1],t,1,N,LastPos[v],-1);
                modify(t,Root[i],1,N,i,1);
            }else{
                modify(Root[i-1],Root[i],1,N,i,1);
            }

            LastPos[v] = i;
        }

        //查询
        M = getUnsigned();
        for(int i=0;i<M;++i){
            a = getUnsigned();b = getUnsigned();
            printf("%d\n",query(Root[b],1,N,a,N));
        }
    }
    return 0;
}
