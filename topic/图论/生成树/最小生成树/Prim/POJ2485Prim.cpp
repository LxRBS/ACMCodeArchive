#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Graph[500][500];
int Ans;
int N;

bool Flag[500];
int Edge[500];
vector<int> Used;

int main(){
	int t;
	scanf("%d",&t);

	while(t--){
		scanf("%d",&N);
		for(int i=0;i<N;++i)for(int j=0;j<N;++j)
			scanf("%d",Graph[i]+j);

		Ans = 0;
		memset(Flag,0,sizeof(Flag));
		Used.clear();

		int num = 1;
		Flag[0] = true;
		Used.push_back(0);

		while( num != N ){
			int t = INT_MAX;
			int jt = -1;

			vector<int>::iterator it;
			for(it=Used.begin();it!=Used.end();++it){
				for(int j=0;j<N;++j)if(!Flag[j]){
					if ( t > Graph[*it][j] ){
						t = Graph[*it][j];
						jt = j;
					}
				}				
			}

			Flag[jt] = true;
			Used.push_back(jt);
			++num;

			if ( Ans < t ) Ans = t;
		}

		printf("%d\n",Ans);
	}

	return 0;
}
