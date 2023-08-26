/**
 * 假设有数组A，数组B如下：
 * 1. B1 = A1
 * 2. 如果Ai >= A[i-1]，将Ai加入数组B
 * 现在给定B，要求重现A。任一答案均可
 * 如果Bi>=B[i-1]，则直接就是Bi
 * 否则弄两个Bi即可
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
vi A, B;

void proc(){
    B.clear(); B.reserve(N + N);
    B.push_back(A[0]);
    for(int i=1;i<N;++i){
        B.push_back(A[i]);
        if(A[i - 1] <= A[i]){
            
        }else{
            B.push_back(A[i]);
        }
    }
    cout << B.size() << endl;
    for(auto i : B) cout << i << " ";
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
        A.assign(N, 0);
        for(auto & i : A) cin >> i;
        proc();
    }
    return 0;
}
