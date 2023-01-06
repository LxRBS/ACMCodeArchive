/**
 * 给定N长度的排列A，以及一个整数K
 * 每一次操作，允许从A中任抽K个数，将其排序以后接在A后面
 * 问最少多少次操作能将A变得有序
 * 首先由于只能往后接，所以如果2在1前面，则2必须移动，如果2必须移动，则无论3在何处，3也必须移动
 * 因此，原A中从1开始的123...x数不用动，其余的数全都要移动
 * 其次，可以发现需要移动的数只要移动一次即可
 * 因此答案是 (N-x)/K +((N-x)%K?1:0)
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
int const SIZE = 130;
#else
int const SIZE = 2e5+5;
#endif

using Real = long double; 
using llt = long long;
using vi = vector<int>; 
using vvi = vector<vi>;
using vvvi = vector<vvi>;

int N, K;
vi A;

int proc(){
    int cnt = 0;
	int cur = 1;
	for(int i : A){
        if(i > cur) continue;
		assert(i == cur);
		++cnt; ++cur;
	}
	cnt = N - cnt;
	return cnt / K + (cnt % K ? 1 : 0);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        A.assign(N = getInt(), 0);
		K = getInt();
		for(int & i : A) i = getInt();
		printf("%d\n", proc());
    }
    return 0;
}