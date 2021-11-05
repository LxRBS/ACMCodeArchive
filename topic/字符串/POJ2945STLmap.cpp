#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

char Input[22];
string Str[20000];
int Ans[20001];

int main(){
	int n,m;

	while(scanf("%d%d%*c",&n,&m) && n && m){
		for(int i=0;i<n;++i){
			scanf("%s",Input);
			Str[i] = string(Input);
		}

		sort(Str,Str+n);
		
		for(int i=0;i<n;){
            int k = 1;
			while( Str[i] == Str[i+1] ){
				++k;++i;
			}
			++Ans[k];
			++i;
		}

		for(int i=1;i<=n;++i){
			Str[i-1].clear();
			printf("%d\n",Ans[i]);
		}
		memset(Ans,0,sizeof(int)*n);
		
	}
	return 0;
}