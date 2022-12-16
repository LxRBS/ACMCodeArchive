/**
 * 给定一个数字串L，再给定一个W，然后有M个询问[s, e, k]
 * 对每个询问，找出不同的i和j，使得
 * L.substr(i, W) * L.substr(s, e-s+1) + L.substr(j, W) = k (mod 9)
 * 首先注意到某个数模9其实就等于它的各位数字之和模9，因此首先可以对L计算一个模9的前缀和D
 * 然后注意到W是固定的，可以计算出所有长度为W的子段的余数。用Map记录
 * Map[i]记录了余数为i的所有开头位置，并且排序，其实记录两个就可以了。
 * 令c = D[e] - D[s-1]，相当于解方程 x * c + y = k (mod 9)，其中c和k已知，x和y未知
 * 遍历一遍Map即可，因为x和y均在[0, 9]
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

using llt = int;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using vpii = vector<pii>;

char S[SIZE];
int W, M, N;
vi A, D;
vi U;
msi Map;

void answer(){
	pii ans = {INT32_MAX, INT32_MAX};
	int s, e, k;
	scanf("%d%d%d", &s, &e, &k);
    int c = (D[e] - D[s-1]) % 9;
    (c += 9) %= 9;
	for(const auto & p : Map){
		int t = (k - p.first * c) % 9;
		
		(t += 9) %= 9;
		if(t == p.first){
			if(p.second.size() == 1) continue;
			ans = min(ans, {*p.second.begin(), *++p.second.begin()});
			continue;
		}

		auto it = Map.find(t);
		if(it == Map.end()) continue;
		ans = min(ans, {*p.second.begin(), *it->second.begin()});
	}
	if(ans.first == INT32_MAX) printf("-1 -1\n");
	else printf("%d %d\n", ans.first, ans.second);
	return;
}

void proc(){
	A.assign((N = strlen(S+1))+1, 0);
	D.assign(N+1, 0);
	for(int i=1;i<=N;++i){
		D[i] = (D[i-1] + (A[i] = S[i] - '0')) % 9;
	}

    Map.clear();
	U.assign(N+1, 0);
    for(int i=1;i<=N-W+1;++i){
		U[i] = (D[i+W-1] - D[i-1]) % 9;
	    Map[(U[i] += 9) %= 9].insert(i);
	}

	for(int i=0;i<M;++i){
		answer();
	}
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
	int nofkase;
	scanf("%d", &nofkase);
    while(nofkase--){
		scanf("%s%d%d", S+1, &W, &M);
		proc();
	}
    return 0;
}


