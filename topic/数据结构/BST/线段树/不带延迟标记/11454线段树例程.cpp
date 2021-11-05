//单点修改区间和 
#include <cstdio>
#define SIZE 100005

int N,M;
int A[SIZE];
int ST[SIZE<<2];

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

void _pushUp(int t){
	ST[t] = ST[lson(t)] + ST[rson(t)];
}

void build(int t,int s,int e){
	if ( s == e ){
		scanf("%d",ST+t);
		return;
	}

	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
	_pushUp(t);
}

int query(int t,int s,int e,int a,int b){
	if ( a <= s && e <= b ) return ST[t];
	int mid = ( s + e ) >> 1;
	int ret = 0;
	if ( a <= mid ) ret += query(lson(t),s,mid,a,b);
	if ( b > mid ) ret += query(rson(t),mid+1,e,a,b);
	return ret;
}

void modify(int t,int s,int e,int idx,int delta){
	if ( s == e ){
		ST[t] += delta;
		return;
	}
	int mid = ( s + e ) >> 1;
	if ( idx <= mid ) modify(lson(t),s,mid,idx,delta);
	else modify(rson(t),mid+1,e,idx,delta);
	_pushUp(t);
}

bool read(){
	if ( EOF == scanf("%d%d",&N,&M) ) return false;
	build(1,1,N);
	return true;
}

int main(){
	for(int kase=1;read();++kase){
		printf("Case %d:\n",++kase);
		while(M--){
			char cmd[3];
			int a,b;
			scanf("%s%d%d",cmd,&a,&b);
			if ( 'Q' == *cmd ){
				printf("%d\n",query(1,1,N,a,b));
			}else{
				modify(1,1,N,a,b);
			}
		}
	}
	return 0;
}
