/**
 * 1~N的排列，每一轮得到一个新数组，新数组依次右老数组相邻的两个数加起来
 * 因此每轮均会少一个数。直到只剩一个数。
 * 问如何排使得数最大，并给出方案。
 * 小范围测试一下就知道奇数从小到大，然后偶数从大到小即可。
 * 由于N在1000，因此排出来以后可以暴力一下。
 * 找了一个递推公式。
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
int const SIZE = 1E6+10;
#endif

using llt = long long;
using pii = pair<int, int>;
using vpii = vector<pii>;
using vi = vector<int>;
vector<llt> Inv;

llt const MOD =  1000000000 + 7LL;

llt qpow(llt a, llt n){
    llt ret = 1;
    while(n){
        if(n & 1) ret = ret * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return ret;
}

llt inv(llt a){return qpow(a, MOD-2LL);}

inline llt add(llt a, llt b){return (a + b) % MOD;}
inline llt mul(llt a, llt b){return a * b % MOD;}
inline llt mul(llt a, llt b, llt c){return a * b % MOD * c % MOD;}

int N;
vi A;

llt f(){    
    if(1 == N) return 1;
    if(2 == N) return 3;
    if(3 == N) return 9;
    if(4 == N) return 24;
    vector<llt> d = {0, 1, 3, 9, 24};
    for(int i=5;i<=N;++i){
        auto t1 = mul(4LL, i - 1, d[i-1]);
        auto t2 = mul(12, d[i-2]);
        auto t3 = mul(16, 4 - i, d[i-3]);
        auto t4 = mul(16, i - 4, d[i - 4]);
        auto t = (t1 - t2 + t3 + t4) % MOD;
        t = mul(t, inv(i - 1));
        d.emplace_back(t);
    }
    auto ans = d[N];
    if(ans < 0) ans += MOD;
    return ans;
}

void proc(){
    if(N & 1){
        int k = 1;
        for(int i=1;i<=N;i+=2){
            A[k++] = i;
        }
        for(int i=N-1;i>0;i-=2){
            A[k++] = i;
        }
        assert(k == N + 1);
    }else{
        int k = 1;
        for(int i=1;i<=N;i+=2){
            A[k++] = i;
        }
        for(int i=N;i>0;i-=2){
            A[k++] = i;
        }
        assert(k == N + 1);
    }

    llt ans = f();
    printf("%lld\n", ans);
    for(int i=1;i<=N;++i)printf("%d%c", A[i], (i==N?'\n':' '));
    return;
}

void test(){
    auto f = [](vi vec)->llt{        
        while(vec.size() != 1){
            vi tmp;
            for(int i=0;i<vec.size()-1;++i){
                tmp.push_back(vec[i] + vec[i+1]);
            }
            tmp.swap(vec);
        }
        return vec[0];
    };
    
    for(int n=4;n<=10;++n){
        vi v;
        vi ret;
        llt ans = 0;
        for(int i=1;i<=n;++i)v.push_back(i);
        do{
            auto tmp = f(v);
            if(ans < tmp) ans = tmp, ret = v;
        }while(next_permutation(v.begin(), v.end()));
        printf("%d: %lld\n", n, ans);
        for(int i : ret) printf("%d ", i); printf("\n");        
    }
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // test();
    cin >> N;
    A.assign(N + 1, 0);
    proc();    
    return 0;
}