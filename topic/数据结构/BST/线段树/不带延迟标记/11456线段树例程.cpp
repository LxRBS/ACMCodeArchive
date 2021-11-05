//��̬��������� 
#include <cstdio>

int const SIZE = 100005;

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}


int A[SIZE];//Դ���飬ʵ���Ͽ��Բ��� 
int ST[SIZE<<2];//�߶����ĳ�����Դ�����4�� 
int N,M;

//��Ϣ�ϴ�,t��ʾ�ڵ㣬����t�Ķ��Ӽ���t����Ϣ 
void _pushUp(int t){
	ST[t] = ST[lson(t)] + ST[rson(t)];
} 

//������t��ʾ�ڵ㣬[s,e]��ʾt����������� 
void build(int t,int s,int e){
	if ( s == e ){
		ST[t] = A[s];
		return;
	}
	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
	_pushUp(t);
}

//��ѯ,t��ʾ�ڵ㣬[s,e]��ʾt�����������
//[a,b]��ʾ�������󣬼���[a,b]������� 
int query(int t,int s,int e,int a,int b){
	if ( a <= s && e <= b ) return ST[t];
	int mid = ( s + e ) >> 1;
	int ret = 0;
	if ( a <= mid ) ret += query(lson(t),s,mid,a,b);
	if ( mid < b ) ret += query(rson(t),mid+1,e,a,b);
	return ret;
} 

bool read(){
	if ( EOF == scanf("%d%d",&N,&M) ) return false;
	for(int i=1;i<=N;++i) scanf("%d",A+i);
	build(1,1,N);
	return true;
}

int main(){
	for(int kase=1;read();++kase){
		printf("Case %d:\n",kase);
		for(int i=0;i<M;++i){
			int a,b;
			scanf("%d%d",&a,&b);
			printf("%d\n",query(1,1,N,a,b));
		}
	}
	return 0;
}
