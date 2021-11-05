/*
    可持久化线段树
    一共4种操作：
    C l r d:A[l...r]都增加一个d，且时间戳加1
    Q l r:求区间和
    H l r t:求历史区间和
    B t:回到过去
    不能使用pushDown，因为会MLE
    不能使用pushUp，因为不能保证子节点的和是当前的和，必须手动更新
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

typedef long long llt;
int const SIZE = 100003;
struct node_t{
    int left; //左儿子
    int right;//右儿子
    llt sum;
    llt lazy;
}Node[SIZE*50];
int toUsed = 0;
int Root[SIZE];//根节点
int TimeStamp;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

inline int _newNode(){
    Node[toUsed].left = Node[toUsed].right = Node[toUsed].sum = Node[toUsed].lazy = 0;
    return toUsed++;
}

//t为本节点的指针,[s,e]为区间
void _build(int&t,int s,int e){
    t = _newNode();
    if ( s == e ){
        Node[t].sum = getInt();
        return;
    }

    int mid = ( s + e ) >> 1;
    _build(Node[t].left,s,mid);
    _build(Node[t].right,mid+1,e);
    Node[t].sum = Node[Node[t].left].sum + Node[Node[t].right].sum;
}

inline void build(int&t,int s,int e){
    toUsed = 0;
    _newNode();
    _build(t,s,e);
}

//区间增加，必须保证[a,b]是[s,e]的子区间
void modify(int old,int& t,int s,int e,int a,int b,llt delta){
    Node[t=_newNode()] = Node[old];
    Node[t].sum += ( b - a + 1 ) * delta;

    if ( a <= s && e <= b ){
        Node[t].lazy += delta;
        return;
    }

    int mid = ( s + e ) >> 1;
    if ( a <= mid ) modify(Node[old].left,Node[t].left,s,mid,a,min(b,mid),delta);
    if ( mid < b ) modify(Node[old].right,Node[t].right,mid+1,e,max(a,mid+1),b,delta);
}

//区间求和
llt query(int t,int s,int e,int a,int b,llt lazy){
    if ( a <= s && e <= b ) return Node[t].sum + lazy * ( e - s + 1 );

    int mid = ( s + e ) >> 1;
    llt ret = 0LL;
    if ( a <= mid ) ret += query(Node[t].left,s,mid,a,b,Node[t].lazy+lazy);
    if ( mid < b ) ret += query(Node[t].right,mid+1,e,a,b,Node[t].lazy+lazy);
    return ret;
}

int N,M;
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;
    TimeStamp = 0;
    build(Root[TimeStamp],1,N);
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    char cmd[3];
    int a,b,dt;
    bool flag = false;
    while( read() ){
        if ( flag ) printf("\n");
        else flag = true;

        while(M--){
            if (4==M){
                int x = 4;
            }
            scanf("%s",cmd);
            switch(*cmd){
            case 'C':{
                a = getInt();b = getInt();
                modify(Root[TimeStamp],Root[TimeStamp+1],1,N,a,b,getInt());
                ++TimeStamp;
            }break;

            case 'Q':{
                a = getInt();
                printf("%lld\n",query(Root[TimeStamp],1,N,a,getInt(),0));
            }break;

            case 'H':{
                a = getInt();b = getInt();
                printf("%lld\n",query(Root[getInt()],1,N,a,b,0));
            }break;

            case 'B':{
                TimeStamp = getInt();
            }break;

            }
        }
    }
    return 0;
}
