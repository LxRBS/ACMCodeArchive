/**
 * 交互式，有一个未知数N，每次询问可以给定一个t，返回t%N
 * N的范围在[1, 1E12]，要求在41次询问中求出N，并且每次询问的t是递增的
 * 很明显，可以二分。但是要求t递增，因此使用倍增。
 * 从1开始问，有两种结果，0或者1
 * 接着问2，有两种结果，0、2
 * 接着问4，有三种结果，0、1、4
 * 接着问8，有四种结果，0，1，2，3，8
 * 因此如果询问t的结果是x，且x!=t，则答案是 t - x
 * 否则将t乘2继续即可
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
int const SIZE = 23;
#else
int const SIZE = 2E5+10;
#endif

using pii = pair<int, int>;
using vpii = vector<pii>;
using vi = vector<int>;
using vs = vector<string>;
using vvs = vector<vs>;
using t3t = tuple<int, int, int>;
using vt3t = vector<t3t>;
using vvt3t = vector<vt3t>;
using si = set<int>;
using vsi = vector<si>;

using llt = long long;

bool check(llt x){
	printf("? %lld\n", x);
	fflush(stdout);

	llt r;
	scanf("%lld", &r);
	if(r == x) return true;
	return false;
}

int main(){
#ifndef ONLINE_JUDGE
    // freopen("1.txt", "r", stdin);
#endif
    llt t = 1;
	while(1){
		printf("? %lld\n", t);
		fflush(stdout);

		llt r;
		scanf("%lld", &r);

        if(t == r){
			t <<= 1;
			continue;
		}

		printf("! %lld\n", t - r);
		fflush(stdout);
		break;
	}
    return 0;
}
// 500000000001