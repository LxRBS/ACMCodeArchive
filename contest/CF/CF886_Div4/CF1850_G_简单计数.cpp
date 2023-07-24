/**
 * 本质上就是问: 给定N个点，任选两点所形成的的向量在八个方向上，问满足条件的点对有多少对
 * 统计4个直线族，每条直线上假设有m个点，对答案的贡献就是 m * (m - 1)
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

int N;
map<int, vector<pii>> M[4];

llt proc(){
    llt ans = 0;
    for(const auto & m : M){
        for(const auto & p : m){
            llt sz = p.second.size();
            ans += sz * (sz - 1LL);
        }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;    
    while(nofkase--){
        cin >> N;
        for(auto & m : M) m.clear();
        for(int x,y,i=0;i<N;++i){
            cin >> x >> y;

            M[0][x].emplace_back(x, y);
            M[1][y].emplace_back(x, y);
            M[2][x - y].emplace_back(x, y);
            M[3][x + y].emplace_back(x, y);
        }
        cout << proc() << endl;
    }
    return 0;
}

