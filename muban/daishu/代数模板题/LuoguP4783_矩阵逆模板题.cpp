#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>
using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

namespace IO{

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

using llt = long long;

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;    
}

char getChar(function<bool(char)> ok){
    char ch = __hv007();
    while(!ok(ch)) ch = __hv007();
    return ch;
}

}


namespace DAISHU{

using llt = long long;
llt const MOD = 1000000007LL;

llt qpow(llt a, llt n){
	llt ret = 1LL;
	a %= MOD;
	while(n){
		if(n & 1) (ret *= a) %= MOD;
		(a *= a) %= MOD;
		n >>= 1;
	}
	return ret;
}

inline llt inv(llt a){return qpow(a, MOD-2LL);}

/// 矩阵求逆, src的元素保证在[0, MOD)之间
/// 函数结束, ret为结果, src会变为单位阵 
/// 使用vector需要做一些常数时间加速，否则会T 
int invAss(vector<vector<llt>> & a){
	auto n = a.size();
	vector<vector<llt>> b(n, vector<llt>(n, 0));
	for(int i=0;i<n;++i) b[i][i] = 1;

    for(int row=0;row<n;++row){
        //整型不需要找列主元，只需找非零元即可
        int maxr = row;
        while(maxr < n && 0 == a[maxr][row]) ++maxr;
        //无解
        if(n == maxr) return 0;
        //交换
        if(row != maxr) a[row].swap(a[maxr]), b[row].swap(b[maxr]);
        
        //求逆元
        auto tmp = inv(a[row][row]);
        //更新当前行
		auto * arow = a[row].data();
		auto * brow = b[row].data();
        for(int j=0;j<n;++j){
			(*(arow + j) *= tmp) %= MOD;
			(*(brow + j) *= tmp) %= MOD;
        }
        //更新其余行
        for(int i=0;i<n;++i)if(i!=row){
            // auto & ai = a[i];
			// auto & bi = b[i];
			/// 换成指针访问，比直接方括号要快，
			/// 方括号比迭代器要快
			auto * ai = a[i].data();
			auto * bi = b[i].data();
            auto tt = MOD - ai[row];
			for(int j=0;j<n;++j){
				(*(ai + j) += *(arow + j) * tt % MOD) %= MOD;
				(*(bi + j) += *(brow + j) * tt % MOD) %= MOD;
            }
        }
    }
	a.swap(b);
    return 1;
}


}

#ifndef ONLINE_JUDGE
int const SZ = 130;
#else
int const SZ = 1E6+13;
#endif

int N;
vector<vector<long long>> A, B;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
    using namespace IO;
	N = getInt();
	A.assign(N, vector<long long>(N, 0));
	for(auto & vec : A)for(auto & i : vec) i = getInt();
	bool b = DAISHU::invAss(A);
	if(0 == b) return printf("No Solution\n"), 0;
	for(auto & vec : A){for(auto & i : vec)printf("%lld ", i);printf("\n");}
	return 0;
}