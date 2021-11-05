#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct _t{
	int d;
	int r,c;
	int t;
	_t(int dd,int rr,int cc,int tt):d(dd),r(rr),c(cc),t(tt){}
};

char A[2][12][12];
bool B[2][12][12];
int N,M,T;
int DR[] = {-1,1,0,0};
int DC[] = {0,0,-1,1};//Ç°ºó×óÓÒ

void read(){
    scanf("%d%d%d",&N,&M,&T);
    for(int i=0;i<N;++i) scanf("%s",A[0][i]);
    for(int i=0;i<N;++i) scanf("%s",A[1][i]);
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
    	if ( ( '#' == A[0][i][j] && '*' == A[1][i][j] )
    	  || ( '#' == A[1][i][j] && '*' == A[0][i][j] )
		  || ( '#' == A[0][i][j] && '#' == A[1][i][j] ) )
    		A[0][i][j] = A[1][i][j] = '*';
    }
}
bool bfs(){
	if ( T <= 0 ) return false;

	memset(B,0,sizeof(B));

    queue<_t> q;
    q.push(_t(0,0,0,0));
    B[0][0][0] = true;

    while( !q.empty() ){
    	_t u = q.front();
    	q.pop();

    	for(int i=0;i<4;++i){
            int nr = u.r + DR[i];
            int nc = u.c + DC[i];

            if ( nr < 0 || nr >= N || nc < 0 || nc >= M ) continue;

            int nd = u.d;
            if ( '#' == A[u.d][nr][nc] ) nd = u.d ^ 1;

            if ( 'P' == A[nd][nr][nc] ) return true;

            if ( '*' == A[nd][nr][nc] || B[nd][nr][nc] ) continue;

            if ( u.t + 1 < T ){
            	q.push(_t(nd,nr,nc,u.t+1));
            	B[nd][nr][nc] = true;
            }
    	}
    }

	return false;
}
int main() {
	int kase;
	scanf("%d",&kase);
	while(kase--){
		read();
		printf(bfs()?"YES\n":"NO\n");
	}
	return 0;
}
