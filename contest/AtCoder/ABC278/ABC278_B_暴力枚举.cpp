/**
 * 对于hh:mm时刻，如果h2和m1互换，仍然是一个合法的时刻，则称为迷惑时刻。
 * 给定当前时刻hh:mm，问从当前时刻开始的第一个遇到的迷惑时刻是多少
 * 直接循环判断即可
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
int const SIZE = 2E5+13;
#endif

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    auto isOK = [](int h, int m)->bool{
        int h10 = h / 10;
        int h1 = h % 10;
        int m10 = m / 10;
        int m1 = m % 10;
        int th = h10 * 10 + m10;
        int tm = h1 * 10 + m1;
        if(0<=th&&th<24&&0<=tm&&tm<60) return true;
        return false;
    };
    int H, M; cin >> H >> M;
    while(1){
        if(isOK(H, M)) break;
        ++M;
        if(60 == M) {
            M = 0;
            ++H;
            if(24 == H) H = 0;
        }        
    }
    cout << H << " " << M << endl;
    return 0;
}
