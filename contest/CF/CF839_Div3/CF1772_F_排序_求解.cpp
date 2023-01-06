/**
 * 给定一个01矩阵，每次有两种操作：
 * 1 选一个位置，该位置的元素与四邻域均不同，将该元素改变
 * 2 对当前矩阵进行一个拷贝，生成一个副本
 * 现在给定K+1个矩阵，已知这中间有一个是原始矩阵，另外K个是2操作得到的副本
 * 要求还原出一个操作序列，恰好符合给定的K+1个矩阵，保证一定有答案
 * 关键是确定顺序，由于不一定给出了所有操作过程中间出现的矩阵，因此简单的一步判断无法得到矩阵之间的关系
 * 但是考虑到操作1是不可逆的，而且由于保证答案存在，所以根据可能的操作1的数量排序，则一定是按这个顺序操作
 * 然后根据前一个矩阵与后一个矩阵的关系即可还原出操作。
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
int const SIZE = 2E5+10;
#endif

using pii = pair<int, int>;
using vpii = vector<pii>;
using vi = vector<int>;
using vs = vector<string>;
using vvs = vector<vs>;
using t3t = tuple<int, int, int>;
using vt3t = vector<t3t>;
using vvt3t = vector<vt3t>;
using si = set<int>;
using vsi = vector<si>;



int N, M, K;
vvs A;
vvt3t G;

vi Old2New;
vsi NewIdx;

bool operator == (const vs & a, const vs & b){
	for(int i=0;i<N;++i){
		if(a[i] != b[i]) return false;
	}
	return true;
}

bool check(const vector<string> & v, int r, int c){
	if(0 == r || N - 1 == r || 0 == c || M - 1 == c) return false;
	auto ch = v[r][c];
	if(ch == v[r-1][c]) return false;
	if(ch == v[r+1][c]) return false;
	if(ch == v[r][c-1]) return false;
	if(ch == v[r][c+1]) return false;
	return true;
}

t3t cmp(int idx, int jdx){
	const auto & a = A[idx];
	const auto & b = A[jdx];
	int r = -1, c = -1, d = 0;
	for(int i=0;i<N;++i)for(int j=0;j<M;++j){
		if(a[i][j] == b[i][j]) continue;

		if(++d > 1) return {false, r, c};
		r = i, c = j;
	}
	// assert(1 == d);
	if(1 != d) return {false, r, c};
	return {check(a, r, c), r, c};
}

int f(const vector<string> & vec){
	int ans = 0;
    for(int i=1;i<N-1;++i)for(int j=1;j<M-1;++j){
		auto ch = vec[i][j];
		if(ch == vec[i+1][j]) continue;
		if(ch == vec[i-1][j]) continue;
		if(ch == vec[i][j+1]) continue;
		if(ch == vec[i][j-1]) continue;
		++ans;
	}
	return ans;
}

void proc(int aidx, int bidx, vt3t & ans){
	const auto & a = A[aidx];
	const auto & b = A[bidx];

	int d = 0;
	vpii rc;
	for(int i=0;i<N;++i)for(int j=0;j<M;++j){
		if(a[i][j] != b[i][j]){
			++d;
			rc.emplace_back(i, j);
		}
	}

	for(auto p : rc){
		ans.emplace_back(1, p.first, p.second);
	}
    ans.emplace_back(2, bidx, -1);
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N >> M >> K;
	A.assign(K + 1, vs(N, string()));
	for(auto & vec : A)for(auto & s : vec) cin >> s;

	vpii cnt(K+1, {0, 0});
	for(int i=0;i<=K;++i) cnt[i] = {i, f(A[i])};
	sort(cnt.begin(), cnt.end(), [](pii a, pii b){
        if(a.second != b.second) return a.second > b.second;
		return a.first < b.first;
	});

	vt3t ans;
	for(auto it=++cnt.begin(),et=cnt.end();it!=et;++it){
		proc((it-1)->first, it->first, ans);
	}

	printf("%d\n", cnt.begin()->first + 1);
	printf("%d\n", (int)ans.size());
    for(auto p : ans){
		if(1 == get<0>(p)){
			printf("1 %d %d\n", get<1>(p) + 1, get<2>(p) + 1);
		}else{
			printf("2 %d\n", get<1>(p) + 1);
		}
	}
    return 0;
}

