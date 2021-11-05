#include <cstdio>
#include <algorithm>
using namespace std;

int const SIZE = 5001;

int A[SIZE];//Դ����

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}
int ST[SIZE<<2];//��̬����ʵ���߶���������Ϊ1

//����ֵΪ����Ӽ��Ҷ���
inline void _pushUp(int t){
	ST[t] = ST[lson(t)] + ST[rson(t)];
}
//����һ�ÿ��߶���������λ��ST[t]����ʾ[s,e]����
void build(int t,int s,int e){
    ST[t] = 0;
	if ( s == e ) return;
	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
}
//���£���vΪ��׼������[s,e]���䣬����λ��ST[t]
void modify(int t,int s,int e,int v){
	if ( s == e ){
		++ ST[t];
		return;
	}
	int mid = ( s + e ) >> 1;
	if ( v <= mid ) modify(lson(t),s,mid,v);
	else modify(rson(t),mid+1,e,v);
	_pushUp(t);
}
//��ѯ,ST[t]��ʾ����[s,e]ֵ����ѯ[a,b]֮���ֵ
int query(int t,int s,int e,int a,int b){
	if ( a <= s && e <= b ) return ST[t];
	int mid = ( s + e ) >> 1;
	int ret = 0;
	if ( a <= mid ) ret += query(lson(t),s,mid,a,b);
	if ( mid < b ) ret += query(rson(t),mid+1,e,a,b);
	return ret;
}
int main(){
	int n;
	while( EOF != scanf("%d",&n) ){
		build(1,0,n-1);//��һ������������ST[1]����������[0,n-1]
		int ret = 0;
		for(int i=0;i<n;++i){
			scanf("%d",A+i);
            ret += query(1,0,n-1,A[i],n-1);
			modify(1,0,n-1,A[i]);
		}
		int t = ret;
		for(int i=0;i<n;++i){
            t += n - A[i] - A[i] - 1;
			ret = min(ret,t);
		}
		printf("%d\n",ret);
	}
	return 0;
}
