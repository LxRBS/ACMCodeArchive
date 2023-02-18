/**
 * 给定A、B两个数组，Ai和Bi代表第i个区间的中心，A中的区间跨度为W，B中的区间宽度为H，H<=W
 * 问能否移动B数组，使得每个Bi都恰好在Ai之内，允许端点重合。
 * 首先将AB按第0个左端点对齐。此时允许向右移动的最大距离为 2 * (W - H)
 * 然后依次检查，记录一下允许向右移动的最大距离。同时还要记录一下需要向右移动的最大距离。
 * 然后需要向右移动的最大距离显然要大于等于允许向右移动的最大距离。
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
int const SIZE = 1E6+1;
#else
int const SIZE = 1E6+1;
#endif

using llt = long long;
using vll = vector<llt>;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

int N, W, H;
vll A, B;

bool proc(){
    auto cha = A[0] - B[0];
    B[0] += cha;
    for(int i=1;i<N;++i) B[i] += cha;

    llt right = 2 * (W - H);
    llt h2 = H + H;
    llt w2 = W + W;
	llt need = 0LL;
    for(int i=1;i<N;++i){
        if(B[i] + h2 > A[i] + w2) return false;
        llt houxuan = A[i] + w2 - (B[i] + h2);
        if(A[i] > B[i]){
            need = max(need, A[i] - B[i]);
			if(need > right) return false;
        }else{
            right = min(right, houxuan);
        }
    }
	if(need > right) return false;
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        A.assign(N = getInt(), 0);
        B.assign(N, 0);
        W = getInt(); H = getInt();
        for(auto & a : A) a = getInt() - W;
        for(auto & a : B) a = getInt() - H;
        puts(proc()?"YES":"NO");
    }

    return 0;
}