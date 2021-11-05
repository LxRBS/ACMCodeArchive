//²¢²é¼¯
#include <stdio.h>
#include <algorithm>
#include <numeric>
using namespace std;

struct ufs_t{
    enum{UF_SIZE=1102};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

int A[ufs_t::UF_SIZE];
int main(){
	int kase;
	scanf("%d",&kase);
	while(kase--){
		int n,m;
		scanf("%d%d",&n,&m);

		UF.init(n);

		for(int i=0;i<m;++i){
			int a,b;
			scanf("%d%d",&a,&b);
			UF.unite(a,b);
		}

		fill(A+1,A+n+1,0);
		for(int i=1;i<=n;++i) A[UF.find(i)] = 1;
		printf("%d\n",accumulate(A+1,A+n+1,0));
	}
	return 0;
}
