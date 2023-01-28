#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>
using namespace __gnu_pbds;


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
using vll = vector<llt>;
using vvll = vector<vll>;

llt const MOD = 1000000007LL;

/// a *= b，ab表示矩阵
void mulAss(vvll & a, const vvll & b){
    assert(a.size() == b.size());

	auto n = a.size();
	vvll r(n, vll(n, 0));
	//// 常数优化
	for(int i=0;i<n;++i){
		auto * ri = r[i].data();
		for(int k=0;k<n;++k){
            const auto aik = a[i][k];
		    const auto * bk = b[k].data();
		    for(int j=0;j<n;++j){
				(*(ri + j) += *(bk + j) * aik) %= MOD;
		    } 
		}
	}
	r.swap(a);
	return;
}

/// a = (a ^ n) a表示矩阵
void powAss(vvll & a, llt n){
    auto sz = a.size();

	vvll ret(sz, vll(sz, 0));
	for(int i=0;i<sz;++i) ret[i][i] = 1;

	while(n){
		if(n & 1) mulAss(ret, a);
		mulAss(a, a);
		n >>= 1;
	}
	ret.swap(a);
	return;
}


}


DAISHU::vvll A;
int N;
long long K;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
    using namespace IO;
	N = getInt(); K = getLL();
	A.assign(N, DAISHU::vll(N, 0));
	for(auto & vec : A)for(auto & i : vec) i = getInt();
	DAISHU::powAss(A, K);
	for(const auto & vec : A){for(const auto i : vec)printf("%lld ", i);printf("\n");}
    return 0;
}