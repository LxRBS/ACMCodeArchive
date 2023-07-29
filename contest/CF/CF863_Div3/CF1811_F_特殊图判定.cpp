/**
 * 给定图，判断是否为K圈图，K未知
 * 题面描述感觉不太清楚。所谓K圈图，中心有一个圈，共K条边
 * 每个节点向外又连有一个圈，也是一共K条边。除此之外没有其他边
 * 首先，如果满足条件必然有 N == K * K, M = K * K + K，可以先求出K，此处可以进行判断
 * 然后图必然连通，且必然只含度为2的点和度为4的点，且各自数量有定数，此处可以进行判断
 * 然后对每一个度为4的点，需要再接一个长度为K的圈，且该圈上其他点均为度为2的，可以依次判断
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
int const SZ = 200000 + 12;
#endif

int N, M;
vvi G;

vi Father;
void init(int n){Father.assign(n + 1, 0);for(int i=1;i<=n;++i)Father[i]=i;}
int find(int x){return x == Father[x]?x:Father[x]=find(Father[x]);}
void unite(int x, int y){Father[find(y)] = find(x);}

bool dfs(int cur, int pre, int end, int cnt, int target){
    if(cur == end) {
        if(cnt + 1 == target){
            return true;
        }
        return false;
    }

    const auto & vec = G[cur];
    if(vec.size() != 2) return false;
    assert(vec[0] == pre or vec[1] == pre);

    return dfs(vec[0] + vec[1] - pre, cur, end, cnt + 1, target);
}

bool isOK(int u, int k, const set<int> & leaf, const set<int> & cycle){
    const auto & vec = G[u];
    assert(vec.size() == 4);
    vi v2, v4;
    for(int i : vec){
        auto it = leaf.find(i);
        if(it != leaf.end()){
            v2.push_back(i);  
        }else{
            assert(cycle.find(i) != cycle.end());
            v4.push_back(i);
        }
    }
    if(v2.size() != 2 or v4.size() != 2) return false;
    int s = v2[0], e = v2[1];
    assert(s != -1 and e != -1);
    return dfs(s, u, e, 1, k);
}

bool proc(){
    int k = sqrt(N);
    if(k * k != N) return false;
    if(M != k * (k + 1)) return false;

    map<int, set<int>> mm;
    for(int i=1;i<=N;++i){
        if(find(1) != find(i)) return false;
        mm[G[i].size()].insert(i);
    }

    auto it = mm.find(2);
    if(it == mm.end()) return false;
    const auto & vec2 = it->second;
    if(vec2.size() != k * (k - 1)) return false;

    it = mm.find(4);
    if(it == mm.end()) return false;
    const auto & vec4 = it->second;
    if(vec4.size() != k) return false;

    for(int i : vec4){
        if(not isOK(i, k, vec2, vec4)) return false;
    }
    return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> M;
        G.assign(N + 1, vi());
        init(N);
        for(int a,b,i=0;i<M;++i){
            cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
            unite(a, b);
        }
        cout << (proc() ? "YES" : "NO") << endl;
    }
    return 0;
}

