/**
 * 给定一个数组A，每次操作可以选择一个Ai，令其Ai = Ai / 2
 * 欲使A之和为偶数，问最少操作多少次。
 * 如果本来就是偶数，返回0即可。
 * 否则找到一个Ai，用最少的次数改变其奇偶性即可。
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
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using vpii = vector<pii>;

int N;
vi A;

int f(int x){
	int ans = 0;
	while(1){
		++ans;
		int t = x - x / 2;
		if(t & 1) return ans;
	    x /= 2;
	}
	return -1;
}

int proc(){
	int sum = accumulate(A.begin(), A.end(), 0);
	if(sum % 2 == 0) return 0;

	int ans = 2000000000;
	for(int i : A){
		ans = min(ans, f(i));
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt(); 
	while(nofkase--){
        A.assign(N=getInt(), 0);
		for(int & i : A) i = getInt();
		printf("%d\n", proc());
	}

    return 0;
}


