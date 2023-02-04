/**
 * 给定只含有1和-1的数组，要求只操作一次，选择相邻的两个数翻转一下。
 * 问操作后的数组和最大是多少
 * 显然枚举一下，找到2个-1就可以翻转。要么就是一正一负
 * 最后实在不行，就只能翻两个正1了。
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
int const SIZE = 810;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<llt>;
using pii = pair<int, int>;
using vpii = vector<pii>;

int N;
vi A;

int proc(){
    int ans = 0;
    int c2 = 0, c1 = 0;
    for(int i=0;i<N;++i){
        ans += A[i];
        if(i + 1 < N){
            if(-1 == A[i] && -1 == A[i + 1]){
                c2 = 1;
            }
            if(A[i] * A[i + 1] == -1){
                c1 = 1;
            }
        }
    }
    if(1 == c2) return ans + 4;
    if(1 == c1) return ans;
    return ans - 4;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
    while(nofkase--){
        A.assign(N=getInt(), 0);
        for(auto & i : A) i = getInt();
        printf("%d\n", proc());
    }
    return 0;
}