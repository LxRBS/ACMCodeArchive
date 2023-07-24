/**
 * 给定一个数组，问最少删除多少个数，使得剩下的相邻数的差小于等于K
 * 求出最长的满足条件的段，其他数均去掉即可
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

int N, K;
vi A;

int proc(){
    sort(A.begin(), A.end());
    int ans = 0;
    int cur = 0;
    while(1){
        int k = 0;
        while(cur + k + 1 < N and (A[cur + k + 1] - A[cur + k] <= K)){
            ++k;
        }
        ans = max(ans, k + 1);
        cur += k + 1;
        if(cur == N) break;
    }
    return N - ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> K;
        A.assign(N, 0);
        for(auto & i : A) cin >> i;
        cout << proc() << endl;
    }
    return 0;
}

