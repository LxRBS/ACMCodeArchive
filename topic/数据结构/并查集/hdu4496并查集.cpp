#include <cstdio>
#include <algorithm>
using namespace std;
#define SIZE 10001
int Father[SIZE] = {0};
void init(int n){for(int i=0;i<=n;++i)Father[i]=i;}
int find(int x){
	return x == Father[x] ? x : Father[x] = find(Father[x]);
}
void unite(int x,int y){
	x = find(x);
	y = find(y);
	Father[y] = x;
}

int N,M;
int U[SIZE*10],V[SIZE*10];
int A[SIZE*10];
bool read(){
	if ( EOF == scanf("%d%d",&N,&M) )return false;
	init(N);
	for(int i=0;i<M;++i)scanf("%d%d",U+i,V+i);
	return true;
}
void solve(){
	int r = N;
	A[M] = N;
    for(int i=M-1;i>=0;--i){
		if ( find(U[i]) != find(V[i]) ){
            --r;
		}
		A[i] = r;
		unite(U[i],V[i]);
		if ( 1 == r ){
			fill(A+1,A+i,1);
			break;
		}
	}
	for(int i=1;i<=M;++i)printf("%d\n",A[i]);
}
int main(){
	while(read()) solve();
	return 0;
}