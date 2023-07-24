/**
 * 将字符矩阵中的小写字母按照从上到下从左到右的顺序组成一个字符串
 * 
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

array<string, 8> A;
string proc(){
    string ans;
    for(const auto & s : A){
        for(char ch : s){
            if(islower(ch)){
                ans += ch;
            }
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
        for(auto & s : A) cin >> s;
        cout << proc() << endl;
    }
    return 0;
}

