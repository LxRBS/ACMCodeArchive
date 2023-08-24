/**
 * 给定字符串删除指定字母后输出
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
string S;

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> S;
    for(auto ch : S){
        if(ch != 'a' and ch != 'e' and ch != 'i' and ch != 'o' and ch != 'u'){
            cout << ch;
        }
    }
    cout << endl;
    return 0;
}
