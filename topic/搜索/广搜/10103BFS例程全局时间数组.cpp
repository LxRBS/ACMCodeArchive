#include <iostream>
#include <queue>

using namespace std;

int N,M,K;
int Snake[100][2];
int Ladder[100][2];
bool Flag[20*20+1];
int Ans[20*20+1];

int goStep(int n){
	for(int i=0;i<M;i++)if(n == Ladder[i][0])return Ladder[i][1];
	for(int i=0;i<K;i++)if(n==Snake[i][0]) return Snake[i][1];
	return n;
}

void bfs(){
	queue<int> que;
	que.push(1);
	
	while(1){
		int status = que.front();
		que.pop();		

		for(int i=1;i<=6;i++){
			int st = goStep(i+status);
			if ( st <= N * N && !Flag[st] ){
				que.push(st);
				Flag[st] = true;
				Ans[st] = Ans[status] + 1;
				if ( N * N == st ) return;
			}
		}		
	}
}

int main(){
	while( scanf("%d",&N) && N ){
		scanf("%d",&M);
		for(int i=0;i<M;i++)scanf("%d%d",Ladder[i],Ladder[i]+1);

		scanf("%d",&K);
		for(int i=0;i<K;i++)scanf("%d%d",Snake[i],Snake[i]+1);

		memset(Flag,0,sizeof(Flag));
		memset(Ans,0,sizeof(Ans));
		
		if ( 1 == N ){
			printf("0\n");
			continue;
		}

        bfs();
		printf("%d\n",Ans[N*N]);
	}	

	return 0;
}

