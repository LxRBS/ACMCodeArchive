/**
 * AB两个人，各有一个长度为N表示区间的序列
 * 初始两人手中各有一个空集，对每一个i：
 * 首先将当时的区间并到各自手里，然后问双方手里的序列，从1开始延伸，谁的能延伸最远
 * N在1E5，所以找一个O(NlogN)的算法即可，因此用线段树。由于区间范围在1E9所以需要离散化
 * 因为要考虑区间的连续性，所以离散化时，将每个区间端点的左右两端均塞进去。
 * 总数量最多在12E5。还是可以在O(NlogN)内。最后查询的时候还需要线段树上二分，因此是O(NlogNlogN)，时间凑合
 * 对每个区间，线段树上成段设置为1
 * 然后从1开始，二分查询最后一个最小值为1的位置，即为答案。
 * 因为加上下一个位置，最小值就变成了0，说明下一个位置没有连上。
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
using vvll = vector<vll>;
using pii = pair<int, int>;
using pll = pair<llt, llt>;
using vpii = vector<pii>;

struct _t{

int n;
vi st;
vi lazy;

static int lson(int t){return t<<1;}
static int rson(int t){return lson(t) | 1;}

void _pushUp(int t){
    st[t] = min(st[lson(t)], st[rson(t)]);
}

void _pushDown(int t){
    auto & lz = lazy[t];
    if(0 == lz) return;

    auto son = lson(t);
    st[son] = lazy[son] = lz;

    son = rson(t);
    st[son] = lazy[son] = lz;

    lz = 0;
}

void init(int nn){
    n = nn;
    st.assign((n<<2)+1, 0);
    lazy.assign((n<<2)+1, 0);
}

void modify(int t, int s, int e, int a, int b, int d){
    if(a <= s && e <= b){
        st[t] = lazy[t] = d;
        return;
    }
    int mid = (s + e) >> 1;
    _pushDown(t);
    if(a <= mid) modify(lson(t), s, mid, a, b, d);
    if(mid < b) modify(rson(t), mid+1, e, a, b, d);
    _pushUp(t);
}

int query(int t, int s, int e, int a, int b){
    if(a <= s && e <= b){
        return st[t];
    }

    int mid = (s + e) >> 1;
    _pushDown(t);   

    int ans = 20000000;
    if(a <= mid) ans = min(ans, query(lson(t), s, mid, a, b));
    if(mid < b) ans = min(ans, query(rson(t), mid+1, e, a, b));
    return ans;
}

int answer(){
    int left = 1, right = n, mid;
    do{
        mid = (left + right) >> 1;
        if(0 == query(1,1,n,1,mid)) right = mid - 1;
        else left = mid + 1;
    }while(left <= right);
    return right;
}


}Sha, Ya;

int N;
array<vpii, 2> A;
vi W;

int proc(const pii & cur, _t & st){
    int x = lower_bound(W.begin(), W.end(), cur.first) - W.begin();
    int y = lower_bound(W.begin(), W.end(), cur.second) - W.begin();
    st.modify(1, 1, st.n, x, y, 1);
    auto ans = st.answer();
    auto real_ans = W[ans];
    // printf("x = %d, y = %d, ans = %d, real_ans = %d\n", x, y, ans, real_ans);
    return real_ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt();
    auto & a = A[0];
    a.assign(N, {0, 0});
    auto & b = A[1];
    b.assign(N, {0, 0});
    W.reserve(N+N+1); W.push_back(0);
    for(auto & p : a){
        W.emplace_back(p.first = getInt());
        W.emplace_back(p.second = getInt());
        W.emplace_back(p.first - 1);
        W.emplace_back(p.first + 1);
        W.emplace_back(p.second - 1);
        W.emplace_back(p.second + 1);
    }
    for(auto & p : b){
        W.emplace_back(p.first = getInt());
        W.emplace_back(p.second = getInt());
        W.emplace_back(p.first - 1);
        W.emplace_back(p.first + 1);
        W.emplace_back(p.second - 1);
        W.emplace_back(p.second + 1);
    }

    sort(W.begin(), W.end());
    W.erase(unique(W.begin(), W.end()), W.end());

    auto n = W.size();
    Sha.init(n); Ya.init(n);

    for(int i=0;i<N;++i){
        const auto & pa = a[i];
        const auto & pb = b[i];
        auto sha = proc(pa, Sha);
        auto ya = proc(pb, Ya);
        if(sha == ya){
            printf("win_win!\n0\n");
        }else if(sha > ya){
            printf("sa_win!\n%d\n", sha - ya);
        }else{
            printf("ya_win!\n%d\n", ya - sha);
        }
    }
    return 0;
}