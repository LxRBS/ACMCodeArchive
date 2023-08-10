/**
 * 数组条件：1~N的某个排列的前缀和数组，从中删除任意一个元素
 * 现在给定N和某个数组A，问A是否符合上述条件
 * 在对数组A求差分，一共有3种可能性为符合条件：
 * 1. 1~N中恰有2个数没有出现，记作x和y，且有且仅有一个大于N的数出现，且等于x、y之和，其余只出现一次
 * 2. 1~N中恰有2个数没有出现，记作x和y，且有且仅有一个数出现二次，且等于x、y之和，其余只出现一次
 * 3. 1~N中恰有1个数没有出现过，其他数均恰好出现一次
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
vector<llt> A;

bool proc(){
    vi flag(N + 1, 0);
    vector<llt> other;

    auto f = [&flag, &other](llt v){
        if(v <= N) ++flag[v];
        else other.push_back(v);
    };

    f(A[0]);
    for(int i=1;i<N-1;++i)f(A[i] - A[i - 1]);

    if(other.size() >= 2) return false;

    vi zero, two;
    for(int i=1;i<=N;++i){
        switch(flag[i]){
            case 0: {
                zero.push_back(i);
                break;
            }
            case 1: break;
            case 2: {
                two.push_back(i);
                break;
            }
            default: return false;
        }        
    }

    if(zero.size() == 2 and other.size() == 1 and two.size() == 0){
        return zero[0] + zero[1] == other[0];
    }

    if(zero.size() == 2 and other.size() == 0 and two.size() == 1){
        return zero[0] + zero[1] == two[0];
    }

    if(zero.size() == 1 and other.size() == 0 and two.size() == 0){
        return true;
    }

    return false;
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
        for(auto & i : A) cin >> i;
        cout << (proc() ? "YES" : "NO") << endl;
    }
    return 0;
}

