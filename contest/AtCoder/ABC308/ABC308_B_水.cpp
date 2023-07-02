/**
 * 字符串map的一个简单应用
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

int N, M;
map<string, int> Price;
vector<string> A, D;
int P0;

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    A.assign(N, "");
    for(auto & i : A) cin >> i;
    
    D.assign(M, "");
    for(auto & i : D) cin >> i;

    cin >> P0;
    for(int i=0;i<M;++i){
        cin >> Price[D[i]];
    }

    int ans = 0;
    for(const auto & i : A){
        auto it = Price.find(i);
        if(it == Price.end()) ans += P0;
        else ans += it->second;
    }
    cout << ans << endl;
    return 0;
}