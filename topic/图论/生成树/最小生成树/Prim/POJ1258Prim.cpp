#include <iostream>

using namespace std;

int Graph[100][100];

//返回最小生成树的长度
long long int Prim(int n){
    int min[100];
	long long int ret = 0;
	bool flag[100] = {0};
	int i,j,k;

	for(i=0;i<n;++i)
		min[i] = INT_MAX;

	for(min[j=0]=0;j<n;++j){
		for(k=-1,i=0;i<n;++i)
			if ( !flag[i] && ( -1==k || min[i] < min[k] ) )
				k = i;
		for(flag[k]=1,ret+=min[k],i=0;i<n;++i)
			if ( !flag[i] && Graph[k][i] < min[i] )
				min[i] = Graph[k][i];
	}

	return ret;
}

int main(){
	int n;

	while( EOF != scanf("%d",&n) ){
        for(int i=0;i<n;i++)for(int j=0;j<n;j++)
			scanf("%d",Graph[i]+j);

        printf("%I64d\n",Prim(n));
	}

	return 0;
}