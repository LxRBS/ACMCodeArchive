/**
 * 假设有数组A，数组B由min(Ai, Aj)构成。
 * 现在给定B，要求还原A，保证有解，任一均可
 * 给B排个序，最小值至少有N-1个，这就是A1。
 * 再找接下来的N-2个最小值，这就是A2.
 * ……
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

int N;
int M;
vi B;
vi A;

bool check(){
    return true;
}

void proc(){
    map<int, int> c;
    sort(B.begin(), B.end());
    for(auto i : B) ++c[i];
    
    A.assign(N, 0);    
    int n = N - 1;
    int k = 0;
    for(const auto & p : c){
        int left = p.second;
        while(left){
            A[k++] = p.first;
            left -= n--;
            if(N == k) break;
        }
    }
    
    while(k < N) A[k] = A[k - 1], ++k;
    
    for(auto i : A) cout << i << " ";
    cout << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N;
        M = N * (N - 1) / 2;
        B.assign(M, 0);
        for(auto & i : B) cin >> i;
        proc();
    }
    return 0;
}
