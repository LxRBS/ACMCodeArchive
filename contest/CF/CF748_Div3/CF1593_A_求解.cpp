/**
 * A/B/C代表三个人的得票数，问每个人要想获胜，分别要加多少票，至少。
 * 如果A是最大，则加0；如果A是并列最大，则加1即可
 * 否则，A要加到比最大还多1
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

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 200010;
#endif

llt A[3], B[3];
void proc(){
    const llt m = *max_element(A, A+3);
    int cnt = 0;
    for(int i=0;i<3;++i)if(m==A[i])++cnt;

    cnt = (cnt > 1) ? 1 : 0;
    for(int i=0;i<3;++i){
        B[i] = m == A[i] ? cnt : m - A[i] + 1;
        printf("%lld ", B[i]);
    }
    puts("");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
        for(int i=0;i<3;++i) A[i] = getInt();
        proc();
	}
    return 0;
}