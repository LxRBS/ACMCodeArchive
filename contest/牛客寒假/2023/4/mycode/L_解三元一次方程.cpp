/**
 * 根据题意就是求三元一次方程组
 * x + y = A
 * y + z = B
 * z + x = C
 * 的正整数解，且要求x、y、z能够构成三角形的边长
 * 显然 2 * (x + y + z) = A + B + C
 * 所以ABC之和必须是偶数，然后依次减去原方程就能得到xyz
 * 再判断一下三角形边长的条件即可。
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
int const SIZE = 3E5+10;
#endif

using llt = long long;

llt Va, Vb, Vc;


void proc(){
    auto total = Va + Vb + Vc;
    if(total & 1) return (void)printf("No\n");

    total >>= 1;

    auto la = total - Va;
    auto lb = total - Vb;
    auto lc = total - Vc;
    if(la <= 0 || lb <= 0 || lc <= 0) return (void)printf("No\n");
    auto mmax = max(la, max(lb, lc));
    auto mmin = min(la, min(lb, lc));
    auto mid = la + lb + lc - mmax - mmin;
    if(mid + mmin <= mmax) return (void)printf("No\n");
    printf("Yes\n%lld %lld %lld\n", la, lb, lc);
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
    while(nofkase--){
        Va = getInt(); Vb = getInt(); Vc = getInt();
        proc();
    }
    return 0;
}