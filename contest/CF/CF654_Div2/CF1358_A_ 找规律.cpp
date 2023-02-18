/**
 n×m的格子，在边的中点放一盏灯就能照亮两边的格子
 问照亮所有格子最少要几个灯
 贪心一下即可
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}


int N, M;

int proc(){
	if(N > M) swap(N, M);
	if(1 == N) return M + 1 >> 1;

    return N & 1 ? (N>>1)*M+(M+1>>1) : (N>>1) * M;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getUnsigned();
	while(nofkase--){
        N = getUnsigned();
		M = getUnsigned();
		printf("%d\n", proc());
	}
	return 0;
}