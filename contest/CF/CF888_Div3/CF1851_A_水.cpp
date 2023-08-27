/**
 * 按照给定条件检查一下数组A中符合条件的元素数量
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

int N, M, K, H;
vi A;

int proc(){
    int ans = 0;
    for(auto h : A){
        auto cha = H - h;
        if(cha % K) continue;
        cha /= K;
        if(-M < cha and cha < M and cha != 0) ++ans;
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
        cin >> N >> M >> K >> H;
        A.assign(N, 0);
        for(auto & i : A) cin >> i;
        cout << proc() << endl;
    }
    return 0;
}