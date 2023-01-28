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

llt MOD = 0;

/// 求行列式a的值，会改变a的内容
llt determinant(vector<vector<llt>> & a){
    llt ret = 1;
    auto n = a.size();

    for(int i=0;i<n;++i){
		auto * ai = a[i].data();
    	for(int j=i+1;j<n;++j){
			auto * aj = a[j].data();
			auto & aji = *(aj + i);
    		while(aji){
    			auto t = *(ai + i) / aji;
    			for(int k=i;k<n;++k){
					/// 复合赋值更加耗时，导致T
    				// (*(ai + k) -= t * *(aj + k) % MOD) %= MOD;
					*(ai + k) = (*(ai + k) - *(aj + k) * t) % MOD;
				}
				for(int k=i;k<n;++k) swap(*(ai + k),*(aj + k));
				ret = -ret;
			}
		}

		if(0 == *(ai + i)) return 0;
		ret = ret * *(ai + i) % MOD;
	}

	// for(int i=0;i<n;++i) (ret *= a[i][i]) %= MOD;
	if(ret < 0) ret += MOD;
	return ret;
}



}

int N;

vector<vector<long long>> A;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
    using namespace IO;
	N = getInt();
    A.assign(N, vector<long long>(N, 0));
	DAISHU::MOD = getInt();
	for(auto & vec : A)for(auto & i : vec) i = getInt() % DAISHU::MOD;
    auto ans = DAISHU::determinant(A);
	cout << ans << endl;
    return 0;
}