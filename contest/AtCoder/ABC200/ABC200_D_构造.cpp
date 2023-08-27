/**
 * 给定数组A，要求从中选出两个不同的子序列，使得：
 * 两个子序列之和同模200，输出方案，或者输出No
 * 这是标程的解法。显然是要取余数。
 * 当数组A的长度大于等于8以后，从A中可能取出的不同子序列总数必然超过255个
 * 因此其中必然有2个子序列对200的余数相同。
 * 因此只需要取A的前八个元素，枚举幂集即可
 * O(8*2^8)
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

void proc(){
    int n = min(N, 8);
    int limit = 1 << n;
    map<int, vi> m;
    for(int i=1;i<limit;++i){
        int tmp = 0;
        vi vec;
        for(int j=0;j<n;++j){
            if(i & (1 << j)){
                vec.push_back(j + 1);
                (tmp += A[j]) %= 200;
            }
        }
        auto it = m.find(tmp);
        if(it == m.end()){
            it = m.insert(it, {tmp, vec});
        }else{
            cout << "Yes" << endl;
            cout << it->second.size();
            for(auto i : it->second) cout << " " << i;
            cout << endl;
            cout << vec.size();
            for(auto i : vec) cout << " " << i;
            cout << endl;
            return;
        }
    }
    return (void)(cout << "No" << endl);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    A.assign(N, 0);
    for(auto & i : A)cin >> i;
    proc();
    return 0;
}