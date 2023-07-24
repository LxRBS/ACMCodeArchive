/**
 * 给定N个数，问[1, N]范围内拥有Ai作为因子的数量最多的数是多少
 * Ai可能有重复，需要先用map统计一下
 * 然后对每个Ai，用筛法即可
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

int N;
map<int, int> M;
vi A;

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    
    while(nofkase--){
        cin >> N; 
        M.clear();
        for(int a,i=0;i<N;++i){
            cin >> a;
            ++M[a];
        }

        A.assign(N + 1, 0);
        for(const auto & p : M){
            int a = p.first;
            int c = p.second;
            for(int j=a;j<=N;j+=a){
                A[j] += c;
            }
        }
        cout << *max_element(A.begin(), A.end()) << endl;
    }
    return 0;
}

