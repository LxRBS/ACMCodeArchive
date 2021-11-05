#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 1002
int Father[SIZE];
void init(int n){for(int i=1;i<=n;Father[i]=i++);}
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}
void unite(int x,int y){x=find(x),y=find(y),Father[y]=x;}

int Ans[SIZE];
int main(){
    int n,m;
	while( scanf("%d",&n) && n ){
		scanf("%d",&m);
		init(n);
		for(int i=0;i<m;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			unite(x,y);
		}
		fill(Ans+1,Ans+n+1,0);
		for(int i=1;i<=n;++i)Ans[find(i)] = 1;
		printf("%d\n",count(Ans+1,Ans+n+1,1)-1);
	}
	return 0;
}