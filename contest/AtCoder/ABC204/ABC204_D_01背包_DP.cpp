/**
 * 有N个任务，每个任务需要连续花费Ti分钟，有两个工作器，问最少多少时间可以完成
 * 做一个01背包，将任务分成两半，看长的那一半的时间，求一个最小。
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

int N;
vi A;

int proc(){
    int total = accumulate(A.begin(), A.end(), 0);
    vi d(total + 1, 0);
    d[0] = 1;
    for(int i=1;i<=N;++i){
        const auto wi = A[i];
        for(int v=total;v>=wi;--v){
            d[v] |= d[v - wi];
        }
    }
    int ans = total;
    for(int i=1;i<=total;++i){
        if(d[i] and d[total - i]){
            ans = min(ans, max(i, total - i));
        }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    A.assign(N + 1, 0);
    for(int i=1;i<=N;++i) cin >> A[i];
    cout << proc() << endl;
    return 0;
}