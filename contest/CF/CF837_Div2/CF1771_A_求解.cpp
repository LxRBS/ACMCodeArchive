/**
 * 给定一个数组，A从中选一个数，B从中选另外一个数
 * 要求这两个数的差的绝对值达到最大，问一共有多少种不同的选法
 * 记录以下最小值和最大值的数量，如果最小值与最大值不同，
 * 答案就是2*Cmax*Cmin
 * 否则，答案就Cmax个数选2个做排列
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
int const SIZE = 13;
#else
int const SIZE = 35000;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;

int N;
vi Cnt;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	for(int kase=1;kase<=nofkase;++kase){
        N = getInt();
		Cnt.assign(100010, 0);
		int mn = 2000000000, mx = 0;
		for(int a,i=0;i<N;++i){
			++Cnt[a = getInt()];
			mn = min(mn, a);
			mx = max(mx, a);
		}
		if(mn != mx) printf("%lld\n", 2LL * Cnt[mn] * Cnt[mx]);
	    else printf("%lld\n", (Cnt[mn] - 1LL) * Cnt[mn]);
	}
    return 0;
}