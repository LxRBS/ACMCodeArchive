/**
 * 给定AB数组，其中Ai表示分数，Bi表示数量。再给定三种操作
 * 1 x y: 将第x个分数修改为y
 * 2 x y: 将第x个数量修改为y
 * 3 x: 从A中间挑出x个分数，使得分数之和最大，显然不能超过相应的数量限制
 * 在树状数组上做二分即可，两个树状数组，一个在Ai位置保存Bi，记作C
 * 一个在Ai位置保存Ai*Bi，记作S
 * 1和2操作在相应位置上修改即可。
 * 3操作需要先在C上做一个二分。找到位置以后，在S中做一个查询操作即可。
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
int const SIZE = 3E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using vll = vector<llt>;
using vvll = vector<vll>;
using pll = pair<llt, llt>;
using vpll = vector<pll>;
using t3t = tuple<int, int, int>;
using vt3t = vector<t3t>;

llt const MOD = 998244353LL;

struct FenwickTree{

using llt = long long;
using vll = vector<llt>;

int n;
vll c;

static int lowbit(int x){return x & -x;}

void init(int nn){c.assign((this->n=nn)+1, 0LL);}

void modify(int pos, llt delta){
	for(int i=pos;i<=n;i+=lowbit(i)) c[i] += delta;
}

llt query(int pos){
	llt ans = 0;
	for(int i=pos;i;i-=lowbit(i)) ans += c[i];
	return ans;
}

llt query(int s, int e){return query(e) - query(s - 1);}

};

int N, Q;

FenwickTree C, S;
vpll AB;
vll W;
vt3t Cmds;

void proc1(int x, llt y){
	auto & p = AB[x - 1];
    int pos = lower_bound(W.begin(), W.end(), p.first) - W.begin();
	C.modify(pos, - p.second);
	S.modify(pos, - p.first * p.second);

    p.first = y;
	pos = lower_bound(W.begin(), W.end(), p.first) - W.begin();
	C.modify(pos, p.second);
	S.modify(pos, p.first * p.second);
}

void proc2(int x, int y){
    auto & p = AB[x - 1];
	int pos = lower_bound(W.begin(), W.end(), p.first) - W.begin();
	C.modify(pos, y - p.second);
	S.modify(pos, (y - p.second) * p.first);
	p.second = y;
}

llt proc3(int x){
	auto n = C.n;
	auto total = C.query(n);
	if(total < x) return -1;
	if(total == x) return S.query(n);

    int left = 1, right = n, mid;
	do{
        mid = (left + right) >> 1;
		if(total - C.query(mid) > x) left = mid + 1;
		else right = mid - 1;
	}while(left <= right);

	auto cnt = C.query(left + 1, n);
    auto ans = S.query(left + 1, n);
	
	auto bi = C.query(left, left);
	auto aibi = S.query(left, left);
	auto ai = aibi / bi;
    auto ans2 = (x - cnt) * ai;

	return ans + ans2;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    AB.assign((N=getInt()), {});
	W.reserve(N + 1); W.push_back(-1);
	for(auto & p : AB){
		W.emplace_back(p.first = getInt());
		p.second = getInt();
	} 

    Cmds.reserve(Q = getInt());
    for(int op,x,y,q=1;q<=Q;++q){
		op = getInt(); x = getInt();
		if(op != 3) y = getInt();
		else y = -1;
        Cmds.emplace_back(op, x, y);
		if(1 == op) W.emplace_back(y);
	}

	sort(W.begin(), W.end());
	W.erase(unique(W.begin(), W.end()), W.end());

    C.init(W.size());
	S.init(W.size());

	for(const auto & p : AB){
		int pos = lower_bound(W.begin(), W.end(), p.first) - W.begin();
        C.modify(pos, p.second);
		S.modify(pos, p.first * p.second);    
	}

	for(const auto & p : Cmds){
		switch(get<0>(p)){
			case 1:proc1(get<1>(p), get<2>(p));break;
			case 2:proc2(get<1>(p), get<2>(p));break;
			case 3:printf("%lld\n", proc3(get<1>(p)));break;
			default: assert(0);
		}
	}
    return 0;
}