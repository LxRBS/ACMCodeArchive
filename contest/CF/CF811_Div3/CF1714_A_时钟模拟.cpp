/**
 * 给定睡觉的时刻，再给定n个闹钟，问能睡多久
 * 找到睡觉时刻之后最近的闹钟时刻，计算一下即可。
 */
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using vpii = vector<pii>;

int N;
pii Time;

pii f(const pii & a, const pii & b){
    int h = a.first - b.first;
	if(h < 0) h += 24;
	int m = a.second - b.second;
	if(m < 0) m += 60, h -= 1;
	if(-1 == h) h += 24;
	return {h, m};
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
		cin >> N >> Time.first >> Time.second;
        vpii vec;
		for(int h,m,i=0;i<N;++i){
            cin >> h >> m;
			vec.emplace_back(h, m);
		}
		sort(vec.begin(), vec.end());
		auto it = lower_bound(vec.begin(), vec.end(), Time);
		if(it == vec.end()) it = vec.begin();
		pii ans = f(*it, Time);
		cout << ans.first << " " << ans.second << endl;		
    }
    return 0;
}
