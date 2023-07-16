/**
 * 给定若干个Fi，每个Fi有若干个权值，以及一个价格
 * 问是否存在Fi和Fj，满足以下全部条件
 * 1. Pi >= Pj
 * 2. Fi有的权值，Fj都有
 * 3. Pi > Pj 或者 Fj比Fi的权值要多
 * N和M只有100，用STL暴力
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using vi = vector<int>;
using vvi = vector<vi>;

int N, M;
vi P;
vector<set<int>> F;

bool isOK(int idx, int jdx){
    if(P[idx] < P[jdx]) return false;

    int c = 0;
    for(const auto i : F[idx]){
        auto it = F[jdx].find(i);
        if(it == F[jdx].end()){
            ++c;
        }
    }

    if(c) return false;    
    if(P[idx] != P[jdx]) return true;

    c = 0;
    for(auto i : F[jdx]){
        auto it = F[idx].find(i);
        if(it == F[idx].end()) return true;
    }
    return false;
}

bool proc(){
    for(int i=0;i<N;++i){
        for(int j=i+1;j<N;++j){
            if(isOK(i, j) or isOK(j, i)){
                // cout << i + 1 << ", " << j + 1 << endl;
                return true;
            }
        }
    }
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;

    P.assign(N, 0);
    F.assign(N, set<int>());
    
    for(int i=0;i<N;++i){
        cin >> P[i];
        int c; cin >> c;
        for(int j=0;j<c;++j){
            int f; cin >> f;
            F[i].insert(f);
        }
    }

    cout << (proc() ? "Yes" : "No") << endl;
    return 0;
}