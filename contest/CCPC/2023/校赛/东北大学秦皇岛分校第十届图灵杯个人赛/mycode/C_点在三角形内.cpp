/**
 * 如题，算叉积即可
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
int const SIZE = 1E6+10;
#endif

using pii = pair<int, int>;

int cross(pii O, pii A, pii B){
    auto ax = A.first - O.first;
    auto ay = A.second - O.second;
    auto bx = B.first - O.first;
    auto by = B.second - O.second;
    return ax * by - bx * ay;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    pii A = {0, 0};
    pii B = {getInt(), 0};
    pii C;
    C.first = getInt(); C.second = getInt();
    pii D;
    D.first = getInt(); D.second = getInt();
    if(cross(D, A, B) > 0 && cross(D, B, C) > 0 && cross(D, C, A) > 0) puts("yes");
    else puts("no");
    return 0;
}