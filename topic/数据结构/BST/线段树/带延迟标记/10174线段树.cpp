#include <iostream>
using namespace std;

//用数组实现线段树
int const SIZE = 100000+1;

int Node[SIZE<<2] = {0};
int Flag[SIZE<<2] = {0};

//以0为根
#define lson(x) ( ( (x) << 1 ) | 1 )
#define rson(x) ( ( (x) + 1 ) << 1 )

//确定父节点的存储值
void _pushUp(int t){
	Node[t] = Node[lson(t)] + Node[rson(t)];
}
//延迟操作,确定子节点的值
void _pushDown(int t,int s,int e){
	//Flag表示每个节点需要改变的值
	if ( Flag[t] ){
		int x = Flag[t];
		Flag[t] = 0;
		Flag[lson(t)] += x;
		Flag[rson(t)] += x;
		int mid = ( s + e ) >> 1;
		Node[lson(t)] += x * ( mid - s + 1 );
		Node[rson(t)] += x * ( e - mid );
	}
}
//在数组里建立线段树
void build(int t,int s,int e){
	//如果区间宽度为1，则输入建立，此处均为0
	if ( s == e ) return;

	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
	_pushUp(t);
}

//成段更新,[a,b]增加c
void update(int t,int s,int e,int a,int b,int c){
	//如果区间宽度为1
	if ( a <= s && e <= b ){
		Flag[t] += c;
		Node[t] += c * ( e - s + 1 );
		return;
	}
	_pushDown(t,s,e);
	//递归
	int mid = ( s + e ) >> 1;
	if ( a <= mid ) update(lson(t),s,mid,a,b,c);
	if ( mid < b )  update(rson(t),mid+1,e,a,b,c);
	_pushUp(t);
}
//查询[a,b]
int query(int t,int s,int e,int a,int b){
    if( a <= s && e <= b ) return Node[t];
	_pushDown(t,s,e);
	int ans = 0;
	int mid = ( s + e ) >> 1;
	if ( a <= mid ) ans += query(lson(t),s,mid,a,b);
	if ( mid < b ) ans += query(rson(t),mid+1,e,a,b);
	return ans;
}

int main(){
	int n,m;
	while( EOF != scanf("%d%d",&n,&m) ){
        memset(Node,0,(n<<2)*sizeof(int));
		memset(Flag,0,(n<<2)*sizeof(int));

	    for(int i=0;i<m;++i){
			char cmd[5];
			scanf("%s",cmd);
			if ( 'C' == *cmd ){
				int x,num;
				scanf("%d%d",&x,&num);
				--x;

				if ( x + num > n ){
					update(0,0,n-1,x,n-1,1);
					num -= n - x;
				}else{
					update(0,0,n-1,x,x+num-1,1);
					continue;
				}

				int c = num / n;
				if ( c ) update(0,0,n-1,0,n-1,c);

				c = num % n;
				if ( c ) update(0,0,n-1,0,c-1,1);

			}else if ( 'U' == *cmd ){
				int x,num;
				scanf("%d%d",&x,&num);
				--x;

				if ( x + 1 > num ){
					update(0,0,n-1,x-num+1,x,1);
					continue;
				}

				update(0,0,n-1,0,x,1);
				num -= x + 1;

				int c = num / n;
				if ( c ) update(0,0,n-1,0,n-1,c);

				c = num % n;
				if ( c ) update(0,0,n-1,n-c,n-1,1);
			}else{
				int x;
				scanf("%d",&x);
				--x;
				printf("%d\n",query(0,0,n-1,x,x));
			}
		}
	}
	return 0;
}
