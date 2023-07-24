/**
 * 给定一个无向图，问最少添加多少条边，可以使得dfs序恰好是1~N
 * 模拟一遍深搜，每一次无法继续的情况必然要添加一条边。
 * 将每个点的邻居从小到大排序，然后反着入栈即可
 * 有自环边与重边。
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;

int N, M;
vector<set<int>> G;
vi Flag;

int proc(){
    int ans = 0;
    vi stack(1, 1);
    vi vec;
    while(1){
        int cur = vec.size();
        if(cur == N) break;       

        ++cur;
        while(!stack.empty() and stack.back() < cur) stack.pop_back();

        if(stack.empty() or stack.back() != cur){
            ++ans;
        }else{
            stack.pop_back();
        }
        vec.push_back(cur);
        for(auto it=G[cur].rbegin(),et=G[cur].rend();it!=et;++it){
            stack.emplace_back(*it);
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
        cin >> N >> M;
        G.assign(N + 1, set<int>());
        for(int a,b,i=0;i<M;++i){
            cin >> a >> b;
            if(a == b) continue;
            G[a].insert(b);
            G[b].insert(a);
        }
        cout << proc() << endl;
    }
    return 0;
}


