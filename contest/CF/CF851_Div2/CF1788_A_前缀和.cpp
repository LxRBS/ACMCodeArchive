/**
 * 1和2的数组，问是否能够将数组分成两半，前一半的乘积等于后一般的
 * 只需要数一下2的数量即可。
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

using vi = vector<int>;

int N;
vi A;

int proc(){
    int c = 0, d = 0;
    for(int i=N-1;i>=0;--i)if(A[i] == 2) ++d;
    int k = -1;
    for(int i=0;i+1<N;++i){
        if(A[i] == 2) ++c, --d;
        if(c == d){
            k = i + 1;
            break;
        }
    }
    return k;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
    while(nofkase--){
        A.assign(N = getInt(), 0);
        for(int & i : A) i = getInt();
        printf("%d\n", proc());
    }
    return 0;
}