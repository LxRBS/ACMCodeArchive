/**
 * N*N的方格，从(1, 1)开始走，只能向右或者向下，副对角线上任意格为终点
 * 有M个障碍点，M=10；问从起点到终点一共有多少条路径
 * M很小，显然要反过来考虑，考虑经过障碍点的路径一共有多少条
 * 然后显然要容斥。
 * 假设两点之间的坐标差分别是dx和dy，则两点之间的路径总数是C(dx + dy, dx)
 * 因为一共要走dx+dy步，其中必然要向右dx次，所以就是dx+dy步中选dx出来作为向右的即可
 * 再考虑到终点是副对角线，简单计算一下就发现任何点到终点的路径数量是2^(N + 1 - x - y)
 * 枚举障碍集合的子集，对每一个子集，按照先x后y的坐标进行排序，然后依次计算
 * 起点 -> 1 -> 2 -> 3 -> ... -> 终点 
 * 每一段的路径数量，乘起来可得经过此子集的路径条数，然后根据其内元素的数量，奇数加偶数减。
 * 如果存在某个点的y坐标比前面的小，则此段为0，显然总乘积也是0
 * 这样就能求出至少经过一个障碍的路径总数，而从起点到终点的路径总数是2^(N-1)
 * 相减即可。注意取模。
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
int const SIZE = 1E5+10;
#endif

using llt = long long;
using pii = pair<int, int>;
using vpii = vector<pii>;
using vll = vector<llt>;

llt const MOD = 1000000000+7LL;
inline llt add(llt a, llt b){return (a+b)%MOD;}
inline llt mul(llt a, llt b){return a * b % MOD;}
inline llt mul(llt a, llt b, llt c){return a * b % MOD * c % MOD;}

llt qpow(llt a, llt n){
    llt ret = 1;
    while(n){
        if(n & 1) ret = ret * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return ret;
}
inline llt inv(llt a){return qpow(a, MOD-2LL);}

int N, M;

vll Fac, IFac;

void init(){
    int n = N + 10;
    Fac.assign(n, 0LL);
    IFac.assign(n, 0LL);
    Fac[0] = Fac[1] = 1LL;
    for(int i=2;i<n;++i){
        Fac[i] = mul(i, Fac[i - 1]);
    }
    IFac[n-1] = inv(Fac[n-1]);
    IFac[0] = 1LL;
    for(int i=n-2;i>=1;--i){
        IFac[i] = mul(i + 1, IFac[i + 1]);
    }
    assert(IFac[1] == 1LL);
}

void test(){
    int n = 6;
    vector<vector<int>> d(n+1, vector<int>(n+1, 0));
    d[1][1] = 1;
    for(int i=1;i<=n;++i){
        for(int j=1;i+j<=n+1;++j)if(i!=1||j!=1){
            d[i][j] = d[i-1][j] + d[i][j-1];
        }
    }
    for(int i=1;i<=6;++i){
        for(int j=1;i+j<=n+1;++j){
            printf("%6d ", d[i][j]);
        }
        printf("\n");
    }
}

/// 组合数
inline llt C(int n, int m){
    return mul(Fac[n], IFac[m], IFac[n - m]);
}

inline llt f(const vector<pii> & vec){
    auto pre = vec[0];
    auto ret = C(pre.first + pre.second - 2, pre.first - 1);
    for(int i=1,n=vec.size();i<n;++i){
        const auto & p = vec[i];
        assert(pre.first <= p.first);
        if(! (pre.second <= p.second)) return 0;

        auto dx = p.first - pre.first;
        auto dy = p.second - pre.second;
        ret = mul(ret, C(dx + dy, dx));
        pre = p;
    }
    auto h = (N + 1) - (pre.first + pre.second);
    ret = mul(ret, qpow(2LL, h));
    return ret;
}

vpii Pos;

llt proc(int st){
    int sn = -1;
    vpii vec;
    for(int i=0;i<M;++i){
        if((1 << i) & st){
            vec.emplace_back(Pos[i]);
            sn = sn * -1;
        }
    }
    sort(vec.begin(), vec.end());
    auto ret = f(vec);
    return ret * sn;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // test();
    N = getInt(); M = getInt();
    init();
    Pos.assign(M, {});
    for(auto & p : Pos) p.first = getInt(), p.second = getInt();

    int status = 1 << M;

    llt ans = 0LL;
    for(int i=1;i<status;++i){
        ans = add(ans, proc(i));
    }

    llt total = qpow(2LL, N - 1);
    cout << ((total - ans) % MOD + MOD) % MOD << endl;
    return 0;
}