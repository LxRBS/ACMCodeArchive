/**
 * 给定一个数组A，再给定若干对(i, j)
 * 对任意A的子串，对任意对(i, j)，如果不同时含有i和j，则称该子串是好的
 * 问好的子串的数量
 * 首先只需考虑i<j的情况，将所有对排序，对每个i只记录最小的j即可
 * 再反向扫描一遍，对所有i记录min(到目前为止的最小j)
 * 然后正向扫描一遍，for i 1...N
 * 对每一个i，求出距离它最近的j，则以i为起点的子数组，一共有N-j+1个是不好的
 * 求出不好的总数，剪一下即可
 * 也可以使用数组对每个i直接记录最小的j，应该O(N)即可。
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
int const SIZE = 35000;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;

int N, M;
msi Map;

llt proc(){
	map<int, int> m;
	int tmp = 2000000000;
	for(auto it=Map.rbegin(),et=Map.rend();it!=et;++it){
        tmp = m[it->first] = min(tmp, *it->second.begin()); 
	}

	llt ans = 0;
	for(int i=1;i<=N;++i){
		auto it = m.lower_bound(i);
		if(it == m.end()) break;
		ans += N - it->second + 1;
	}
	return (N+1LL)*N/2LL - ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	for(int kase=1;kase<=nofkase;++kase){
        Map.clear();
		N = getInt(); M = getInt();
		for(int a,b,i=0;i<M;++i){
			a = getInt(); b = getInt();
			if(a > b) swap(a, b);
			Map[a].insert(b);
		}
		printf("%lld\n", proc());
	}
    return 0;
}