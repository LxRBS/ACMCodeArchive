/**
 * N堆石子，可以做如下操作：每次选3堆，将中间那堆拿走两个，一边放一个。
 * 问：要将所有石子都置于第1堆和第N堆，最少需要几次操作？不可行则输出-1。
 * 首先1和N显然不影响答案。其次，如果都是偶数，显然可行，且一次操作完成2个，除2即可
 * 考虑某堆为奇数，显然它的左边或者右边必然有堆，因此总是可以取的
 * 取出2个以后，1个把奇数补成偶数，另1个直接扔到终点即可
 * 如果另外一边还有奇数堆，也没有关系。因为总之对每一个奇数堆，要花费一个石子来变成偶数
 * 因此所有单个的石子要花费一个操作，剩下的都是成对的石子，每对花费一个。
 * 注意特判全1的情况。
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

#ifndef ONLINE_JUDGE
int const SIZE = 33;
#else
int const SIZE = 100100;
#endif

int N;
int A[SIZE];

typedef long long llt;


llt proc(){
    if(3 == N){
		if(A[1]&1) return -1;
		return A[1]/2;
	}

	if([&]()->bool{
		for(int i=1;i<N-1;++i){
			if(1 == A[i]) continue;
			return false;
		}
		return true;
	}()) return -1;

    int cnt = 0;
	llt ans = 0;
	for(int i=1;i<N-1;++i){
		if(A[i]&1) ++cnt;
		ans += A[i];
	}
	return (ans - cnt) / 2 + cnt;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		for(int i=0;i<N;++i) A[i] = getInt();
		printf("%lld\n", proc());
	}
    return 0;
}