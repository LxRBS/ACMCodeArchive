#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 100003
struct _t{
	int left;
	int right;
	int cnt;
}Node[SIZE*20];//�߶����Ľڵ�
int toUsed = 1;
int Root[SIZE];//��ָ������

int A[SIZE];//Դ����
int B[SIZE];//������������

//idxΪ���ڵ��ָ��,[s,e]Ϊ����
//������ʱ��cntȫΪ0
void build(int&idx,int s,int e){
	idx = toUsed++;
	Node[idx].left = Node[idx].right = Node[idx].cnt = 0;
	if ( s == e ) return;

	int mid = (s+e)>>1;
	build(Node[idx].left,s,mid);
	build(Node[idx].right,mid+1,e);
}

//oldΪ�Ͻڵ�ָ�룬idxΪ���ڵ�ָ��,[s,e]Ϊ����,cΪ�����µĵ�
void update(int old,int&idx,int s,int e,int c){
	idx = toUsed ++;
	Node[idx] = Node[old];
	++Node[idx].cnt;//���¾���������һ����
	if ( s == e ) return;

	int mid = ( s + e ) >> 1;
	c <= mid ? update(Node[old].left,Node[idx].left,s,mid,c)
		     : update(Node[old].right,Node[idx].right,mid+1,e,c);
}

//root1��root2�������ò�ͬʱ�̵���,[s,e]Ϊ���䣬kΪҪ��ѯ�ĵ�
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

		//ȷ��һ���ж��ٸ��������
		int n = unique(B+1,B+N+1) - (B+1);
	    
		toUsed = 1;
		//����һ������cntȫΪ0
		build(Root[0],1,n);

		//��Դ�����ÿһ��������������
		for(int i=1;i<=N;++i){
			//c��ʾA[i]������Դ�����еĵ�cth��ȡֵ��1~n
			int c = lower_bound(B+1,B+n+1,A[i]) - B;
			update(Root[i-1],Root[i],1,n,c);
		}

		//��ѯ
		for(int i=0;i<M;++i){
			int a,b,k;
			scanf("%d%d%d",&a,&b,&k);
			int ans = query(Root[a-1],Root[b],1,n,k);
			printf("%d\n",B[ans]);
		}
	}
	return 0;
}