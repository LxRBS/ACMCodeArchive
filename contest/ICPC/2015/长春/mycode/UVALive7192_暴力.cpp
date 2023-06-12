/*
  给定N个数，找出3个，使得
  (ai+aj)^ak 最大
  
  给了15s时间，暴力
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}


int N,A[1100];
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        for(int i=0;i<N;++i) A[i] = getUnsigned();

        int ans = -1;
        for(int i=0;i<N;++i)for(int j=i+1;j<N;++j){
            int tmp = A[i] + A[j];
            for(int k=0;k<N;++k)if(k!=i&&k!=j){
                int ttt = tmp ^ A[k];
                if(ans<ttt) ans = ttt;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

