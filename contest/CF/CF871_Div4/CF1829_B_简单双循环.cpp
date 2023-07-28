/**
 * 给定01字符串，找最长的0段
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

int proc(){
    int ans = 0;
    int k = 0;
    while(1){
        while(k < N and 1 == A[k]) ++k;
        if(k == N) break;

        int t = 0;
        while(k + t < N and 0 == A[k + t]) ++t;
        ans = max(ans, t);
        
        if((k += t) == N) break;
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
        cin >> N;
        A.assign(N, 0);
        for(int & i : A) cin >> i;
        cout << proc() << endl;
    }
    return 0;
}

