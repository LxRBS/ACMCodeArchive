/**
 * 假设有数组A，令 Bi = max(Ai, A[i+1])，可得到B数组
 * 现在给定B数组，要求还原A数组。多解给出任一即可
 * 反向操作即可，令 A1 = B1, Ai = min(B[i-1], Bi)
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

#ifndef ONLINE_JUDGE
int const SZ = 34;
#else
int const SZ = 200000 + 12;
#endif

int N;
vi A;

void output(const vi & vec){
    for(auto i : vec) cout << i << " ";
    return (void)(cout<<endl);
}

void proc(){
    vi B(N, 0);
    B[0] = A[0];
    for(int i=1;i<N-1;++i){
        B[i] = min(A[i - 1], A[i]);
    }
    B[N - 1] = A[N - 2];
    return output(B);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N;
        A.assign(N - 1, 0);
        for(int & i : A) cin >> i;
        proc();
    }
    return 0;
}

