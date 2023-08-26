/**
 * 给定一个数组A，再给定N，M，D
 * 要求从数组中最多挑出M个数，每个数的得分为： Ai + D * (i - 上一个挑出的数的索引)
 * 求最大得分
 * 简单推导一下，可知对任意序列，得分 = SIMGA{Ai} - D * Last[i]
 * 即惩罚只需考虑最后一个索引即可，前面的元素只是单纯求和
 * 因此负数可以忽略，无论如何不会挑选负数。
 * 然后始终维持前M-1大的数之和即可，记作sum
 * for Ai : 
 *     ans = max(ans, sum + Ai - D * i)
 *     维护sum
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

using QTy = __gnu_pbds::priority_queue<pii, greater<pii>>;

int N, M, D;
vi A;

llt proc(){
    QTy q;
    llt ans = 0;
    llt sum = 0;
    for(int i=0;i<N;++i){
        if(A[i] <= 0) continue;
        
        ans = max(ans, sum + A[i] - D * (i + 1LL));
        sum += A[i];
        q.push({A[i], i});
        if(q.size() >= M){
            sum -= q.top().first;
            q.pop();
        }
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
        cin >> N >> M >> D;
        A.assign(N, 0);
        for(auto & i : A) cin >> i;
        cout << proc() << endl;
    }
    return 0;
}