/**
 * A个a和B个b所构成的所有字符串中，求字典序排在第K位的字符串。
 * 考虑在x个a与y个b中查找第k个字符串，
 * 如果以a开头，则一共还有C(x+y-1, y)个字符串，因此如果k相当于这个数，说明当前以a开头，并且在剩下的x-1个a和y个b中找第k个字符串
 * 如果以b开头，则需要在剩下的y-1个b和x个a中找第 k - C(x+y-1, y) 名字符串
 * 因此可以递归，直到a==0或者b==0 
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
int const SZ = 61;
#else
int const SZ = 61;
#endif

array<array<llt, SZ>, SZ> C;

int A, B;
llt K;

string dfs(int a, int b, llt k){
    assert(a or b);
    if(0 == a) return string(b, 'b');
    if(0 == b) return string(a, 'a');
    if(k <= C[a - 1 + b][b]){
        return string(1, 'a') + dfs(a - 1, b, k);
    }
    return string(1, 'b') + dfs(a, b - 1, k - C[a - 1 + b][b]);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    C[0][0] = 1;
    for(int i=1;i<SZ;++i){
        C[i][0] = C[i][i] = 1;
        for(int j=1;j<i;++j){
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    cin >> A >> B >> K;
    cout << dfs(A, B, K) << endl;
    return 0;
}