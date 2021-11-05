#include <cstdio>
int const SIZE = 1004;

int A[SIZE];//Դ����
int ST[SIZE<<2];//�߶�����1Ϊ����

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

//����,ST[t]����Դ����[s,e]����������
void build(int t,int s,int e){
	if ( s == e ){
		ST[t] = 0;
		return;
	}
	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
}

//�����ӽڵ���㸸�ڵ�ֵ
void _pushUp(int t){ST[t]=ST[lson(t)]+ST[rson(t)];}

//��ѯ,ST[t]��ʾԴ����[s,e]���䣬Ҫ��ѯ[a,b]������
int query(int t,int s,int e,int a,int b){
    if ( s == e ) return ST[t];
	int mid = ( s + e ) >> 1;
	int ret = 0;
	if ( a <= mid ) ret += query(lson(t),s,mid,a,b);
	if ( mid < b ) ret += query(rson(t),mid+1,e,a,b);
	return ret;
}
//����,ST[t]��ʾԴ����[s,e]���䣬���°���v������
void modify(int t,int s,int e,int v){
	if ( s == e ){
		++ST[t];
		return;
	}
	int mid = ( s + e ) >> 1;
	if ( v <= mid ) modify(lson(t),s,mid,v);
	else modify(rson(t),mid+1,e,v);
	_pushUp(t);
}

int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		int n;
		scanf("%d",&n);
		
		//��һ������
		build(1,1,n);

		int ret = 0;
		for(int i=0;i<n;++i){
			scanf("%d",A+i);
			ret += query(1,1,n,A[i]+1,n);
			modify(1,1,n,A[i]);
		}
		printf("%d\n",ret);
	}
	return 0;
}
