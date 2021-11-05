#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;

int const SIZE = 100005;
int const INF = SIZE;

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

int ST[SIZE<<2];
int A[SIZE];

void _pushUp(int t){
	ST[t] = min(ST[lson(t)],ST[rson(t)]);
}

void build(int t,int s,int e){
	if ( s == e ){
		ST[t] = A[s];
		return;
	}
	
	int m = ( s + e ) >> 1;
	build(lson(t),s,m);
	build(rson(t),m+1,e);
	_pushUp(t);
}

int query(int t,int s,int e,int a,int b){
	if ( a <= s && e <= b ) return ST[t];
	int m = ( s + e ) >> 1;
	int ret = INF;
	if ( a <= m ) ret = min(ret,query(lson(t),s,m,a,b));
	if ( m < b ) ret = min(ret,query(rson(t),m+1,e,a,b));
	return ret;
}

void modify(int t,int s,int e,int idx,int newValue){
	if ( s == e ){
		ST[t] = newValue;
		return;
	}
	int m = ( s + e ) >> 1;
	if ( idx <= m ) modify(lson(t),s,m,idx,newValue);
	else modify(rson(t),m+1,e,idx,newValue);
	_pushUp(t);
}

int N,Q;
char Cmd[40];
int Shift[30];
int main(){
	scanf("%d%d",&N,&Q);
	for(int i=1;i<=N;++i)scanf("%d",A+i);
	build(1,1,N);
	while(Q--){
		scanf("%s",Cmd);
		if ( 'q' == *Cmd ){
			int a,b;
			sscanf(Cmd+6,"%d,%d",&a,&b);
			printf("%d\n",query(1,1,N,a,b));
		}else{
			int cnt = 0;
			char *p = Cmd + 5;
			while( *p != ')' ){
				sscanf(++p,"%d",Shift+cnt++);
				while( isdigit(*p) ) ++p;
			}
			int tmp = A[Shift[0]];
			for(int i=0;i<cnt-1;++i)A[Shift[i]] = A[Shift[i+1]];
			A[Shift[cnt-1]] = tmp;
			for(int i=0;i<cnt;++i){
				modify(1,1,N,Shift[i],A[Shift[i]]);
			}
		}
	}	
	return 0;
}
