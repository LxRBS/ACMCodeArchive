/**
 * 给定长度为N的数组A，在A[1...i]等概率重复抽样两个数，记作x和y
 * 求max(x, y)的期望
 * 需要对每一个i=1,2,...,N均回答上述问题，因此一共是N个答案
 * 所有计算在模意义下
 * 对于前i个数，Ei=SS{max(Ax, Ay)}/(i*i)
 * 令Di=SS{max(Ax, Ay)}，可以发现Di由三部分组成
 * Di = D[i-1] + A[i] + 2 * (c * A[i] + s)
 * 其中c是A[1...i-1]中小于等于Ai的数的数量，s是该区间中大于Ai的所有元素之和
 * c和s分别用两个树状数组维护即可
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
int const SIZE = 23;
#else
int const SIZE = 2E5+13;
#endif

using llt = long long int;
llt const MOD = 998244353LL;

llt powerMod(llt a,llt n,llt mod){
    llt ret = 1;
    a %= mod;

    while( n ){
        if ( n & 1 ) ret = ret * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return ret;
}


inline llt inv(llt a){return powerMod(a, MOD-2, MOD);}

inline llt add(llt a, llt b){return (a+b)%MOD;}
inline llt add(llt a, llt b, llt c){return (a+b+c)%MOD;}
inline llt mul(llt a, llt b){return a*b%MOD;}


struct Bit{

int _n;
llt c[SIZE];

void init(int n){this->_n = n; fill(this->c, this->c+n+1, 0LL);}

void modify(int pos, llt delta){
    for(int i=pos;i<=this->_n;i+=lowbit(i)) this->c[i] += delta;
}

llt query(int pos){
    llt ans = 0;
    for(int i=pos;i;i-=lowbit(i)) ans += this->c[i];
    return ans;
}

llt query(int s, int e){return this->query(e) - this->query(s-1);}

static int lowbit(int x){return x & -x;}

};

int N;
llt A[SIZE];
llt D[SIZE];

Bit U, V;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    N = getInt();
    llt maxv = 0;
    for(int i=1;i<=N;++i) maxv = max(maxv, A[i] = getInt());

    U.init(maxv);
    V.init(maxv);

    printf("%lld\n", D[1] = A[1]);
    U.modify(A[1], 1);
    V.modify(A[1], A[1]);
    
    for(int i=2;i<=N;++i){
        llt c = U.query(A[i]); // 小于等于Ai的数量
        llt s = V.query(A[i]+1, maxv); // 大于等于Ai的所有数之和
        D[i] = mul(2LL, add(mul(c, A[i]), s));
        D[i] = add(D[i], A[i], D[i-1]);
        llt ans = mul(D[i], inv(mul(i, i)));
        printf("%lld\n", ans);
        U.modify(A[i], 1);
        V.modify(A[i], A[i]);
    }
    return 0;
}