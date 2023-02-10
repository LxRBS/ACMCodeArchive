/**
 * 猫在坐标0，K个老鼠分别在xi位置（有可能重复），终点在坐标N
 * 每一秒钟，首先选择一只老鼠向右移动一格，其次猫向右移动一格，且吃掉该格上的所有老鼠
 * 问最多能跑掉几只老鼠
 * 
 * 首先仍然是贪心，优先移动靠右的老鼠
 * 令猫当前坐标为a，最靠右老鼠坐标为x，则接下来的N-x秒都会移动该老鼠
 * 此时间内猫到达了a+N-x坐标，如果还有老鼠在右边，继续这个过程。
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

typedef long long llt;

typedef unordered_map<int, int> hash_t;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 400010;
#endif

int X[SIZE], A[SIZE];
int N, K;
hash_t Map;

int proc(){
	sort(X+1, X+K+1);

    llt a = 0LL;
	int cnt = 0;
	for(int i=K;i>=1;--i){
		if(a < X[i]){
            ++cnt;
			a += N - X[i]; 
		}else{
			break;
		}		
	}
	return cnt;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		Map.clear();
		N = getInt();
		K = getInt();
		for(int i=1;i<=K;++i) ++Map[A[i] = N - (X[i] = getInt())];
		printf("%d\n", proc());
	}
    return 0;
}