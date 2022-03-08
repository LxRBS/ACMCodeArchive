/**
 * 前A名，肯定发衣服。B名以后肯定没有衣服
 * AB之间选C个人等概率的发衣服
 * 问第X名拿到衣服的概率是多少。
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
int const SIZE = 100010;
#endif

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int a = getInt();
	int b = getInt();
	int c = getInt();
	int x = getInt();
	if(x <= a) {
		puts("1"); return 0;
	}
	if(x > b){
		puts("0"); return 0;
	}
	printf("%.12f\n", 1.0*c/(b-a));
    return 0;
}