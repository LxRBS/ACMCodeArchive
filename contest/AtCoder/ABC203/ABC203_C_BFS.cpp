/**
 * 初始在坐标0并持有能量K，一共有N个位置，每个位置有(坐标, 能量)
 * 如果能够走到该坐标就可以补充该能量。每走一格消耗一个能量
 * 问最远能走多远。
 * 虽然能量和坐标数值很大，但是补充点的数量是有限的，用一个队列。
 * 初始将{0, K}入队。每次取出头结点，根据h.first到h.first+h.second之间的补充点更新数据
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 34;
#else
int const SZ = 2E5+10;
#endif

int N, K;
map<llt, llt> Map;

llt proc(){
    map<llt, llt> flag;
    flag.insert({0LL, K+0LL});
    queue<pair<llt, llt>> q;
    q.push({0LL, K+0LL});
    llt ans = K;
    while(not q.empty()){
        auto h = q.front(); q.pop();
        auto level = h.first + h.second;
        auto it = Map.upper_bound(h.first);
        auto jt = Map.upper_bound(level);
        for(auto i=it;i!=jt;++i){
            auto used = i->first - h.first;
            auto left = i->second + h.second - used;
            auto tt = flag.find(i->first);
            if(tt == flag.end()){
                tt = flag.insert(tt, {i->first, left});
                q.push({i->first, left});
                ans = max(ans, i->first + left);
            }else if(tt->second < left){
                tt->second = left;
                q.push({i->first, left});
                ans = max(ans, i->first + left);
            }
        }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    for(int i=0;i<N;++i){
        llt a;
        llt b;
        cin >> a >> b;
        Map[a] += b;
    }
    cout << proc() << endl;
    return 0;
}