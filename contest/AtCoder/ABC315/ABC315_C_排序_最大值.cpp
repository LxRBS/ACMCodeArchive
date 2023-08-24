/**
 * 给定N类东西，每一类有Fi和Si，即目标为
 * 当Si >= Sj时， 1. 若Fi != Fj, Target = Si + Sj 
 *               2. 若Fi == Fj， Target = Si + Sj
 * 对每个Fi只需要记录最大的两个S值即可
 * 对全部而言，只需要记录最大的两个不同的F的S值即可
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
map<llt, vector<llt>> M;
vector<llt> A;

llt proc(){
    sort(A.begin(), A.end());  

    llt ans = 0;
    if(A[N - 1]) ans = A[N - 1] + A[N];
    for(auto it=M.rbegin(),et=M.rend();it!=et;++it){
        sort(it->second.begin(), it->second.end());
        if(it->second.size() >= 2){
            ans = max(ans, it->second.back() + (*----it->second.end()) / 2);
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
    for(int f,s,i=0;i<N;++i){
        cin >> f >> s;
        M[f].push_back(s);
        A[f] = max(A[f], (llt)s);
    } 
    cout << proc() << endl;
    return 0;
}
