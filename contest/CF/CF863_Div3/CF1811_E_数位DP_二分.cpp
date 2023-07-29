/**
 * 令数列A为不含4的正整数数列，问该数列的第K个数是多少
 * 显然数位DP可以求出[1, N]中数列A的元素数量，于是二分即可
 * 由于该数列规则极其简单，因此也可以不用递归形式的数位DP，直接推导即可。
 * 标程就是这样做的。
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


llt K;
llt D[20];
llt Dig[20];

llt dfs(int pos, bool limit){
    if(-1 == pos) return 1;

    if(!limit and -1 != D[pos]){
        return D[pos];
    }

    int last = limit ? Dig[pos] : 9;
    llt ans = 0;
    for(int i=0;i<=last;++i){
        if(4 == i) continue;
        ans += dfs(pos - 1, limit and i == last);
    }
    return limit ? ans : D[pos] = ans;
}

bool check(llt n){
    auto on = n;
    int k = 0;
    while(n){
        Dig[k++] = n % 10;
        n /= 10;
    }
    llt c = dfs(k - 1, true) - 1;
    // cout << "value = " << on << ", count = " << c << endl;
    return c < K;
}

llt proc(){
    llt left = 1, right = 1E13+1E12, mid;
    do{
        mid = (left + right) >> 1;
        if(check(mid)) left = mid + 1;
        else right = mid - 1;
    }while(left <= right);
    // cout << ":" << left << " " << right << endl;
    return left;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    memset(D, -1, sizeof(D));
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> K;
        cout << proc() << endl;
        // check(K);
    }
    return 0;
}

