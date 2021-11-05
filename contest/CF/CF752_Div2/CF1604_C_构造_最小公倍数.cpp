/**
 * 给定一个数组，每次操作可以从中选定ai，如果ai不是i+1的倍数，则可以将ai删掉
 * 问能否经过若干次操作，将数组清空。
 * 如果ai全是奇数，每次都删掉第一个数即可。
 * 如果a1是偶数，则不能删，直接no
 * 如果a2是2和3的倍数，则不能删，直接no
 * 依次类推
 * 如果ai包含2~i+1的因子，则ai不能删
 * 因此需要检测ai%lcm(2...i+1)是否为0
 * 另外lcm超过max(ai)就不需要再计算了
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
int const SIZE = 21;
#else 
int const SIZE = 100010;
#endif

#define fi first
#define se second

typedef long long llt;

int N;
int A[SIZE];

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

inline llt lcm(llt a, llt b){
	return a / gcd(a, b) * b;
}

bool proc(){
	if(A[1]%2==0) return false;

	bool flag = true;
    for(int i=1;i<=N;++i){
		if(A[i]%2 == 0){
            flag = false;
			break;
		}
	}
	if(flag) return true;
	
	llt a = 1;
	int m = *max_element(A+1, A+N+1);
	for(int i=1;i<=N;++i){
		if(a<=m) a = lcm(a, i + 1);
		if(A[i]%a == 0) return false;
	}
	return true;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		for(int i=1;i<=N;++i)A[i] = getInt();
		puts(proc()?"YES":"NO");
	}
	return 0;
}