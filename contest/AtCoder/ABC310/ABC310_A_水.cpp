#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using vi = vector<int>;
using vvi = vector<vi>;

int N, P, Q;
vi D;

int proc(){
    auto t = *min_element(D.begin(), D.end());
    return min(t + Q, P);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> P >> Q;
    D.assign(N, 0);
    for(auto & i : D) cin >> i;
    cout << proc() << endl;
    return 0;
}