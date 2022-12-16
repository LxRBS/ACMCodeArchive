/**
 *  对于给定的数组，选定一个x，对每个Ai做如下操作 Ai = |Ai - x| + x
 *  操作完以后要使得数组的严格局部小最少，问这个最少是多少
 *  局部小就是指Ai<A[i-1]且Ai<A[i+1]
 *  对每一个Ai，i = 2...N-1，都有一个或者两个区间[s, e]使得其不为局部小
 *  然后用一个离散化的线段树，求出全区间的最大值，用N-2剪一下即可
 *  计算区间有更简单的方法，其实可以不用线段树 
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

#ifndef ONLIE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 2E5+10;
#endif


using pii = pair<int, int>;
using vpii = vector<pii>;
using vi = vector<int>;
using vvpii = vector<vpii>;

struct SegmentTree{

int n;
vi st;
vi lazy;

static int lson(int x){return x<<1;}
static int rson(int x){return lson(x) | 1;}

void init(int nn){
    this->st.assign((n = nn) + 1 << 2, 0);
    this->lazy.assign(n+1<<2, 0);
}

void _update(int t, int d){
    this->st[t] += d;
    this->lazy[t] += d;
}

void _pushUp(int t){
    this->st[t] = max(st[lson(t)], st[rson(t)]);
}

void _pushDown(int t){
    int & z = this->lazy[t];
    if(0 == z) return;

    this->_update(lson(t), z);
    this->_update(rson(t), z);

    z = 0;
}

void modify(int t, int s, int e, int a, int b, int d){
    if(a <= s && e <= b){
        this->_update(t, d);
        return;
    }
    this->_pushDown(t);
    int m = (s + e) >> 1;
    if(a <= m) this->modify(lson(t), s, m, a, b, d);
    if(m < b) this->modify(rson(t), m+1, e, a, b, d);
    this->_pushUp(t);
    return;
}

int query(int t, int s, int e, int a, int b){
    if(a <= s && e <= b){
        return this->st[t];
    }
    this->_pushDown(t);
    int m = (s + e) >> 1;
    int ans = 0;
    if(a <= m) ans = this->query(lson(t), s, m, a, b);
    if(m < b) ans = max(ans, this->query(rson(t), m+1, e, a, b));
    return ans;
}

};

int const INF = 2000000000;
int N;
vi A;
vpii B;
SegmentTree St;

bool proc(int a, int b, int c, vpii & v){
    v.clear();
    if(a == b || b == c) return v.emplace_back(-INF, INF), true;
    if(a == c){
        int e = a + b;
        if(b < a){
            if(e & 1) e = e / 2 + 1;
            else e = e / 2;
            return v.emplace_back(e, INF), true;            
        }
        e = e / 2;
        return v.emplace_back(-INF, e), true;
    }
    if(a > c) swap(a, c);
    if(b < a){
        int e = a + b;
        if(e & 1) e = e / 2 + 1;
        else e = e / 2;
        return v.emplace_back(e, INF), true;
    }
    if(b > c){
        int e = b + c;
        e = e / 2;
        return v.push_back({-INF, e}), true;
    }
    int e = a + b;
    e = e / 2;     
    v.push_back({-INF, e});
    
    e = b + c;
    if(e & 1) e = e / 2 + 1;
    else e = e / 2;
    v.push_back({e, INF});

    return true;
}

int proc(){
    B.clear(); B.reserve(N);
    for(int i=1;i<N-1;++i){
        vpii tmp;
        if(proc(A[i-1], A[i], A[i+1], tmp)){
            B.insert(B.end(), tmp.begin(), tmp.end());
        }         
    }
    // 离散化
    vi w;
    w.reserve(B.size() * 6 + 100);
    w.push_back(-INF-1);
    for(const auto & p : B){
        w.push_back(p.first);
        w.push_back(p.second);
    }
    sort(w.begin(), w.end());
    w.erase(unique(w.begin(), w.end()), w.end());
    // 线段树
    int n = w.size() - 1;
    St.init(n);
    for(const auto & p : B){
        int a = lower_bound(w.begin(), w.end(), p.first) - w.begin();
        int b = lower_bound(w.begin(), w.end(), p.second) - w.begin();
        St.modify(1, 1, n, a, b, 1);
    }
    int ans = N - 2;
    return ans - St.query(1, 1, n, 1, n);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    int nofkase = getInt();
    while(nofkase--){
        A.assign(N = getInt(), 0);
        for(int & i : A) i = getInt();
        printf("%d\n", proc());
    }
    return 0;
}

