/**
 * 每次操作可以在集合里任挑一个，按2：1分割为两个数放回集合
 * 初始集合里只有N，问能否经过若干次操作使得集合中出现M
 * 所有能够出现的数必然是
 *     2 ^ i
 *   --------- * N ， 其中k在[1, K]，K是N所含3的幂次，i在[0, k]
 *     3 ^ k
 * K必然不大，双重循环即可。
 * 用int的话要注意乘除的顺序，否则溢出
 * 推荐直接使用longlong
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

int N, M;

int get(int n){
    int ans = 0;
    while(n and 0 == n % 3) n /= 3, ++ans;
    return ans;
}

bool proc(){
    if(N == M) return true;
    if(N < M) return false;

    int k = get(N);
    int fenmu = 1;
    for(int i=1;i<=k;++i){
        fenmu *= 3;
        int fenzi = 1;
        for(int j=0;j<=i;++j){
            if(N / fenmu * fenzi == M) return true;
            fenzi <<= 1;
        }
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
        cin >> N >> M;
        cout << (proc() ? "YES" : "NO") << endl;
    }
    return 0;
}

