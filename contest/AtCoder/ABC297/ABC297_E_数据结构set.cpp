/**
 * 本质上就是给定N个数的多重集合（每个数均有无限个），可以从中选任意个数进行组合求和
 * 问第K小的数是多少，不同组合导致同一个和值的只能计算一次，N是10，K在2E5
 * 使用set，首先将N个数全塞进去，然后循环：每次取出最小的，记作s，将N个数加s全部塞进set。
 * 注意要去重，NKlog(NK)
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;

using llt = long long;
using vi = vector<int>;
using vs = vector<string>;

int N, K;
vector<llt> A;
vector<llt> D;

llt proc(){
    set<llt> s, t;
    for(auto i : A) s.insert(i);
	while(t.size() < K){
        auto h = *s.begin();
		t.insert(h);
		s.erase(s.begin());
        for(auto i : A) s.insert(i + h); 
	}

	return *--t.end();
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> K;
    D.reserve(N * K);
	A.assign(N, 0LL);
	for(auto & i : A) cin >> i;
	cout << proc() << endl;
    return 0; 
}
