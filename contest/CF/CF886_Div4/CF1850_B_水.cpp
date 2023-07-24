/**
 * 给定N个pair
 * 问在满足first小于等于10的条件下的second的最大值
 * 保证有答案
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
vector<pair<int, int>> A;

int proc(){
    int k = -1;
    for(int i=0;i<N;++i){
        if(A[i].first > 10) continue;
        if(-1 == k or (A[k].second < A[i].second)){
            k = i;
        }
    }
    return k + 1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N;
        A.assign(N, {});
        for(auto & p : A) cin >> p.first >> p.second;
        cout << proc() << endl;
    }
    return 0;
}

