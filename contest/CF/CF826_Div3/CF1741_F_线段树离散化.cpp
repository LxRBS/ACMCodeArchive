/**
 * 给定若干有颜色的区间，对每一个区间问：具体其最近的不同颜色的其他区间的距离是多少
 * 按左端点排序，然后从左到右扫描一遍，记录向右延伸最远的两个不同颜色的区间
 * 然后依次对当前区间，计算距离左端点最近的距离
 * 然后再反过来，计算右端点，注意到左右的流程是一致的，所以可以使用一个函数，
 * 只需把区间的左右坐标互换且变成负数即可
 * 这种流程相离、交叉的情况都能处理，但是包含的情况没有处理
 * 因此使用离散化线段树，专门考虑包含的情况即可
 * 对每一种颜色，将其所有段删除、再查询、再插入回来即可
 * 时间复杂度还是O(nlogn)，但是常数比标程大
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
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;

struct _t{
	int s;
	int e;
	int c;
	int pos;
};

int N;
vector<_t> T;
vi Ans;

void update(vi & d, int index){
	d.push_back(index);
	sort(d.begin(), d.end(), [&](int a, int b){
        if(T[a].c != T[b].c) return T[a].c < T[b].c;
		if(T[a].e != T[b].e) return T[a].e > T[b].e;
		if(T[a].s != T[b].s) return T[a].s < T[b].s;
		return T[a].pos < T[b].pos;
	});
    d.erase(unique(d.begin(), d.end(), [](int a, int b){return T[a].c==T[b].c;}), d.end());
    sort(d.begin(), d.end(), [&](int a, int b){
		if(T[a].e != T[b].e) return T[a].e > T[b].e;
		if(T[a].s != T[b].s) return T[a].s < T[b].s;
		if(T[a].c != T[b].c) return T[a].c < T[b].c;
		return T[a].pos < T[b].pos;
	});
	if(d.size() > 2) d.pop_back();
	return;
}

void proc2(){
	sort(T.begin(), T.end(), [](const _t & a, const _t & b){
		if(a.s != b.s) return a.s < b.s;
		if(a.e != b.e) return a.e < b.e;
		if(a.pos != b.pos) return a.pos < b.pos;
		return a.c < b.c;
	});	

	vi d;
	for(int i=0;i<N;++i){
		update(d, i);
        for(int j : d){
			if(T[i].c == T[j].c) continue;
            Ans[T[i].pos] = min(Ans[T[i].pos], max(0, T[i].s - T[j].e));
			Ans[T[j].pos] = min(Ans[T[j].pos], max(0, T[i].s - T[j].e));
		}
	}
}

bool isOK(){
    for(auto i : Ans){
		if(i) return false;
	}
	return true;
}

void output(){
	for(int i : Ans) printf("%d ", i);
	return (void)printf("\n");
}

void proc(){
    Ans.assign(N, INT32_MAX);
	proc2();
	for(auto & t : T){
		swap(t.s, t.e);
		t.s = -t.s;
		t.e = -t.e;
	}
	proc2();
    if(isOK()) return (void) output();

    void proc3();
    proc3();
	output();
} 


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
        T.assign(N = getInt(), {0,0,0});
		int k = 0;
		for(auto & t : T){
			t.e = -getInt();
			t.s = -getInt();
			t.c = getInt();
			t.pos = k++;
		}
		proc();
	}

    return 0;
}


struct SegmentTree{

int n;
vi st;
vi lazy;

static int lson(int x){return x<<1;}
static int rson(int x){return lson(x)|1;}

void init(int nn){
	st.assign((n=nn+1)<<2, 0);
	lazy.assign(n<<2, 0);
}

void _pushUp(int t){
	st[t] = max(st[lson(t)], st[rson(t)]);
}

void _update(int t, int d){
	st[t] += d;
	lazy[t] += d;
}

void _pushDown(int t){
    int & z = lazy[t];
	if(0 == z) return;
	_update(lson(t), z);
	_update(rson(t), z);
	z = 0;
}

int query(int t, int s, int e, int a, int b){
    if(a <= s && e <= b){
		return st[t];
	}
    _pushDown(t);
	int m = (s + e) >> 1;
	int ans = 0;
	if(a <= m) ans = query(lson(t), s, m, a, b);
	if(m < b) ans = max(ans, query(rson(t), m+1, e, a, b));
	return ans; 
}

void modify(int t, int s, int e, int a, int b, int d){
    if(a <= s && e <= b){
		_update(t, d);
		return;
	}         
	_pushDown(t);
	int m = (s + e) >> 1;
	if(a <= m) modify(lson(t), s, m, a, b, d);
	if(m < b) modify(rson(t), m+1, e, a, b, d);
	_pushUp(t);
	return;
}

}ST;

vi W;
void proc3(){
    /// 离散化
	W.clear(); W.reserve(N+N+1);
	W.push_back(0);
    for(const auto & t : T){
		W.push_back(t.s);
		W.push_back(t.e);
	}
	sort(W.begin(), W.end());
	W.erase(unique(W.begin(), W.end()), W.end());
	int n = W.size() - 1;
	ST.init(n);

    map<int, vector<_t>> color;
	for(auto & t : T){
        t.s = lower_bound(W.begin(), W.end(), t.s) - W.begin();
		t.e = lower_bound(W.begin(), W.end(), t.e) - W.begin();
        color[t.c].push_back(t);
        ST.modify(1, 1, n, t.s, t.e, 1);
	}
	
	for(const auto & p : color){
        /// 首先把颜色删除
		for(const auto & t : p.second){
			ST.modify(1, 1, n, t.s, t.e, -1);
		}
		/// 然后依次查询
		for(const auto & t : p.second){
			if(0 == Ans[t.pos]) continue;
			int tmp = ST.query(1, 1, n, t.s, t.e);
			if(tmp){
				Ans[t.pos] = 0;
			}
		}
		/// 再依次塞回去
		for(const auto & t : p.second){
			ST.modify(1, 1, n, t.s, t.e, 1);
		}
	}
	return;
}