#include <cstdio>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;
#define SIZE 20
int N,M;
int C[SIZE][SIZE];
bool Flag[SIZE][SIZE];
int L[SIZE];//���ͼ
//�������ͼ��sΪԴ��,tΪ���
bool bfs(int s,int t){
	fill(L+1,L+N+1,-1);
	queue<int> q;
	q.push(s);
	L[s] = 0;

	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int v=1;v<=N;++v)if(Flag[u][v]&&C[u][v]>0&&-1==L[v]){
			q.push(v);
			L[v] = L[u] + 1;
		}
	}
	return -1 != L[t];
}
//�ڲ��ͼ����������·��
//cf�ǵ���ǰ��ڵ�Ŀ�������t�ǻ��
int dfs(int u,int cf,int t){
	if ( u == t ) return cf;
      int tf = 0;//��ǰ�ڵ㵽��һ��Ŀ���������
	for(int v=1;v<=N;++v){
		if(Flag[u][v]&&C[u][v]>0&&L[u]+1==L[v]&&cf>tf){
			int f = dfs(v,min(C[u][v],cf-tf),t);
			if ( 0 == f ) continue;
			C[u][v] -= f;
			C[v][u] += f;
                  tf += f;
		}
	}
      if ( 0 == tf ) L[u] = -1;
	return tf;
}
//Dinic�㷨
int Dinic(int s,int t){
	int ans = 0;
	while( bfs(s,t) ){
		int res;
		while( res = dfs(s,INT_MAX,t) )
			ans += res;
	}
	return ans;
}
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	for(int kase=1;kase<=nofkase;++kase){
		scanf("%d%d",&N,&M);
		for(int i=1;i<=N;++i)fill(C[i],C[i]+N+1,0),fill(Flag[i],Flag[i]+N+1,false);
		for(int i=0;i<M;++i){
			int x,y,c;
			scanf("%d%d%d",&x,&y,&c);
			C[x][y] += c;
			Flag[x][y] = Flag[y][x] = true;
		}
		printf("Case %d: %d\n",kase,Dinic(1,N));
	}
	return 0;
}