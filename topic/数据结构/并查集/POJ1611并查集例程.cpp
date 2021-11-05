//²¢²é¼¯
#include <stdio.h>

struct ufs_t{
    enum{UF_SIZE=30000};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

int main(){
	int n,m;
	while( scanf("%d%d",&n,&m) ){
		if ( 0 == n && 0 == m ) return 0;
		UF.init(n);
		for(int i=0;i<m;++i){
			int nn,x;
			scanf("%d%d",&nn,&x);
			for(int j=1;j<nn;++j){
				int y;
				scanf("%d",&y);
				UF.unite(x,y);
			}
		}

		int ret = 0;
		for(int i=0;i<n;++i)
		    if ( UF.find(0) == UF.find(i) )
		        ++ret;
	    printf("%d\n",ret);
	}
	return 0;
}
