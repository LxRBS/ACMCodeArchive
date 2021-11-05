//最长上升子序列
#include <cstdio>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,A[1100];
int D[1100];//Di表示以i结尾的最长子序列的长度
void dp(){
    D[0] = 1;
    for(int i=1;i<N;++i){
        D[i] = 1;
        for(int j=0;j<i;++j){
            if ( A[j] < A[i] ){
                int t = D[j] + 1;
                if ( D[i] < t ) D[i] = t;
            }
        }
    }
}

int main(){
    N = getUnsigned();
    for(int i=0;i<N;++i) A[i] = getUnsigned();
    dp();
    printf("%d\n",*max_element(D,D+N));
    return 0;
}
