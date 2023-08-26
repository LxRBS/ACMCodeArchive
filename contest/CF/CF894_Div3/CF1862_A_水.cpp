/**
 * 给定一个矩阵，问能否“vika”是否能是按列的子序列
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
vector<string> A;

bool proc(){
    static const string T = "vika";
    int k = 0;

    for(int i=0;i<M;++i){
        for(int j=0;j<N;++j){
            if(A[j][i] == T[k]){
                ++k;
                break;
            }
        }
        if(k == 4) break;
    }
    return k == 4;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> M;
        A.assign(N, "");
        for(auto & s : A) cin >> s;
        cout << (proc() ? "YES" : "NO") << endl;
    }
    return 0;
}
