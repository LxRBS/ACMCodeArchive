#include <iostream>
using namespace std;

int const SIZE = 100000+5;
int SegTree[SIZE<<2];
int Delay[SIZE<<2];

#define lson(x) ( (x) << 1 )
#define rson(x) ( (x) << 1 | 1 )

void calDad(int root,int st[]){
	st[root] = st[lson(root)] + st[rson(root)];
}
//���¼��������Ϣ����root�ڵ��µ�range�θ���
void calSon(int root,int range,int st[]){
	if ( Delay[root] ){
        Delay[lson(root)] = Delay[rson(root)] = Delay[root];
		st[lson(root)] = ( range - ( range >> 1 ) ) * Delay[root];
        st[rson(root)] = ( range >> 1 ) * Delay[root];
		Delay[root] = 0;
	}
}
void build(int root,int left,int right,int st[]){
	Delay[root] = 0;
	SegTree[root] = 1;
	if ( left == right ) return;
	//�ݹ�
	int mid = ( left + right ) >> 1;
	build(lson(root),left,mid,st);
	build(rson(root),mid+1,right,st);
	calDad(root,st);
}
//��[a,b]�������Ϊc���ɶθ���
void update(int root,int left,int right,int a,int b,int c,int st[]){
	if ( a <= left && right <= b ){
		Delay[root] = c;
		st[root] = c * ( right - left + 1 );
		return;
	}
	//�ݹ�
    calSon(root,right - left + 1,st);
	int mid = ( left + right ) >> 1;
	if ( a <= mid ) update(lson(root),left,mid,a,b,c,st);
	if ( b > mid ) update(rson(root),mid+1,right,a,b,c,st);
	calDad(root,st);
}
int main(){
	int nofcase;
	scanf("%d",&nofcase);
	for(int kase=1;kase<=nofcase;++kase){
		int n,m;
		scanf("%d%d",&n,&m);
		//����
		build(1,1,n,SegTree);
		for(int i=0;i<m;++i){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			update(1,1,n,a,b,c,SegTree);
		}
		//ֻ���ܺͣ����������Ĵ洢ֵ
		printf("Case %d: The total value of the hook is %d.\n",kase,SegTree[1]);
	}
	return 0;
}