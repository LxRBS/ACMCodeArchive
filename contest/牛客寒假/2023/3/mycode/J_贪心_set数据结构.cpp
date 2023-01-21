/**
 * 给定一个N长度的数组A，每次操作可以选一个ai乘2或者除2，
 * 最多进行K次操作，要求使得max(A) - min(A)最小，求这个最小值
 * 首先显然是贪心的思想，乘2操作对小数做，除2操作对大数做。
 * 设置一个Map，Map[i]记录了i是经过几次乘法操作得到的
 * 在设置一个Set，里面保存没有操作或者除法操作的数
 * 首先将A排个序，然后从小到大对ai做乘法操作，如果Map中最小的数比当前ai还要小，则乘法操作应该对Map中最小的数做，否则对ai做并塞入Map
 * 有两种可能性，要么K次操作做完。要么所有的数都进了Map。
 * 如果所有的数都进入了Map，则无需再做乘法操作，因为显然除法造成的效果要不劣于乘法，所以不必做多余的乘法操作。
 * 其实可以考虑先做除法操作，除法操作可以全部做完，且有可能可以提前退出。
 * 剩下的数全部进入Set。
 * 用left记录当前可以做除法的数量
 * 做一个循环，当Map不为空：
 * 将Map的最大值拿出来除以2，并且根据情况放入Map或者Set，并且++left
 * while(left允许且Set的最大值大于Map的最大值) 将Set的最大值除2再塞入Map
 * Map变为空以后，对Set的最大值做除法操作，直到left用完。
 * 每一次变动Map和Set的时候更新答案。
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
int const SIZE = 26;
#else
int const SIZE = 2800;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>; 
using vll = vector<llt>;
using mi = multimap<llt, int>;
using si = multiset<llt>;

int N, K;
vll A;

mi Map;
si Set;

inline llt get(){
	llt maxx = -1, minn = -1;
	if(!Map.empty()){
		maxx = Map.rbegin()->first;
		minn = Map.begin()->first;
	}
	if(!Set.empty()){
		if(-1 == maxx || maxx < *Set.rbegin()) maxx = *Set.rbegin();
		if(-1 == minn || *Set.begin() < minn) minn = *Set.begin();
	}
	return maxx - minn;
}

llt proc(){
	if(1 == N) return 0;

	sort(A.begin(), A.end());
	auto ans = *A.rbegin() - *A.begin();

	int cur = 0;
	int left = K;
	for(int i=0;i<K;++i){
		if(Map.empty()){
			Map.insert({A[cur++]<<1, 1});	
		}else{
			auto it = Map.begin();
			if(it->first < A[cur]){
				Map.insert({it->first<<1, it->second+1});
				Map.erase(Map.begin());
			}else{
				Map.insert({A[cur++]<<1, 1});
			}			
		}
		ans = min(ans, max(*A.rbegin(), Map.rbegin()->first) - min(Map.begin()->first, A[cur]));
		
		--left;
        if(cur == N) break;
	}
	for(int i=cur;i<N;++i) Set.insert(A[i]);

	int cnt = left;
	while(cnt < K){
		assert(!Map.empty());
        auto mit = --Map.end();
		auto v = mit->first;
		auto t = mit->second;
		Map.erase(mit);

		++cnt; ++left;

		if(--t){
			Map.insert({v>>1, t});
		}else{
			Set.insert(v>>1);
		}		

		ans = min(ans, get());
        
		while(1){
			if(0 == left) break;
			if(Set.empty()) break;
			if(Map.empty()) break;
			if(Map.rbegin()->first >= *Set.rbegin()) break;

			auto tmp = *Set.rbegin() >> 1;
			Set.erase(--Set.end());
			--left;
			Set.insert(tmp);
			ans = min(ans, get());
		}		
	}
	assert(Map.empty());
    while(left--){
		auto v = *Set.rbegin() >> 1;
		Set.erase(--Set.end());
		Set.insert(v);
		ans = min(ans, get());
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    A.assign(N = getInt(), 0);
	K = getInt();
	for(auto & i : A) i = getInt();
	cout << proc() << endl;
    return 0;
}