/// 给定若干个区间，问将其连接所需的最短长度
/// 排个序，将没有覆盖的长度累加起来即可
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
int const SIZE = 106;
#else
int const SIZE = 1E6+7;
#endif

using llt = long long;
using pii = pair<int, int>;

pii A[SIZE];
int N;

llt proc(){
    sort(A, A+N);
    llt ans = 0;
    int k = 1;
    int cur = A[0].second;
    while(k < N){
        if(A[k].first > cur){
            ans += A[k].first - cur;            
        }
        cur = max(cur, A[k].second);
        ++k;
    }
    return ans; 
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    N = getInt();
    for(int r,a,i=0;i<N;++i) {
        r = getInt();
        a = getInt();
        A[i].first = r - a ;
        A[i].second = r + a;
    }
    cout << proc() << endl;
    return 0;
}