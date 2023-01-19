/**
 * 给定N长度的数组，求SIGMA{SIGMA{max(|Ai - Aj|, |Ai + Aj|)}}
 * 简单推理就能发现将Ai全部变成正的，然后计算SIGMA{SIGMA{Ai + Aj}}即可
 * 再推理一下发现: 原式 = 2 * N * SIGMA{Ai} 
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
using vi = vector<int>;

inline int ABS(int x){return x>=0?x:-x;}

int N;
vi A;

llt proc(){
    return 2LL * (llt)N * accumulate(A.begin(), A.end(), 0LL);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int nofkase = getInt();
    // int nofkase; cin >> nofkase;
    while(nofkase--){
        A.assign(N=getInt(), 0);
        for(int & i : A) i = ABS(getInt());
        printf("%lld\n", proc());
    }
    return 0;
}


