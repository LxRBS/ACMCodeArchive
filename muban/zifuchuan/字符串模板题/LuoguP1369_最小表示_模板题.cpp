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

namespace ZIFUCHUAN{

/// 返回具体begin的位置，begin传指针
template<typename IT>
int minRepresentation(IT begin, int n){
    int i = 0, j = 1, k = 0;
    while(i < n && j < n && k < n){
        while(k < n && *(begin + (i + k) % n) == *(begin + (j + k) % n)) ++k;
		if(k == n) break;
		
		if(*(begin + (i + k) % n) < *(begin + (j + k) % n)) j += k + 1;
		else i += k + 1;
		if(i == j) ++i;
		k = 0;
	}
    return min(i, j);
}

}

int N;
vector<int> A;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
    using namespace IO;
    A.assign(N=getInt(), 0);
	for(auto & i : A) i = getInt();
    int s = ZIFUCHUAN::minRepresentation<int*>(A.data(), N);
	for(int i=0;i<N;++i) printf("%d ", A[(s+i)%N]);
	printf("\n");
    return 0;
}