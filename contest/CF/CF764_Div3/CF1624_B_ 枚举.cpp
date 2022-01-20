/**
 * 给定abc，问能否将其中一个数倍乘任意正整数，从而使得abc形成等差数列
 * 固定2个数，即可知道第3个数。枚举判定3次即可。
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 55;
#endif

typedef long long int llt;

llt A, B, C;

bool isA(){
    llt d = C - B;
    llt a = B - d;
    return a % A == 0 && a / A > 0;
}

bool isB(){
    llt d = C - A;
    if(d&1) return false;
    d = d >> 1;
    llt b = A + d;
    return b % B == 0 && b / B > 0;
}

bool isC(){
    llt d = B - A;
    llt c = B + d;
    return c % C == 0 && c / C > 0;
}

bool proc(){
    if(isA()) return 1;
    if(isB()) return 1;
    if(isC()) return 1;
    return 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getUnsigned();
    while(nofkase--){
        A = getUnsigned();
        B = getUnsigned();
        C = getUnsigned();
        puts(proc()?"YES":"NO");
    }
    return 0;
}
