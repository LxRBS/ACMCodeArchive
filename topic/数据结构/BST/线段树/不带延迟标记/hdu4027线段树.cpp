#include <cstdio>
#include <cmath>
#include <numeric>
#include <algorithm>
using namespace std;

int const SIZE = 100004;
typedef long long llt;

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

//线段树
llt ST[SIZE<<2];
 
void _pushUp(int t){
	ST[t] = ST[lson(t)] + ST[rson(t)];
} 

void build(int t,int s,int e){
    if ( s == e ){
    	scanf("%I64d",ST+t);
    	return;
	}	
	
	int m = ( s + e ) >> 1;
	build(lson(t),s,m);
	build(rson(t),m+1,e);
	_pushUp(t);
}

//更新[a,b]区间 
void modify(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){//[s,e]均要更新 
    	 if ( e - s + 1 == ST[t] ) return;
    }	

    if ( s == e ){
    	ST[t] = sqrt((double)ST[t]);
    	return;
	}
	
	int m = ( s + e ) >> 1;
	if ( a <= m ) modify(lson(t),s,m,a,b);
	if ( m < b ) modify(rson(t),m+1,e,a,b);
	_pushUp(t);
}

llt query(int t,int s,int e,int a,int b){
	if ( a <= s && e <= b ) return ST[t];
	int m = ( s + e ) >> 1;
	llt r = 0LL;
	if ( a <= m ) r += query(lson(t),s,m,a,b);
	if ( m < b ) r += query(rson(t),m+1,e,a,b);
	return r;  
}

int N;
bool read(){
	if ( EOF == scanf("%d",&N) ) return false;
    build(1,1,N);
	return true;
} 
int main(){
	for(int kase=1;read();++kase){
		printf("Case #%d:\n",kase);
		
		int m;
		scanf("%d",&m);
		while(m--){
			int t,x,y;
			scanf("%d%d%d",&t,&x,&y);
			if ( x > y ) swap(x,y);
			if ( t ){
                printf("%I64d\n",query(1,1,N,x,y));
			}else{
				modify(1,1,N,x,y);				
			}
		}
		printf("\n");
	}
	return 0;
}
