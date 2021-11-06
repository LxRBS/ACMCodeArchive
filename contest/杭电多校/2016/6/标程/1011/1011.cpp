#include <bits/stdc++.h>

using namespace std;
const int mod = 1e9 + 7;
int dp[65][1 << 4][4][4],ha[3]={-2,0,2};
long long p[4];
inline void Modify( int & x , int v ){ x += v ; if ( x >= mod ) x -= mod ;}
inline int Transform( int a , int f ){ if( f == 3 ) return 3; int rs = a + ha[f] ; if( rs < -1 ) return -1 ; if( rs > 1 ) return 3 ; return rs + 1;}

int dfs( int x , int mask , int f1 , int f2 ){
	if( x == -1 ) return f1 >= 2 && f2 >= 1;
	if( ~ dp[x][mask][f1][f2] ) return dp[x][mask][f1][f2];
	int ed[4] , & ans = dp[x][mask][f1][f2] = 0;
	for(int i = 0 ; i < 4 ; ++ i) ed[i] = mask >> i & 1 ? 1 : (p[i] >> x & 1);
	for(int i = 0 ; i <= ed[0] ; ++ i)
		for(int j = 0 ; j <= ed[1] ; ++ j)
			for(int k = 0 ; k <= ed[2] ; ++ k)
				for(int v = 0 ; v <= ed[3] ; ++ v){
					int newf1 = Transform( i + k - j - v , f1 ) , newf2 = Transform( i + v - j - k , f2 ) , newmask = mask ;
					if( newf1 == -1 || newf2 == -1 ) continue;
					if( i < ed[0] ) newmask |= 1;
					if( j < ed[1] ) newmask |= 2;
					if( k < ed[2] ) newmask |= 4;
					if( v < ed[3] ) newmask |= 8;
					Modify( ans , dfs( x - 1 , newmask , newf1 , newf2 ) );
				}
	return ans;
}

int main( int argc , char * argv[] ){
	int T ; scanf("%d",&T);
	while(T--){
		memset( dp , -1 , sizeof( dp ) );
		scanf("%lld%lld%lld%lld" , & p[0] , & p[1] , & p[2] , & p[3] );
		printf( "%d\n" , dfs( 61 , 0 , 1 , 1  ) );
	}
	return 0;
}
