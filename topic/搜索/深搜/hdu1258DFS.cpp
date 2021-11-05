#include <cstdio>
#include <vector>
using namespace std;

int T,N;
int A[13] = {0};
bool Flag;
bool read(){
	scanf("%d%d",&T,&N);
	if ( 0 == N ) return false;
	for(int i=1;i<=N;++i)scanf("%d",A+i);
	return true;
}
void dfs(int idx,int sum,vector<int>&v){
	if ( idx > N || sum > T ) return;
	if ( sum == T ){
		Flag = true;
		printf("%d",v[0]);
		for(unsigned i=1;i<v.size();++i)printf("+%d",v[i]);
		printf("\n");
	}
	for(int i=idx+1;i<=N;++i){
		v.push_back(A[i]);
		dfs(i,sum+A[i],v);
		v.pop_back();
		while( i <= N && A[i] == A[i+1] ) ++i;
	}
}
void proc(){
	printf("Sums of %d:\n",T);
	Flag = false;
	vector<int> v;
	dfs(0,0,v);
	if ( !Flag ) printf("NONE\n");
}
int main(){
	while( read() ) proc();
	return 0;
}
