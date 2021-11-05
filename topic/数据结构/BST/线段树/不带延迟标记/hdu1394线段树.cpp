#include <cstdio>
#include <algorithm>
using namespace std;

int const SIZE = 5001;

int A[SIZE];//源数组

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}
int ST[SIZE<<2];//静态数组实现线段树，树根为1

//树根值为左儿子加右儿子
inline void _pushUp(int t){
	ST[t] = ST[lson(t)] + ST[rson(t)];
}
//建立一棵空线段树，树根位于ST[t]，表示[s,e]区间
void build(int t,int s,int e){
    ST[t] = 0;
	if ( s == e ) return;
	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
}
//更新，以v为基准，更新[s,e]区间，树根位于ST[t]
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
//查询,ST[t]表示区间[s,e]值，查询[a,b]之间的值
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
		build(1,0,n-1);//建一个空树，树根ST[1]，代表区间[0,n-1]
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
