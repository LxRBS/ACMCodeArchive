/**
 * 给定X和Y以及N，构造数组A满足如下条件：
 * 1. A1 = X, AN = Y
 * 2. A是严格递增
 * 3. A的差分数组严格递减
 * 从后往前，差分数组按照1/2/3...递增即可
 * 如果这样还构造不出来，就不存在数组A
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

int X, Y, N;

void proc(){
    vi a(N, 0);
    a[0] = X;
    a[N - 1] = Y;
    for(int i=1,j=N-2;j>=0;++i,--j){
        a[j] = a[j + 1] - i;
    }
    if(a[0] < X) return (void)(cout << "-1" << endl);
    a[0] = X;
    for(auto i : a) cout << i << " ";
    cout << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> X >> Y >> N;
        proc();
    }
    return 0;
}