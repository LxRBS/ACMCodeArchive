#include <cstdio>
#include <algorithm>
using namespace std;
#define SIZE 10000003
int Parent[SIZE];
inline void init(int n){for(int i=1;i<=n;Parent[i]=i++);}
inline int find(int x){return Parent[x]==x?x:Parent[x]=find(Parent[x]);}
inline void unite(int x,int y){
	x = find(x), y = find(y);
	x < y ? Parent[y] = x : Parent[x] = y;
}

int A[SIZE];
int main(){
	int n;
	while( EOF != scanf("%d",&n) ){
		if ( 0 == n ){
			printf("1\n");
			continue;
		}
		init(n);
		for(int i=0;i<n;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			unite(x,y);
		}

		fill(A+1,A+n+1,0);
		for(int i=1;i<=n;++i)++A[find(i)];
		printf("%d\n",*max_element(A+1,A+n+1));
	}
	return 0;
}