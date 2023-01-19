/**
 * 给定一个N长度的数组，将其分为K个非空子序列， 这个划分的分数定义为每个子序列唯一值的数量之和。
 * 对每一个k=1,2,...,N，问k划分的最大分数是多少。
 * 用贪心进行划分即可计数。
 * 考虑k划分，对于cnt[i]小于等于k的i，显然每个子序列各分一个即可。
 * 对于cnt[i]大于k的i，首先将k-1个i格子分到子序列，这些都能计分。剩下的塞到一个划分中，这些数不能计分。
 * 对cnt数组做一个哈希，然后对k做一个从1到N的循环，利用前缀和即可求出每个答案。
 * O(maxV + N)。
 * 也可以直接对cnt数组进行排序，O(NlogN)
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
using vpii = vector<pii>;

llt const MOD = 998244353LL;
inline llt add(llt a, llt b){return (a+b)%MOD;}

int N, P;
vi A;

void proc(){
    int total = 0;
    vi cnt(100000+10, 0);
    for(auto i : A) if(1 == ++cnt[i])++total;

    
    vi d(100000+10, 0);
    for(auto i : cnt) ++d[i];

    llt sum = 0;
    int pre = 0;
    for(int i=1;i<=N;++i){
        pre += d[i];
        auto ans = (llt)(total - pre) * (i - 1) + sum + (llt)i * d[i];
        printf("%lld\n", ans);
        sum += (llt)i * d[i];
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        A.assign(N = getInt(), 0);
        for(auto & i : A) i = getInt();
        proc();
    }
    return 0;
}


