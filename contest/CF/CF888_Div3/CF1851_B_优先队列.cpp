/**
 * 给定数组A，只允许做如下操作：若Ai和Aj奇偶相同，则可以交换
 * 问是否可以通过任意次上述交换使得A有序
 * 将奇数和偶数分别塞入最小堆
 * 对每一个位置i，根据Ai的奇偶性在相应队列中取出最小值放上
 * 最后看是否有序即可
 * O(NlogN)
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

int get(int v, __gnu_pbds::priority_queue<int, greater<int>> & q){
    if(q.empty()) return -1;
    auto ans = q.top(); q.pop();
    return ans;
}

bool proc(){
    __gnu_pbds::priority_queue<int, greater<int>> q[2];
    for(auto i : A) q[i&1].push(i);

    vi b(N, 0);
    for(int i=0;i<N;++i){
        b[i] = get(A[i], q[A[i] & 1]);
        if(i > 0 and b[i] < b[i - 1]) return false;
    }
    return true;
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
        cout << (proc() ? "YES" : "NO") << endl;
    }
    return 0;
}