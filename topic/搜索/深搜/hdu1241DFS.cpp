#include <cstdio>
#include <cstring>

char A[105][105];
int M,N;
int DR[] = {-1,1,0,0,-1,-1,1,1};
int DC[] = {0,0,-1,1,-1,1,1,-1};
bool read(){
	scanf("%d%d",&M,&N);
	if ( 0 == M ) return false;
	for(int i=0;i<M;++i)scanf("%s",A[i]);
	return true;
}
inline bool isValid(int r,int c){
	return 0 <= r && r < M && 0 <= c && c < N;
}
void dfs(int r,int c){
	for(int i=0;i<8;++i){
		int dr = r + DR[i];
		int dc = c + DC[i];
		if ( isValid(dr,dc) && '@' == A[dr][dc] ){
			A[dr][dc] = '*';
			dfs(dr,dc);
		}
	}
}
int proc(){
	int ret = 0;
	for(int i=0;i<M;++i){
	    for(int j=0;j<N;++j){
	    	if ( '@' == A[i][j] ){
	    		A[i][j] = '*';
	    		++ret;
	    		dfs(i,j);
			}
		}
	}
	return ret;
}
int main(){
	while ( read() ) printf("%d\n",proc());
	return 0;
}
