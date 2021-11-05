#include <cstdio>
int const SIZE = 1004;

int A[SIZE];//源数组
int ST[SIZE<<2];//线段树，1为树根

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

//建树,ST[t]代表源数组[s,e]的区间性质
void build(int t,int s,int e){
	if ( s == e ){
		ST[t] = 0;
		return;
	}
	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
}

//根据子节点计算父节点值
void _pushUp(int t){ST[t]=ST[lson(t)]+ST[rson(t)];}

//查询,ST[t]表示源数组[s,e]区间，要查询[a,b]的区间
int query(int t,int s,int e,int a,int b){
    if ( s == e ) return ST[t];
	int mid = ( s + e ) >> 1;
	int ret = 0;
	if ( a <= mid ) ret += query(lson(t),s,mid,a,b);
	if ( mid < b ) ret += query(rson(t),mid+1,e,a,b);
	return ret;
}
//更新,ST[t]表示源数组[s,e]区间，更新包含v的区间
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
		
		//建一个空树
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
