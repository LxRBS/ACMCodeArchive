/**
 * 给定N和K，再给定N*N的数字阵
 * 问K*K的子区域的中位数最小是多少
 * K是3，中位数就是排名第5的数，K是4，中位数就是排名第8的数，令中位数排名为rank
 * 做一个二分。令x为当前要检查的数
 * 遍历矩阵，若干Aij <= x，则令Bij为1
 * 然后依次检查B矩阵的每一个K*K的区域，如果该区域的1大于等于rank个，
 * 说明该区域的中位数 <= x，找到最大的x，使得该区域的中位数 <= x 对所有区域均不成立
 * 则 x + 1 就是所有区域中位数的最小值。
 * 数区域1的数量可以使用前缀和完成。
 * Aij最大为1E8，O(31N^2)，N在800.
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
int const SZ = 101;
#else
int const SZ = 110;
#endif

int N, K;
vvi A;

bool check(int mid){
    vvi d(N + 1, vi(N + 1, 0));
    for(int i=1;i<=N;++i)for(int j=1;j<=N;++j){
        int w = A[i - 1][j - 1] <= mid ? 1 : 0;
        d[i][j] = d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1] + w;
    }
    int cnt = K & 1 ? K * K / 2 + 1 : K * K / 2;
    for(int i=K;i<=N;++i)for(int j=K;j<=N;++j){
        auto tmp = d[i][j] + d[i - K][j - K] - d[i - K][j] - d[i][j - K];
        if(tmp >= cnt) return true;
    }
    return false;
}

int proc(){
    int left = 0, right = 1E9, mid;
    do{
        mid = (left + right) >> 1;
        if(check(mid)) right = mid - 1;
        else left = mid + 1;
    }while(left <= right);
    return left;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    A.assign(N, vi(N, 0));
    for(auto & v : A)for(auto & i : v) cin >> i;
    cout << proc() << endl;
    return 0;
}