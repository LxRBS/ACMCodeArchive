/**
 * 字母表按 A,B,C,...,Z,AA,AB,AC,...,AZ,BA,...,ZZ,AAA,...
 * 的顺序排。给定一个字符串，问排第几位。
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 5500;
#endif

using llt = long long;

string S;
llt proc(){
    llt ans = 0;
    int n = S.length();
    llt tmp = 26LL;
    for(int i=1;i<n;++i){
        ans += tmp;
        tmp *= 26LL;
    }
    tmp /= 26;
    for(int i=0;i<n;++i){
        llt t = S[i] - 'A';
        ans += t * tmp;
        tmp /= 26LL;
    }
    return ans + 1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    cin >> S;
    cout << proc() << endl;
    return 0;
}


