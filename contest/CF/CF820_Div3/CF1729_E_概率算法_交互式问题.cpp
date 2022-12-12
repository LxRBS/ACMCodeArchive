/**
 * 长度为n的环，每次允许问一个问题： x y
 * 即x和y的间距。因为是环，所以存两种可能，计算机会随机回答一种
 * 但是一旦回答，(x, y)的答案就会被固定下来
 * 但是(x, y)与(y, x)的答案是独立的。
 * 如果x和y任意一个超过n，则返回-1
 * 要求在50次询问中正确回答n是多少
 * 考虑问(1, x)和(x, 1)，则有50%的机会得到不一样的答案，此时x+y就是正确答案
 * 一共可以询问25次，因此得到正确答案的机会非常大
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

char getChar(){
	char ch = __hv007();
	while(!islower(ch)) ch = __hv007();
	return ch;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 5e5+5;
#endif

using llt = long long;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    llt n = 2;
	llt a, b;
	while(1){
		printf("? 1 %lld\n", n);
        fflush(stdout);
		scanf("%lld", &a);
		if(-1 == a){
			printf("! %lld\n", n - 1);		
			return 0;
		}

		printf("? %lld 1\n", n);
		fflush(stdout);
		scanf("%lld", &b);
		if(-1 == b){
			printf("! %lld\n", n - 1);		
			return 0;
		}
		if(a != b){
			printf("! %lld\n", a + b);		
			return 0;
		}
		++n;
	}
    return 0;
}