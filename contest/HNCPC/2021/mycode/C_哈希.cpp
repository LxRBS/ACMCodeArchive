/**
 * 在一个升序数组里，对每个Ai问是否存在j和k满足2Ai=Aj+Ak
 * 用hash，接近O(N^2)
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 9;
#else
int const SIZE = 1100;
#endif

int N;
int A[SIZE];
unordered_set<int> Map;

int proc(){
    auto END = Map.end();

    int ans = 0;
	for(int i=2;i<N;++i){
		for(int j=1;j<i;++j){
			if(Map.find(A[i]+A[i]-A[j]) != END){
				++ans;
				break;
			}
		}
	}    	 
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    while(1 == scanf("%d", &N)){
		Map.clear();
		for(int i=1;i<=N;++i){
			scanf("%d", A+i);
			Map.insert(A[i]);
		}
		printf("%d\n", proc());
	}
    return 0;
}