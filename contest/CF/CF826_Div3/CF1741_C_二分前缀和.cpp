/**
 * 给一个数组，问能否划分成x段，使得每段的和均相等，且其中最长段的长度最小
 * 求这个最小长度
 * 求一个前缀和，对每一个Si，尝试以Si为目标进行划分即可。
 * 因为所有能够划分出来的子段和一定包含在Si中
 * 由于前缀和是递增的，因此下一个2Si所在的位置只需要二分就行
 */
#include <assert.h>
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

char getChar(){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 2E5+13;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using si = set<int>;

int N;
int A[SIZE], B[SIZE];

int proc(int x){
    int prv = 1;
	int v = x;
	int ans = 0;
	while(1){
		int nxt = lower_bound(B+1, B+N+1, v) - B;
		if(nxt == N + 1 || B[nxt] != v) return N;
		v += x;
		ans = max(ans, nxt - prv + 1);
		if((prv = nxt + 1) == N + 1) break;
	}
	return ans;
}

int proc(){
	int sum = B[N];
	int ans = N;
	for(int i=1;i<N;++i){
        if(sum % B[i]) continue;
		ans = min(ans, proc(B[i]));
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif   
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		for(int i=1;i<=N;++i) B[i] = B[i-1] + (A[i] = getInt());
		printf("%d\n", proc());
	}
    return 0;
}
