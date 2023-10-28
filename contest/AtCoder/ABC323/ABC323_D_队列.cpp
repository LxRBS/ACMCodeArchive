/**
 * 多重集合，有Ni个Ai
 * 每两个Ai可以合成1个新的数值（即Ai+Ai），且原来的两个Ai消失
 * 问最后最少能剩多少个元素
 * 用一个map，从小到大合并即可
 * 已经处理过且剩下的元素绝对不可能再合并
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using llt = long long;

int N;
map<llt, llt> Map;

llt proc(){
    map<llt, llt>::iterator cur = Map.begin();
    while(1){
        while(cur != Map.end() and cur->second == 1) ++cur;
        if(cur == Map.end()) break;

        auto cnt = cur->second;
        auto key = cur->first * 2;
        Map[key] += cnt / 2;

        if(cnt & 1) ++cur;
        else cur = Map.erase(cur);
    }
    return Map.size();
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for(int a,b,i=0;i<N;++i){
        cin >> a >> b;
        Map[a] += b;
    }
    cout << proc() << endl;
    return 0;
}