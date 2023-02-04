/**
 * 给一个数组，选K对数，使得K对数的乘积的和最大。
 * 显然大数应该跟大数配对。此题有负数，因此将正数分一堆，负数分一堆
 * 然后排个序。根据当前对的乘积的大小依次取即可。
 * 最后如果还没有取完，有两种情况，如果有0，则肯定可以去跟0配对。
 * 否则正数和负数必然是各剩下最后一个，只能配对这个。
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


using llt = long long;
using vll = vector<llt>;

int N, K;
vll A, B;
int Zcnt = 0;

inline llt f(int pos, const vll & vec){
    assert(pos + 1 < vec.size());
    return vec[pos] * vec[pos + 1];
}

llt proc(){
    sort(A.begin(), A.end(), greater<llt>());
    sort(B.begin(), B.end());

    llt ans = 0;
    int k = 0;
    int an = A.size(), bn = B.size();
    int ai = 0, bi = 0;
    while(ai + 1 < an && bi + 1 < bn){
        auto at = f(ai, A);
        auto bt = f(bi, B);
        if(at >= bt){
            ai += 2;
            ans += at;
        }else{
            bi += 2;
            ans += bt;
        }
        if(++k == K) break;
    }
    
    if(k != K){
        while(ai + 1 < an){
            auto at = f(ai, A);
            ai += 2;
            ans += at;
            if(++k == K) break;
        }        
    }

    if(k != K)while(bi + 1 < bn){
        auto bt = f(bi, B);
        bi += 2;
        ans += bt;
        if(++k == K) break;
    }

    if(k == K) return ans;

    if(Zcnt){
        return ans;
    }
    ans += A[ai] * B[bi];
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // test();
    N = getInt(); K = getInt();
    A.reserve(N);  B.reserve(N);
    for(int a,i=0;i<N;++i){
        a = getInt();
        if(a > 0) A.push_back(a);
        else if(a < 0) B.push_back(a);
        else ++Zcnt;
    }
    printf("%lld\n", proc());
    return 0;
}