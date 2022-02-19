/**
 * 给定一个数组（有重复的数），对每一对值x和y，令f(x, y) = (cnt[x]+cnt[y])*(x+y)
 * 求f(x, y)的最大值，此外，还有一些(x, y)对是不能计算其中的，称为BadPair
 * 很显然对cnt相同的值，只需要考虑最大即可，但是由于有BadPair的存在，所以需要枚举每一个x
 * 对每一个x，查找比cntx小的每一个cnti，直接比较cnti中最大的值即可，如果最大值是BadPair，那就比较次大值
 * 因为BadPair一共有M个，所以整个多付出的循环次数为M
 * for x 循环是N，for cnt循环是sqrt(N)，查找BadPair可以做成log，应该是O(Nsqrt(N)logM)
 *  题解说没有根号，没看懂
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
int const SIZE = 33;
#else
int const SIZE = 300110;
#endif

typedef pair<int, int> pii;
struct pii_hash{
    size_t operator()(const pii &p)const{
		return p.first * 1331 + p.second;
	}
};
typedef long long llt;
typedef vector<int> vi;
typedef unordered_map<int, unordered_set<int> > Map;

int N, M;
int A[SIZE];
Map Bad;
// unordered_set<pii, pii_hash> BadSet;
// vi CC[SIZE];
vector<vi> CC;
map<int, int> Cnt;
vector<pii> BadVec;

inline bool isBad(int x, int y){
	// auto it = Bad.find(x);
	// return it != Bad.end() && it->second.find(y) != it->second.end();
	// return BadSet.count({x, y}); // 这样查询比下面的vec要慢100+ms
	/// 先塞进去再排序再二分比上面的set要快
	return binary_search(BadVec.begin(), BadVec.end(), pii({x, y}));
}

llt proc(){
	// for(int i=1;i<=N;++i) CC[i].clear(); // 这一句极其耗时，从400+ms直接T到2s。
	CC.assign(N+1, vi()); // 上一句极其耗时，会T，要用这一句
    for(auto p: Cnt){
        CC[p.second].push_back(p.first);
	}
    vi bianli; 
	// bianli.reserve(N); // 这句话加了会影响速度，主要是不知道空间到底多大
	for(int i=1;i<=N;++i){
		if(CC[i].empty()) continue;
		bianli.push_back(i);
		reverse(CC[i].begin(), CC[i].end());
	}

    llt ans = 0;
    for(unsigned ci,cj,i=0,n=bianli.size();i<n;++i){
		for(auto x: CC[ci=bianli[i]]){ // x的数量就是ci
			for(unsigned j=0;j<=i;++j){ // 在cj中找不是bad的最大的数
                for(auto y: CC[cj = bianli[j]]){
					if(x == y || isBad(x, y)) continue;
                    ans = max(ans, (llt)(x + y)*(ci + cj));
					break;
				}
			}			
		}

	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
		Cnt.clear(); 
		// BadSet.clear();
		BadVec.clear();
        N = getInt(); BadVec.reserve(2 *(M = getInt()));
		for(int i=1;i<=N;++i) ++Cnt[A[i] = getInt()];
		for(int x,y,i=1;i<=M;++i){
            x = getInt(); y = getInt();
			// Bad[x].insert(y);
			// Bad[y].insert(x);
			// BadSet.insert({x, y});
			// BadSet.insert({y, x});
			BadVec.emplace_back(pii({x, y}));
			BadVec.emplace_back(pii({y, x}));
		}
		sort(BadVec.begin(), BadVec.end());
		printf("%lld\n", proc());
	}
    return 0;
}
