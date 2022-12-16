/**
 * 两个电梯，一个在a，一个在b，但是要先去c
 * 问哪个电梯先回1层
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

#ifndef ONLIE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 2E5+10;
#endif


using pii = pair<int, int>;
using vpii = vector<pii>;
using vi = vector<int>;
using vvpii = vector<vpii>; 

int proc(int a, int b, int c){
    if(b > c){
        if(a > b) return 2;
        if(a < b) return 1;
        return 3;
    }

    int tmp = c - b + c;
    if(a > tmp) return 2;
    if(a < tmp) return 1;
    return 3;
}


int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    int nofkase = getInt();
    while(nofkase--){
        int a = getInt();
        int b = getInt();
        int c = getInt();
        printf("%d\n", proc(a, b, c));
    }
    return 0;
}