/**
 * 题目很长，但是本质上就是对每一个位置有一个p属于[s, e]区间
 * 现在想将p移出区间，最少要多少次操作。区间整体和p都可以移动。
 * 两个方向，要么将p向前移，一定可以。要么将p向后移，同时区间整体向前移，需要判断一下。
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
int M;
int D;
vi P;
vi A;

int proc(int pos){
    auto ai = A[pos];
    auto aip = A[pos+1];
    auto pi = P[ai];
    auto pp = P[aip];
    if(pi >= pp || pp > pi + D) return 0;
    auto cha = pp - pi;
    auto tt = pi + D - pp + 1;
    if(cha < tt) return cha;   
    if(pi - 1 + N - pp >= tt) return tt;
    return cha;
}

int proc(){
    int ans = N + 4;
    for(int i=0;i+1<M;++i){
        ans = min(ans, proc(i));
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        M = getInt();
        D = getInt();
        P.assign(N + 1, 0);
        for(int i=1;i<=N;++i){
            P[getInt()] = i;
        }
        A.assign(M, 0);
        for(auto & i : A) i = getInt();
        printf("%d\n", proc());
    }
    return 0;
}