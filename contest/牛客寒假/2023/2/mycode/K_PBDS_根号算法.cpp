/**
 * 给定一个N个点M条边的无向图，再给定Q次询问。每次询问给定K个点，
 * 问这K个点一共可以构成原图中的多少条边。
 * N、M、Q、SIGMA{K}均在2E5
 * 考虑根号算法，以sqrt(SIGMA{K})作为分界。
 * 考虑一次询问，假设K比较小的话，直接用暴力法做一个K^2的循环，进行查询。
 * 最多循环次数为O(Ksqrt(K))。
 * 假设K比较大的话，直接遍历K个点在原图上的每个邻点，看该邻点是否存在于K个点中
 * 最多循环M次，该情况最多出现根号K次，因此是O(Msqrt(K))
 * 总之最后是O(Nsqrt(N))
 * 查询需要用到哈希算法。STL会超时。使用PBDS即可。
 * gp_hash_table比cc_hash_table快。 
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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
int const SIZE = 130;
#else
int const SIZE = 1.1E6+10;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
// using si = unordered_set<int>;
using si = gp_hash_table<int, int>;
using vsi = vector<si>;

int const LIMIT = sqrt(2E5);

int N, M, Q;
vsi G;
int K;

int proc1(){
    vi vec(K, 0);
	for(int & i : vec) i = getInt();
	int ans = 0;
	for(int i=0;i<K;++i)for(int j=i+1;j<K;++j){
        if(G[vec[i]].find(vec[j]) != G[vec[i]].end()) ++ans;
	}
	return ans;
}

int proc2(){
	si ss;
	for(int i=0;i<K;++i)ss.insert({getInt(), 0});

    int ans = 0;
	for(const auto & p : ss)for(const auto & pp : G[p.first])if(ss.find(pp.first)!=ss.end())++ans;
	return ans >> 1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    N = getInt();
	M = getInt();
	Q = getInt();
	G.assign(N + 1, si());
	for(int a,b,i=0;i<M;++i){
		a = getInt(); b = getInt();
		G[a].insert({b, 0});
		G[b].insert({a, 0});
	}
	for(int q=1;q<=Q;++q){
		printf("%d\n",((K=getInt()) < LIMIT)?proc1():proc2());
	}
    return 0;
}
