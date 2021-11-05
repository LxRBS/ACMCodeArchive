#include <iostream>
#include <algorithm>
using namespace std;

int const SIZE = 200000 + 2;
int ST[SIZE<<2];
int A[SIZE];

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}
//计算父节点
inline void _pushUp(int t){
    ST[t] = max(ST[lson(t)],ST[rson(t)]);
	return;
}
void build(int t,int s,int e){
	if ( s == e ){
		ST[t] = A[s];
		return;
	}
	//递归
	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
	//向上计算
	_pushUp(t);
	return;
}
//将第sn个节点更新为num
void update(int t,int s,int e,int sn,int num){
	if ( s == e ){
		ST[t] = num;
		return;
	}
	//递归
	int mid = ( s + e ) >> 1;
	if ( sn <= mid ) update(lson(t),s,mid,sn,num);
	else             update(rson(t),mid+1,e,sn,num); 
	//计算更新父节点
    _pushUp(t);
}
//查询[a,b]中的最大值
int query(int t,int s,int e,int a,int b){
	if ( a <= s && e <= b ) return ST[t];

	int mid = ( s + e ) >> 1;
	int ans = 0;
	if ( a <= mid )ans = query(lson(t),s,mid,a,b);
	if ( b > mid ){	
		int y = query(rson(t),mid+1,e,a,b);
		if ( ans < y ) ans = y;
	}
	return ans;
}

int main(){
	int n,m;
	while( EOF != scanf("%d%d",&n,&m) ){
        for(int i=1;i<=n;++i)scanf("%d",A+i);
		//建树
		build(1,1,n);
		//操作
		while(m--){
			char op[2];
			int a,b;
			scanf("%s%d%d",op,&a,&b);
			
			if ( 'U' == *op ){
                update(1,1,n,a,b);
			}else{
                printf("%d\n",query(1,1,n,a,b));
			}
		}
	}
	return 0;
}
