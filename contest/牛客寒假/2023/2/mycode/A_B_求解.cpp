/**
 * 给定区间[A, B]和[C, D]以及N，从两个区间各挑一个数，使得和为N
 * 问一共有多少对。用区间[N-B, N-A]交[C, D]即可 
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
int const SIZE = 110;
#endif

using llt = long long;

llt N;
llt A, B, C, D;

llt inter(llt a, llt b, llt c, llt d){
    assert(a <= b && c <= d);
    if(c > b) return 0;
    if(a > d) return 0;
    auto s = max(a, c);
    auto e = min(b, d);
    return e - s + 1;
}

llt proc(){
    llt x = max(0LL, N - B);
    llt y = max(0LL, N - A);
    auto t = inter(x, y, C, D);
    return t;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // int nofkase = getInt();
    int nofkase; cin >> nofkase;
    while(nofkase--){
        // N = getInt();
        // A = getInt(); B = getInt();
        // C = getInt(); D = getInt();
        cin >> N >> A >> B >> C >> D;
        // printf("%lld\n", proc());
        cout << proc() << endl;
    }
    return 0;
}


