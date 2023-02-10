/**
 * 有一个数组A，Ai在[1, 6]，已知其和是S，拿掉一个最大值后，其和为R
 * 构造数组A。
 * 令A0 = S - R
 * 然后剩下的数与A0维持在[1, A0]之间即可
 */
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

using llt = long long;
using vll = vector<llt>;
using vvll = vector<vll>;
using v3ll = vector<vvll>;
using si = set<int>;

using namespace IO;

int N, S, R;
vector<int> A;

int proc(){
    A.assign(N, 0);
    A[0] = S - R;
    int t = R / (N - 1);
    int left = R % (N - 1);
    for(int i=1;i<=left;++i) A[i] = t + 1;
    for(int i=left+1;i<N;++i) A[i] = t;
    assert(accumulate(A.begin(), A.end(), 0) == S);
    for(int i=0;i<N;++i) printf("%d%c", A[i], (N-1==i?'\n':' '));
    return 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // int nofkase; cin >> nofkase;
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        S = getInt();
        R = getInt();
        proc();          
    }
    return 0;
}