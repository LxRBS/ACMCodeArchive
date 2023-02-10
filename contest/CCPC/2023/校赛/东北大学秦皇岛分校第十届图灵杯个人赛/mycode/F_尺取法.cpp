/**
 * 给定01数组，选择一段区间，0的数量不超过m个，1的数量最大，
 * 问这个最大是多少
 * 基于贪心，答案区间必然是1开头1结尾。设置两个指针然后移动即可。
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
int const SIZE = 133;
#else
int const SIZE = 1E6+10;
#endif

using vi = vector<int>;

int N, M;
vi A;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    A.assign(N=getInt(), 0);
    M = getInt();
    for(int & i : A) i = getInt();
    
    int ans = 0;
    int s = 0, e = 0;
    int k = 0;
    while(e < N){
        if(0 == A[e] && ++k == M + 1) break;
        ++e;
    }
    if(e == N) return cout << e - s - k << endl, 0;

    ans = e - s - M;

    while(1){
        while(s < N && A[s] != 0) ++s;
        if(s == N) break;
        assert(A[s] == 0);
        s += 1;

        e += 1;
        while(e < N && A[e] != 0) ++e;
        ans = max(ans, e - s - M);
        if(e == N) break;
    }
    cout << ans << endl;
    return 0;
}