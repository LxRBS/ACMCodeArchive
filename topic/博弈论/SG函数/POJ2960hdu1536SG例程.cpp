/**
  若干堆若干个石子，双方轮流取，最后不能取者判负。
  但是，每次取出石子的个数受到限制，由一个整数集合规定。问先手的胜负。
*/
#include <iostream>
#include <algorithm>
using namespace std;

int const MAX = 10001; 
int g[MAX];
int S[101];
int stone[101];

//给定合法集合S，计算所有的sg值
//参数num是S的size
void calsg(int num){
	g[0] = 0;
	char flag[101];
	int i,j,n;
    for(i=1;i<MAX;i++){
		memset(flag,0,sizeof(flag));
        for(j=0;j<num;j++){
			if ( i - S[j] >= 0 ){ 
				flag[ g[ i - S[j] ] ] = 1;
			}
		}
		for(j=0;;j++)if(!flag[j]) {
			g[i] = j;
			break;
		}
	}
	return;
}

int main(){
	int k=0;
	int cases;//测试的个数
	while(cin>>k && k){
		memset(g,-1,MAX);
        int i;
		for(i=0;i<k;i++) cin>>S[i];
		sort(S,S+k);
		calsg(k);

		cin>>cases;
        while(cases--){
			int num;//石子堆数
			cin>>num;
			cin>>stone[0];
			int ans = g[stone[0]];
            for(i=1;i<num;i++) {
				cin>>stone[i];
				ans ^= g[stone[i]];
			}
			if ( ans ) cout<<'W';
			else       cout<<'L';
		}
		cout<<endl;
	}
	return 0;
}
