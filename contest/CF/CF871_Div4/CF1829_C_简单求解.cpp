#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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

int N;
vector<pair<int, string>> A;

int proc(){
    static const int INF = 1E9;
    int ans = INF;
    int a = 1E9, b = 1E9;
    for(const auto & p : A){
        if(p.second == "11"){
            ans = min(ans, p.first);
        }
        if(p.second[0] == '1'){
            a = min(a, p.first);
        }
        if(p.second[1] == '1'){
            b = min(b, p.first);
        }
    }
    ans = min(ans, a + b);
    return ans != INF ? ans : -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N;
        A.assign(N, {});
        for(auto & i : A) cin >> i.first >> i.second;
        cout << proc() << endl;
    }
    return 0;
}

