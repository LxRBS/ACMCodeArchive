/**
 * 给定N个字符串，对每一个Si，求其他字符串与之能够产生的最长前缀的长度
 * 字符串总长度在5E5，记作L
 * 对每个字符串的每个前缀做一个哈希，保存起来。
 * 令Mi保存Si的所有前缀，其中Mi[j]字符串Si长度为j的前缀
 * 再令Total保存所有字符串的前缀，即Total[j][h]表示字符串的集合，此集合里的字符串均有长度为j的前缀h
 * 采用map保存，预处理显然在O(LlogL)
 * 对每一个Si，对它的所有前缀，从大到小，查询同一个集合里是否还有其他字符串即可。
 * 所有前缀就是L个，在集合里查询是log的。因此处理阶段也是O(LlogL)
 * 保存前缀用了字符串双哈希，以防冲突。但实际上做了截断，因为哈希是ULL，而保存时转成了int，不过可以过。
 * 标程用了一个递归的方法，首先有26个集合，然后将N个字符串的首字母扔到对应的集合。如果某个集合只有一个成员，则该成员的答案就是0
 * 然后开始递归。对第k次递归，根据增加的字母进行划分，如果某个字符串单独成集合，则它的答案就是k-1
 * 复杂度是O(26(N + L))。
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

using llt = unsigned long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using t3t = tuple<int, llt, llt>;

llt Seed = 13331ULL;
llt Teed = 131ULL;

int N;

vector<map<int, pii>> Vec;

map<int, map<pii, set<int>>> Map;

int proc(int pos){
	const auto & mm = Vec[pos];
	for(auto it=mm.rbegin(),et=mm.rend();it!=et;++it){
		const auto lcp = it->first;
		const auto & pp = it->second;
		auto tt = Map.find(lcp);
		if(tt != Map.end()){
			const auto & total_mm = tt->second;
			auto ut = total_mm.find(pp);
			if(ut != total_mm.end()){
				const auto & sss = ut->second;
				assert(sss.count(pos));
				if(sss.size() != 1){
					return lcp;
				}
			}
		}
	}
	return 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
	Vec.reserve(N);
	for(int i=0;i<N;++i){
		string s; cin >> s;
		Vec.emplace_back(map<int, pii>());
		auto & mm = Vec.back();

        llt a = 0, b = 0;
		for(int j=0,n=s.length();j<n;++j){
			a = a * Seed + s[j] - 'a';
			b = b * Teed + s[j] - 'a';
		    mm.insert({j + 1, {a, b}});	
			Map[j + 1][{a, b}].insert(i);
		}
	}

	for(int i=0;i<N;++i){
		printf("%d\n", proc(i));
	}
    return 0;
}