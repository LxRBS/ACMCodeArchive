/**
 * 给定一个无向图，N=10
 * 找一条不重复点的且距离最长的路径
 * 由于N很小，可以使用O(N!)算法
 * 答案必然是某个排列的前缀，因此枚举全排列即可
 * 标程用的DFS，是O(NN!)。
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
vector<vector<pii>> G;

int get(int a, int b){
    for(const auto & p : G[a]){
        if(p.first == b){
            return p.second;
        }
    }
    return -1;
}

llt proc(const vi & vec){
    llt ans = 0;
    for(int i=0;i+1<N;++i){
        auto tmp = get(vec[i], vec[i + 1]);
        if(tmp == -1) return ans;
        ans += tmp;
    }
    return ans;
}

llt proc(){
    vi vec(N, 0);
    for(int i=0;i<N;++i) vec[i] = i + 1;
    llt ans = 0;
    do{
        ans = max(ans, proc(vec));
    }while(next_permutation(vec.begin(), vec.end()));
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    G.assign(N + 1, {});
    for(int a,b,c,i=0;i<M;++i){
        cin >> a >> b >> c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }
    cout << proc() << endl; 
    return 0;
}