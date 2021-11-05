/**N皇后问题*/
#include <cstdio>
#include <cstring>
using namespace std;
#define SIZE 22
int N;
bool Flag[4][SIZE];

int dfs(int depth){
    if ( 0 == depth ) return 1;

    int ret = 0;
    //将第N-depth个放在第N-depth行
    for(int i=0;i<N;++i){
        if ( Flag[1][i]
		  || Flag[2][N-depth-i+N]
		  || Flag[3][N-depth+i] ) continue;

        Flag[1][i] = Flag[2][N-depth-i+N] = Flag[3][N-depth+i] = true;
        ret += dfs(depth-1);
        Flag[1][i] = Flag[2][N-depth-i+N] = Flag[3][N-depth+i] = false;
    }
    return ret;
}
int Ans[SIZE] = {0};
int main() {
	for(N=1;N<=10;++N){
		memset(Flag,0,sizeof(Flag));
		Ans[N] = dfs(N);
	}

	while(scanf("%d",&N)&&N)
		printf("%d\n",Ans[N]);

	return 0;
}
