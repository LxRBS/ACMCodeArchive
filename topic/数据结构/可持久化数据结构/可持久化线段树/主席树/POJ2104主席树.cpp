/*
    主席树
    静态区间第k大问题
    对源数组的每个区间[1,x]，x=1,2,...,n
    建立n个线段树，线段树记录[s,e]区间内一共有多少个不同的数
    用第b个线段树减去第a-1个线段树，就能得到源数组[a,b]区间内一共有多少个数
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE = 100003;
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

//t1为t1时刻的线段树，t2为t2时刻的线段树，t2>t1
//k为要查询的第k大，从1开始
int query(int t1,int t2,int s,int e,int k){
    if ( s == e ) return s;

    int x = Node[Node[t2].left].cnt - Node[Node[t1].left].cnt;
    int mid = ( s + e ) >> 1;
    return x >= k ? query(Node[t1].left,Node[t2].left,s,mid,k) : query(Node[t1].right,Node[t2].right,mid+1,e,k-x);
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

int N,M;
int A[SIZE],B[SIZE];
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;
    for(int i=1;i<=N;++i) A[i] = B[i] = getInt();
    return true;
}

int main(){
    int a,b;
    while( read() ){
        //离散化
        sort(B+1,B+N+1);
        int n = unique(B+1,B+N+1) - B - 1;

        //建树
        build(Root[0],1,n);

        //对源数组的每个数依次更新
        for(int i=1;i<=N;++i){
            int pos = lower_bound(B+1,B+n+1,A[i]) - B;
            modify(Root[i-1],Root[i],1,n,pos,1);
        }

        //查询
        for(int i=0;i<M;++i){
            a = getInt();b = getInt();
            printf("%d\n",B[query(Root[a-1],Root[b],1,n,getInt())]);
        }
    }
    return 0;
}