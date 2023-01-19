/**
 * 给定一个数组和P，对x=0,1,2,3...,P-1，求三元组(i, j, k)满足
 * 1 i,j,k互异
 * 2 (Ai*Aj+Ak) % P = x
 * 对每一个x，问满足条件的三元组的数量是多少。
 * 暴力法显然是O(N^3)。由于N、P均在5000，可以考虑平方算法。
 * 首先用O(N)可以求出Cnt1[Ai%P]
 * 然后用O(N^2)求出Cnt2[Ai*Aj%P]
 * 然后for i=0...P-1:
 *   再for k=0...P-1:
 *      Ans[k] = Cnt2[i] * Cnt1[k - i]
 * 此时统计了i==k或者j==k的情况，把这种情况从Ans中去掉即可，即要找出
 * (Ai * Aj + Ai) % P = x 的数量，直接暴力法即可
 * 总复杂度是O(N^2 + P^2 + N^2)。
 * 标程还提供了一种DP的做法。
 */
#include <bits/stdc++.h>
using namespace std;
 
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
 
#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 110;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

llt const MOD = 998244353LL;
inline llt add(llt a, llt b){return (a+b)%MOD;}

int N, P;
vi A;
vector<llt> Ans;
unordered_map<int, int> Map;
unordered_map<int, int> DD;

void proc(){
    for(int i=0;i<N;++i)for(int j=0;j<N;++j){
        if(i == j) continue;
        auto tmp = A[i] * A[j] % P;
        ++DD[tmp];
    }
    Ans.assign(P, 0LL);
    for(const auto & p : DD){
        auto tmp = p.first;
        for(int k=0;k<P;++k){
            auto t2 = (k - tmp + P) % P;
            auto it = Map.find(t2);
            if(it == Map.end()) continue;
            Ans[k] += (llt)p.second * (llt)it->second;
        }
    }
    for(int i=0;i<N;++i)for(int j=0;j<N;++j){
        if(i == j) continue;
        auto tmp = (A[i] * A[j] + A[i]) % P;
        Ans[tmp] -= 2;
    }

    for(llt i : Ans)printf("%lld ", i);
    printf("\n");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    A.assign(N = getInt(), 0);
    P = getInt();
    for(int i=0;i<N;++i){
        ++Map[A[i] = getInt() % P];
    }
    proc();
    return 0;
}


