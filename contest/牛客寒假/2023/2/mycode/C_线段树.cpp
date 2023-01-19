/**
 * 给定N和M个区间，选两个区间，各挑一个数，使得和等于N
 * 问一共有多少种选法。标程是O(N+M)的方法。
 * 这里用线段树暴力求解。
 * 对给定区间[L, R]，可以求出满足的条件的最大区间[N-R, N-L]，
 * 然后看这个最大区间与其他区间有多少个交即可。
 * 纯暴力法要O(M)，因此需要将其变为对数时间，很自然用线段树。
 * 对每个区间[L, R]，成段加1。
 * 然后for每个区间[Li, Ri]:
 *   首先将[Li, Ri]成段减1
 *   然后查询[N-Ri, N-Li]的区间和，为本区间的答案，累加进最终答案
 *   再将[Li, Ri]加回去即可
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

vector<llt> St;
vi Lazy;

void build(int n){
    St.assign(n * 4 + 10, 0LL);
    Lazy.assign(n * 4 + 10, 0);
}

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

inline void _pushUp(int t){
    St[t] = add(St[lson(t)], St[rson(t)]);
}

inline void _pushDown(int t, int s, int e){
    auto & lazy = Lazy[t];
    if(0 == lazy) return;

    int mid = (s + e) >> 1;
   
    int lchild = lson(t);
    Lazy[lchild] += lazy;
    (St[lchild] += (llt)lazy * (mid - s + 1) % MOD) %= MOD;    

    int rchild = rson(t);
    Lazy[rchild] += lazy;
    (St[rchild] += (llt)lazy * (e - mid) % MOD) %= MOD;

    lazy = 0;
}

void modify(int t, int s, int e, int a, int b, int d){
    if(a <= s && e <= b){
        Lazy[t] += d;
        (St[t] += (llt)d * (e - s + 1) % MOD) %= MOD;
        return;
    }
    _pushDown(t, s, e);
    int mid = (s + e) >> 1;
    if(a <= mid) modify(lson(t), s, mid, a, b, d);
    if(mid < b) modify(rson(t), mid+1, e, a, b, d);
    _pushUp(t);
    return;
}

llt query(int t, int s, int e, int a, int b){
    if(a <= s && e <= b){
        return St[t]; 
    }
    _pushDown(t, s, e);
    int mid = (s + e) >> 1;
    llt ans = 0;
    if(a <= mid) (ans += query(lson(t), s, mid, a, b)) %= MOD;
    if(mid < b) (ans += query(rson(t), mid+1, e, a, b)) %= MOD;
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    // int nofkase; cin >> nofkase;
    // int nofkase = getInt();
    // while(nofkase--){
        
    // }
    vector<pair<int, int>> vec;

    int n = getInt();
    int m = getInt();
    build(n);

    auto f = [&n](const pii & p)->pair<int, int>{
        assert(p.first <= p.second);
        int a = n - p.second;
        int b = n - p.first;
        if(b <= 0) return {0, 0};
        if(a <= 0) a = 1;
        return {a, b};
    };

    for(int a,b,i=0;i<m;++i){
        a = getInt();
        b = getInt();
        if(a > n) {
            vec.emplace_back(0, 0);
            continue;
        }
        if(b > n) b = n;
        modify(1, 1, n, a, b, 1);
        vec.emplace_back(a, b);
    }

    llt ans = 0LL;
    for(int a,b,i=0;i<m;++i){
        if(0 == vec[i].first){ 
            assert(0 == vec[i].second);
            continue;
        }
        auto p = f(vec[i]);
        if(0 == p.first){
            assert(0 == p.second);
            continue;
        }
        modify(1, 1, n, vec[i].first, vec[i].second, -1);
        auto tmp = query(1, 1, n, p.first, p.second);
        if(tmp < 0) tmp += MOD;
        (ans += tmp) %= MOD;
        modify(1, 1, n, vec[i].first, vec[i].second, +1);
    }
    cout << ans << endl;
    return 0;
}


