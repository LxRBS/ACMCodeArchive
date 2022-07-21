#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 100003
struct _t{
	int left;
	int right;
	int cnt;
}Node[SIZE*20];//线段树的节点
int toUsed = 1;
int Root[SIZE];//根指针数组

int A[SIZE];//源数组
int B[SIZE];//用于排序数组

//idx为本节点的指针,[s,e]为区间
//建树的时候cnt全为0
void build(int&idx,int s,int e){
	idx = toUsed++;
	Node[idx].left = Node[idx].right = Node[idx].cnt = 0;
	if ( s == e ) return;

	int mid = (s+e)>>1;
	build(Node[idx].left,s,mid);
	build(Node[idx].right,mid+1,e);
}

//old为老节点指针，idx为本节点指针,[s,e]为区间,c为待更新的点
void update(int old,int&idx,int s,int e,int c){
	idx = toUsed ++;
	Node[idx] = Node[old];
	++Node[idx].cnt;//更新就是新来了一个数
	if ( s == e ) return;

	int mid = ( s + e ) >> 1;
	c <= mid ? update(Node[old].left,Node[idx].left,s,mid,c)
		     : update(Node[old].right,Node[idx].right,mid+1,e,c);
}

//root1和root2代表两棵不同时刻的树,[s,e]为区间，k为要查询的点
int query(int root1,int root2,int s,int e,int k){
	if ( s == e ) return s;
	int x = Node[Node[root2].left].cnt - Node[Node[root1].left].cnt;
	int mid = ( s + e ) >> 1;
	return x >= k ? query(Node[root1].left,Node[root2].left,s,mid,k)
		:query(Node[root1].right,Node[root2].right,mid+1,e,k-x);
}
int N,M;
inline void read(){
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;++i){
		scanf("%d",A+i);
		B[i] = A[i];
	}
}
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		read();
		sort(B+1,B+N+1);

		//确定一共有多少个互异的数
		int n = unique(B+1,B+N+1) - (B+1);
	    
		toUsed = 1;
		//建第一棵树，cnt全为0
		build(Root[0],1,n);

		//对源数组的每一个数依次做更新
		for(int i=1;i<=N;++i){
			//c表示A[i]是整个源数组中的第cth，取值从1~n
			int c = lower_bound(B+1,B+n+1,A[i]) - B;
			update(Root[i-1],Root[i],1,n,c);
		}

		//查询
		for(int i=0;i<M;++i){
			int a,b,k;
			scanf("%d%d%d",&a,&b,&k);
			int ans = query(Root[a-1],Root[b],1,n,k);
			printf("%d\n",B[ans]);
		}
	}
	return 0;
}